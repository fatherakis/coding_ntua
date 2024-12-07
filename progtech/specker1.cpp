#include <iostream>
#include <stdexcept>
using namespace std;

/* Initial implementation of Specker Game */


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
      if ((move.getSource() < 0) || (move.getSource() > size) || (move.getTarget() < 0) || (move.getTarget() > size)) {
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
     if (count == size) return true;
     else return false;
    }
    int getHeaps() const {
      return size;
    }
    int getCoins(int h) const throw(logic_error) {
      if (h < size && h >= 0) return a[h];
      else throw logic_error("invalid heap");
    }
    friend ostream & operator << (ostream &out, const State &state) {
        for (int i = 0; i < state.size; ++i){
          out << state.a[i];
          if ( i+1 > state.size) out << ", ";
        }
        out << endl;
        return out;
    }
  protected:
    int size;
    int *a;
};
