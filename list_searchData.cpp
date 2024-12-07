#include <iostream>
using namespace std;

/*
  List implementation with search by data and move results to front.
*/


class list
{
public:
  list()
  {
    start = new node;
    start = nullptr;
    sizen = 0;
  }
  bool empty()
  {
    return (start == nullptr);
  }
  int size()
  {
    return sizen;
  }
  void add(int k, int x)
  {
    node *temp = new node;
    node *current = new node;
    temp->data = x;
    temp->next = nullptr;
    current = start;
    if (start == nullptr || k == 0)
    {
      temp->next = current;
      start = temp;
    }
    else
    {
      node *previous;
      int limit = sizen;
      if (k < sizen)
        limit = k;
      for (int i = 0; i < sizen; i++)
      {
        previous = current;
        current = current->next;
      }
      previous->next = temp;
      temp->next = current;
    }
    ++sizen;
  }
  void display()
  {
    node *print = new node;
    print = start;
    while (print != nullptr)
    {
      cout << print->data << " ";
      print = print->next;
    }
    cout << endl;
  }
  int get(int k)
  {
    node *ret = new node;
    ret = start;
    int limit = sizen;

    if (k < sizen)
      limit = k;
    for (int i = 0; i < limit; i++)
    {
      ret = ret->next;
    }
    return (ret->data);
  }
  void remove(int k)
  {
    node *previous = new node;
    node *current = new node;
    previous = nullptr;
    current = start;
    if (k == 0)
    {
      start = start->next;
    }
    else
    {
      if (k >= sizen)
        return;
      for (int i = 0; i < k; i++)
      {
        previous = current;
        current = current->next;
      }
      previous->next = current->next;
    }
    --sizen;
  }
  int searchMF(int x)
  {
    int found = 0;
    int count = 1;
    int counter = 0;
    int s = 0;
    node *temp = new node;
    node *previous = new node;
    node *current = new node;
    current = start;
    while (current->data != x)
    {
      previous = current;
      current = current->next;
      ++count;
      if (count > sizen)
        return 0;
    }
    if (current != start)
    {
      temp = current;
      previous->next = current->next;
      current = start;
      start = temp;
      start->next = current;
    }
    return count;
  }

private:
  struct node
  {
    int data;
    node *next;
  };
  node *start;
  int sizen;
};

int main()
{
  list l;
  int a, k, x;
  cout << "Number of items to add: ";
  cin >> a;
  for (int i = 0; i < a; i++)
  {
    cout << "Type position and value to add: ";
    cin >> k >> x;
    l.add(k, x);
    l.display();
    cout << endl;
  }
  int b, d;
  cout << "Number of values to be searched: ";
  cin >> b;
  if (b > 1)
  {
    for (int i = 0; i < b; i++)
    {
      cout << "Type value to search";
      cin >> d;
      cout << l.searchMF(d) << endl;
      l.display();
      cout << endl;
    }
  }
  else
  {
    cout << "Type value to search: ";
    cin >> d;
    cout << l.searchMF(d) << endl;
  }

}
