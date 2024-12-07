#include <iostream>
using namespace std;

/*
  Program checking if input year is a mundial year
*/

int main () {
  long int N;
  cin >> N;
  if (N < 1930){
    cout << "no" << endl;
    return 0;
  }
  if (N == 1942 || N == 1946){
    cout << "no" << endl;
    return 0;
  }
  if ((N - 1930) % 4 == 0)
    cout << "yes" << endl;
  else cout << "no" << endl;
}
