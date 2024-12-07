#include <iostream>
using namespace std;

/*
  Input 2 numbers and print the last 2 digits of their product inverted
*/


int main() {
  int A,B;
  cin >> A >> B;

  int C;
  C = A * B;

  int firstlast;
  firstlast = (C / 10) % 10;

  int secondlast;
  secondlast = (C / 100) % 10;

  cout << secondlast << firstlast << endl;
}
