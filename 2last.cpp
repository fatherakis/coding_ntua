#include <iostream>
using namespace std;

/*
Simple Program checking if a number is within 0 - 999999 and printing "yes" if total number of digits is even
*/


int main() {
  int C;
  cin >> C;

  int mul = 1;
  for (int i = 1; i < 7; ++i){
    mul = mul * 10;
    if (C / mul == 0){
      if (i % 2 != 0) cout << "no" << endl;
      else cout << "yes" << endl;
      return 0;
    }
  }
  cout << "out of bounds" << endl;
  return 0;
}
