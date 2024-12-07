#include <iostream>
using namespace std;

/*
  List implementation
*/


struct node
{
  int data;
  node *next;
};
typedef node *lst;

class list
{
public:
  list();
  bool empty();
  int size();
  void add(int k, int x);
  int get(int k);
  void remove(int k);

private:
  struct node
  {
    int data;
    node *next;
  };
  node *head;
};

list::list()
{
  head = nullptr;
}

bool list::empty()
{
  return (head == nullptr);
}

int list::size()
{
  int length = 1;
  node *count;
  count = head;
  if (head == nullptr)
    return 0;
  while (count->next != nullptr)
  {
    ++length;
    count = count->next;
  }
  return length;
}

void list::add(int k, int x)
{
  node *cur;
  node *temp = new node;
  node *prev;
  temp->data = x;
  cur = head;
  if (head == nullptr || k == 0)
  {
    temp->next = cur;
    head = temp;
  }
  else
  {
    int limit = size();
    if (k < size()) limit = k;
    for (int i = 0; i < limit; i++)
    {
      prev = cur;
      cur = cur->next;
    }
    prev->next = temp;
    temp->next = cur;
    
  }
}

int list::get(int k)
{
  node *temp;
  temp = head;
  if (k == 0)
  {
    return temp->data;
  }
  else
  {
    int limit = size();
    if (k < size()) limit = k;
    for (int i = 0; i < limit; i++)
    {
      temp = temp->next;
    }
    return temp->data;
  }
}

void list::remove(int k)
{
  node *current;
  current = head;
  if (k == 0)
  {
    head->next = head->next->next;
  }
  else
  {
    if (k >= size()) return;
    for (int i = 0; i < k; i++)
    {
      current = current->next;
    }
    current->next = current->next->next;
  }
  delete current;
}

int main()
{
  list l;
  int a, k, x;
  cout << "num ";
  scanf("%d", &a);
  for (int i = 0; i < a; i++)
  {
    cout << "pos, val: ";
    scanf("%d %d", &k, &x);
    l.add(k, x);
  }
  int b, d;
  cout << "num remove: "; 
  scanf("%d", &b);
  if (b > 1)
  {
    for (int i = 0; i < b; i++)
    {
      cout << "pos: ";
      scanf("%d", &d);
      l.remove(d);
    }
  }
  else
  {
    cout << "pos: ";
    scanf("%d", &d);
    l.remove(d);
  }
  int r;
  cout << "fetch: ";
  scanf("%d", &r);
  cout << l.size() << ' ' << l.get(r) << endl;
}
