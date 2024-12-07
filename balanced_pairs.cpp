#include <iostream>
#include <sstream>
using namespace std;

/*
  Program checking whether there is a balanced pair of positive and negative integers in the input string.
  Eg. 2 -2 5 -5 -> yes,  2 -1 -> no, 5 -2 -3 -> no. 
  Any character in the input will be ignored 
*/


struct node {
	int info;
	node *next;
};
typedef node *list;

class queue {
	public:
		queue ();
		bool empty ();
		void enqueue (   int x);
		int dequeue ();
    int peak ();
	private:
		struct node {
			int info;
			node *next;
		};
		node *front, *rear;
};

queue::queue () {
	front = rear = nullptr;
}

bool queue::empty () {
	return front == nullptr;
}

void queue::enqueue (   int x) {
	node *p = new node;
	p->info = x;
	p->next = nullptr;
	if (front == nullptr) front = p;
	else
		rear->next = p;
	rear = p;
}

int queue::dequeue () {
	node *p = front;
	int result = front->info;
  if (front == rear) rear = nullptr; front = front->next; delete p;
	return result;
}

int queue::peak () {
	node *p = front;
	int result = front->info;
  if (front == rear) rear = nullptr;
	return result;
}

int main(){
  queue pos, neg;
  bool value = true;
  int a;
  string s ,l ;
  int c;
  const char* m;
  int count = 0;
  getline(cin,s);
    istringstream ss(s);
      while (getline(ss, l, ' ')){
        m = l.c_str();
        a = atoi(m);
        if (a < 0){
          neg.enqueue(a);
          count++;
        }
        else if (a > 0){
          pos.enqueue(a);
          count++;
        }
      }
  if ((count % 2) == 0){
   while (!pos.empty() && !neg.empty()){
     if(pos.peak() == abs(neg.peak())){
       pos.dequeue();
       neg.dequeue();
       value = true;
     }
     else {value = false; break;}
   }
  }
  else if ((count % 2) != 0){ value = false; }
  if (value == true) cout << "yes" << endl; else cout << "no" << endl; //answer
}
