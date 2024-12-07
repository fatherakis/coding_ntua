#include <iostream>
#include <stdexcept>
using namespace std;

/* 
  Full implementation of Specker Game along with 4 different player types
*/

class Move {
  public:
     Move(int sh, int sc, int th, int tc);
     int getSource() const;
     int getSourceCoins() const;
     int getTarget() const;
     int getTargetCoins() const;
     friend ostream & operator << (ostream &out, const Move &move){
       if (move.gave != 0) {
    			out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts " << move.getTargetCoins() << " coins to heap " << move.getTarget();
       }
       else {
    			out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts nothing";
    		}
        out << endl;
        return out;
     }
  protected:
    int took;
    int from;
    int gave;
    int to;
};

Move::Move (int sh, int sc, int th, int tc) {
    took = sc;
    from = sh;
    gave = tc;
    to = th;
}

int Move::getTarget () const {
  return to;
}

int Move::getTargetCoins () const {
  return gave;
}

int Move::getSource () const {
  return from;
}

int Move::getSourceCoins () const {
  return took;
}

class State {
  public:
    State(int h, const int c[]) {
      size = h;
      a = new int [size];
      for(int i = 0; i < size; ++i) a[i] = c[i];
    }
    ~State () {
      delete[] a;
    }
    void next(const Move &move) throw(logic_error) {
      if ((move.getSource() < 0) || (move.getSource() >= size) || (move.getTarget() < 0) || (move.getTarget() >= size)) {
         throw logic_error("invalid heap");
       }
       else if ((move.getSourceCoins() < 1) || (move.getTargetCoins() < 0) || (move.getSourceCoins() <= move.getTargetCoins()) || (move.getSourceCoins() > getCoins(move.getSource()))) {
         throw logic_error("invalid heap");
       }
       else {
         a[move.getSource()] -= move.getSourceCoins();
         a[move.getTarget()] += move.getTargetCoins();
       }
    }
    bool winning() const {
     int count = 0;
     for (int i = 0; i < size; ++i){
       if (a[i] == 0) ++count;
     }
     if (count > size-1) return true;
     else return false;
    }
    int getHeaps() const {
      return size;
    }
    int getCoins(int h) const throw(logic_error) {
      if (h < size && h >= 0) return a[h];
      else throw logic_error("invalid heap, out of bounds call");
    }
    friend ostream & operator << (ostream &out, const State &state) {
        for (int i = 0; i < state.size; ++i){
          out << state.a[i];
          if ( i+1 < state.size) out << ", ";
        }
        out << endl;
        return out;
    }
  protected:
    int size;
    int *a;
};

class Player {
  public:
    Player(const string &n){
      name = n;
    }
    virtual ~Player(){
      name.clear();
    }
    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;
    friend ostream & operator << (ostream &out, const Player &player){
      out << player.getType() << " player " << player.name;
    	return out;
    }
  protected:
    string name;
};

class SneakyPlayer : public Player {
    public:
    	SneakyPlayer(const string &n) : Player(n) {
    		player_type = "Sneaky";
    	}
    	virtual const string &getType() const override {
    		return player_type;
    	}
    	virtual Move play(const State &s) override {
    		int j = 0;
    		while (s.getCoins(j) == 0) ++j;
    		int source_heap = j;
    		int source_coins = s.getCoins(j);
    		for (int i = j + 1; i < s.getHeaps(); i++) {
    			if ((s.getCoins(i) < source_coins) && (s.getCoins(i) > 0)) {
    				source_heap = i;
    				source_coins = s.getCoins(i);
    			}
    		}
    		Move SneakyObject(source_heap, source_coins, 0, 0);
    		return SneakyObject;
    	}
    private:
    	string player_type;
};

class SpartanPlayer : public Player {
  public:
    SpartanPlayer(const string &n) : Player(n) {
      player_type = "Spartan";
    }
    virtual const string &getType() const override {
      return player_type;
    }
    virtual Move play(const State &s) override {
      int count = 0;
      int j = 0;
      while (s.getCoins(j) == 0) ++j;
      int source_heap = j;
      int source_coins = s.getCoins(j);
      for (int i = j + 1; i < s.getHeaps(); i++) {
        if ((s.getCoins(i) > source_coins)) {
          if(i+1 < s.getHeaps() && s.getCoins(i) == s.getCoins(i+1)){
            source_heap = i+1;
            source_coins = s.getCoins(i+1);
            break;
          }
          else{
            source_heap = i;
            source_coins = s.getCoins(i);
          }
        }
      }
      Move SpartanObject(source_heap, 1, 0, 0);
      return SpartanObject;
    }
  private:
    string player_type;
};

class GreedyPlayer : public Player {
  public:
    GreedyPlayer(const string &n) : Player(n) {
      player_type = "Greedy";
    }
    virtual const string &getType() const override {
      return player_type;
    }
    virtual Move play(const State &s) override {
      int count = 0;
      int j = 0;
      while (s.getCoins(j) == 0) ++j;
      int source_heap = j;
      int source_coins = s.getCoins(j);
      for (int i = j + 1; i < s.getHeaps(); i++) {
        if ((s.getCoins(i) > source_coins)) {
          if(i+1 < s.getHeaps() && s.getCoins(i) == s.getCoins(i+1)){
            source_heap = i+1;
            source_coins = s.getCoins(i+1);
            break;
          }
          else{
            source_heap = i;
            source_coins = s.getCoins(i);
          }
        }
      }
      Move GreedyObject(source_heap, source_coins, 0, 0);
      return GreedyObject;
    }
  private:
    string player_type;
};

class RighteousPlayer : public Player {
  public:
    RighteousPlayer(const string &n) : Player(n) {
      player_type = "Righteous";
    }
    virtual const string &getType() const override {
      return player_type;
    }
    virtual Move play(const State &s) override {
      int count = 0;
      int count1 = 0;
      int j = 0;
      while (s.getCoins(j) == 0) ++j;
      int source_heap = j;
      int source_coins = s.getCoins(j);
      int l = j;
      int target_heap = l;
      int target_coins = s.getCoins(l);
      for (int i = j + 1; i < s.getHeaps()-1; i++) {
        if ((s.getCoins(i) > source_coins)) {
          if(i+1 < s.getHeaps() && s.getCoins(i) == s.getCoins(i+1)){
            source_heap = i+1;
            source_coins = s.getCoins(i+1);
            break;
          }
          else{
            source_heap = i;
            source_coins = s.getCoins(i);
          }
        }
        else if ((s.getCoins(i) < source_coins) && (s.getCoins(i) > 0)) {

          if(i+1 < s.getHeaps() && s.getCoins(i) == s.getCoins(i+1)){
            target_heap = i+1;
            target_coins = s.getCoins(i+1);
            break;
          }
          else {
            target_heap = i;
            target_coins = s.getCoins(i);
          }
        }
      }
      Move RighteousObject(source_heap, source_coins/2, target_heap, (source_coins/2)-1);
      return RighteousObject;
    }
  private:
    string player_type;
};

class Game {
public:
	Game(int heaps, int players){
    maxHeaps = heaps;
  	maxPlayers = players;
  	heap_now = 0;
  	player_now = 0;
  	heap_coins = new int [maxHeaps];
  	player_table = new Player*[maxPlayers];
  }
	~Game(){
    delete [] heap_coins;
    delete [] player_table;
  }
	void addHeap(int coins) throw(logic_error){
    if (coins < 0 || heap_now >= maxHeaps) throw logic_error("Check coins or maxHeaps");
    else {
      heap_coins[heap_now] = coins;
      ++heap_now;
    }

  }
	void addPlayer(Player *player) throw(logic_error){
    if ( player_now >= maxPlayers) throw logic_error("Check maxPlayers");
  	else {
  		player_table[player_now] = player;
  		++player_now;
  	}
  }
	void play(ostream &out) throw(logic_error){
    if ( (player_now != maxPlayers) && (heap_now != maxHeaps) ) throw logic_error("Something went wrong");
    else {
      int l = 0;
      State object(maxHeaps, heap_coins);
      while ( !object.winning() ){
        out << "State: " << object << endl;
        out << *player_table[l % maxPlayers] << " " << player_table[l % maxPlayers]->play(object) << endl;
        object.next( player_table[l % maxPlayers]->play(object) );
        ++l;
      }
      out << "State: " << object << endl;
      --l;
      out << *player_table[l % maxPlayers] << " wins" << endl;
    }
  }
private:
	int maxHeaps, maxPlayers, heap_now, player_now;
	int *heap_coins;
	Player **player_table;
};


int main () {
	Game specker(10, 8);
	specker.addHeap(10);
	specker.addHeap(20);
	specker.addHeap(17);
  specker.addHeap(32);
  specker.addHeap(56);
  specker.addHeap(47);
  specker.addHeap(119);
  specker.addHeap(23);
  specker.addHeap(43);
  specker.addHeap(56);
  specker.addPlayer(new RighteousPlayer("Robin"));
  specker.addPlayer(new GreedyPlayer("Alan"));
  specker.addPlayer(new SpartanPlayer("Mary"));
  specker.addPlayer(new SneakyPlayer("Tom"));
  specker.addPlayer(new RighteousPlayer("Elle"));
  specker.addPlayer(new GreedyPlayer("Chris"));
  specker.addPlayer(new SpartanPlayer("Jack"));
  specker.addPlayer(new SneakyPlayer("Sophie"));
  
	
	

	specker.play(std::cout);
}