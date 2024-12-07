#include <iostream>
#include <cmath>
using namespace std;

/*
  A program returning yes if the 3rd input number is between the min and max of the other 2
*/


int main () {
  double N, M, L;
  cin >> N >> M >> L;
  double max = N + M;
  double min = abs(N - M);
  if (L == 0 || M == 0 || N == 0){
    cout << "no" << endl;
    return 0;
  }
  if (L > min && L < max){
    cout << "yes" << endl;
  }
  else cout << "no" << endl;
}
