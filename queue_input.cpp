#include <iostream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;

/*
	Queue implementation, parsing string input with " " delimiter adding item into the queue
*/

struct nod3
{
	nod3 *next;
	string input;
	int w;
};
typedef nod3 *typ;

struct node
{
	string info;
	node *next;
};
typedef node *list;

class queue
{
public:
	queue();
	bool empty();
	void enqueue(string x);
	string dequeue();

private:
	struct node
	{
		string info;
		node *next;
	};
	node *front, *rear;
};

queue::queue()
{
	front = rear = nullptr;
}

bool queue::empty()
{
	return front == nullptr;
}

void queue::enqueue(string x)
{
	node *p = new node;
	p->info = x;
	p->next = nullptr;
	if (front == nullptr)
		front = p;
	else
		rear->next = p;
	rear = p;
}

string queue::dequeue()
{
	node *p = front;
	string result = front->info;
	if (front == rear)
		rear = nullptr;
	front = front->next;
	delete p;
	return result;
}

struct nodenew
{
	int num;
	nodenew *next;
};
typedef nodenew *count;

class queuenew
{
public:
	queuenew();
	bool empty();
	void enqueuenew(int x);
	int dequeuenew();

private:
	struct node
	{
		int num;
		nodenew *next;
	};
	nodenew *front, *rear;
};

queuenew::queuenew()
{
	front = rear = nullptr;
}

bool queuenew::empty()
{
	return front == nullptr;
}

void queuenew::enqueuenew(int x)
{
	nodenew *p = new nodenew;
	p->num = x;
	p->next = nullptr;
	if (front == nullptr)
		front = p;
	else
		rear->next = p;
	rear = p;
}

int queuenew::dequeuenew()
{
	nodenew *p = front;
	int result = front->num;
	if (front == rear)
		rear = nullptr;
	front = front->next;
	delete p;
	return result;
}

int main()
{
	queue s;
	stack<string> mystruct;
	queuenew number, check;
	nod3 h;
	string test, test2;
	string temp;
	string line = "  ";
	int word = 0;
	int count = 0;
	int counter = 0;
	int variable = 0;
	char c = ' ';

	while (count != 3)
	{
		getline(cin, test);
		istringstream ss(test);
		while (getline(ss, h.input, ' '))
		{
			h.w = h.input.length();
			if (h.w != 0)
			{
				number.enqueuenew(h.w);
				check.enqueuenew(h.w);
				mystruct.push(h.input);
				s.enqueue(h.input);
			}
		}
		count++;
	}
	while (!s.empty())
	{
		test2 = s.dequeue();
		counter++;
		word += number.dequeuenew();
		cout << test2 << endl;
	}
}
