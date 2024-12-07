#include <iostream>
using namespace std;

/*
  Calculate the input power of 2
*/

int main() {
  int A;
  cin >> A;
  int sum = 0;
  if (A / 10 == 0) sum += A;
  while (A / 10 != 0){
    sum += A % 10;
    A = A / 10;
    if (A / 10 == 0) sum += A;
  }
  cout << sum << endl;
}
