#include <iostream>
using namespace std;

/*
  Lexicon Program listing added words and their duplicate count along with search and replace functionality
*/

class LexiconTreeStructure{
  public:
    string key;
    int repetition_count;
    LexiconTreeStructure *left,*right;
    LexiconTreeStructure(const string &k) : key(k), repetition_count(1), left(nullptr), right(nullptr){}
    ~LexiconTreeStructure(){
      delete left;
      delete right;
    }
};

class lexicon{
  public:
    lexicon() : root(nullptr) {}
    ~lexicon() {
      delete root;
    }
    void insert (const string &s){
      if (root == nullptr){
        root = new LexiconTreeStructure(s);
        return;
      }
      LexiconTreeStructure *recur = root, *parent;
      while (recur != nullptr){
        if (recur->key == s){
          recur->repetition_count++;
          return;
        }
        parent = recur;
        if (recur->key < s) recur = recur->right;
        else if (recur->key > s) recur = recur->left;
      }
      if(recur == nullptr){
        if (parent->key < s){
          parent->right = new LexiconTreeStructure(s);
        }
        else if (parent->key > s){
          parent->left = new LexiconTreeStructure(s);
        }
      }
    }
    int lookup (const string &s) const{
      LexiconTreeStructure *p = find(s);
      if (p != nullptr) return p->repetition_count;
      else return 0;
    }
    int depth (const string &s) const{
      int depth = 0;
      LexiconTreeStructure *p;
      p = root;
      while (p->key != s){
        if (p->key < s) p = p->right;
        else if (p->key > s) p = p->left;
        if (p == nullptr) return 0;
        depth++;
      }
      return depth+1;
    }
    void replace (const string &s1, const string &s2){
      LexiconTreeStructure *s = find(s1);
      if (s == nullptr) return;
      else{
        int count = s->repetition_count;
        dele(root,s1);
        LexiconTreeStructure *g = find(s2);
        if (g == nullptr){
          insert(s2);
          g = find(s2);
          g->repetition_count += abs(count) - 1;
        }
        else g->repetition_count += abs(count);
        return;
      }
    }
    friend ostream & operator << (ostream &out, const lexicon &l){
      l.postorder(l.root);
      return out;
    }
  private:
    void postorder (LexiconTreeStructure *t) const{
      if(t != nullptr){
        postorder(t->left);
        cout << t->key << ' ' << t->repetition_count << endl;
        postorder(t->right);
      }
    }
    LexiconTreeStructure *root;
    LexiconTreeStructure *find (const string &s) const{
      LexiconTreeStructure *temp = root;
      LexiconTreeStructure *parent = root;
      while (temp->key != s){
        if (temp->key > s) temp = temp->left;
        else if (temp->key < s) temp = temp->right;
        if (temp == nullptr) return nullptr;
      }
      return temp;
    }
    int height (LexiconTreeStructure *c){
      if (c == nullptr) return -1;
      else return 1 + max(height(c->left),height(c->right));
    }
    void dele(LexiconTreeStructure *&root, const string &str){
      if (root == nullptr) return;
      if (str < root->key) dele(root->left, str);
      else if (str > root->key) dele(root->right, str);
      else{
        if (root->left == nullptr && root->right == nullptr){
          delete root;
          root = nullptr;
        }
        else if (root->left != nullptr && root->right != nullptr){
          LexiconTreeStructure *predec = FindMax(root->left);
          root->key = predec->key;
          root->repetition_count = predec->repetition_count;
          dele(root->left, predec->key);
        }
        else{
          LexiconTreeStructure *kiddo;
          if (root->left != nullptr) kiddo = root->left;
          else kiddo = root->right;
          root = kiddo;
        }
      }
    }
    LexiconTreeStructure* FindMax(LexiconTreeStructure* root){
	    while(root->right != NULL) root = root->right;
	    return root;
    }
    void search (LexiconTreeStructure *&temp, const string &str, LexiconTreeStructure* &parent1){
      while (temp != nullptr && temp->key != str){
        parent1 = temp;
        if(str < temp->key) temp = temp->left;
        else temp = temp->right;
        }
    }
};

int main(){
  lexicon l;
  l.insert("key");
  l.insert("gun");
  l.insert("game");
  l.insert("of");
  l.insert("thrones");
  l.insert("thrones");
  cout << l.lookup("thrones") << endl;
  cout << endl;
  cout << l.depth("game") << endl;
  cout << endl;
  cout << l << endl;
  l.replace("key", "game");
  cout << l << endl;
  l.replace("game", "thrones");
  cout << l << endl;
}
