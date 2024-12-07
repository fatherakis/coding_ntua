#include <iostream>
using namespace std;

/*
  List implementation supporting adding nodes in specific (pre-existing) positions, removal of specific node by position, fetch and display
*/

class list {
  public:
    list () {
      start = new node;
      start = nullptr;
      sizen = 0;
    }
    bool empty () {
      return (start == nullptr);
    } 
    int size () {
      return sizen;
    } 
    void add (int k, int x){
      node *temp = new node;
      node *current = new node;
      temp->data = x;
      temp->next = nullptr;
      current = start;
      if (start == nullptr || k == 0){
        temp->next = current;
        start = temp;
      }
      else {
        node *previous;
        int limit = sizen;
        if (k < sizen) limit = k;
        for (int i = 0; i < sizen; i++){
          previous = current;
          current = current->next;
        }
        previous->next = temp;
        temp->next = current;
      }
      ++sizen;
    }
    void display (){
      node *print = new node;
      print = start;
      while (print != nullptr){
        cout << print->data << " ";
        print = print->next;
      }
      cout << endl;
    }
    int get (int k) {
      node *ret = new node;
      ret = start;
      int limit = sizen;

      if (k < sizen) limit = k;
      for (int i = 0; i < limit; i++){
        ret = ret->next;
      }
      return (ret->data);
    }
    void remove (int k) {
      node *previous = new node;
      node *current = new node;
      previous = nullptr;
      current = start;
      if (k == 0){
        start = start->next;
      }
      else{
        if (k >= sizen) return;
        for (int i = 0; i < k; i++){
          previous = current;
          current = current->next;
        }
        previous->next = current->next;
      }
      --sizen;
    }
  private:
    struct node {
      int data;
      node *next;
    };
    node *start;
    int sizen;
};

int main(){
  list l;
  int a, k, x;
  cout << "Insert number of nodes to add: ";
  cin >> a;
  for (int i = 0; i < a; i++){
    cout << "Insert Position and Value: " << endl;
    cin >> k >> x;
    l.add(k,x);
    l.display();
    cout << endl;
  }
  int b , d;
  cout << "Insert number of nodes to remove: ";
  cin >> b;
  if (b > 1){
    for (int i = 0; i < b; i++){
      cout << "Insert node position: ";
      cin >> d;
      l.remove(d);
      l.display();
      cout << endl;
    }
  }
  else{
    cout << "Insert node position: ";
    cin >> d;
    l.remove(d);
    l.display();
    cout << endl;
  }
  int r;
  cout << "Insert node position to fetch data: ";
  cin >> r;
  cout << l.size() << ' ' << l.get(r) << endl;
  l.display();
}
