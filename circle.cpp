#include <iostream>
#include <cmath>
using namespace std;

/*
  Simple program checking if given coordinates are within the unit circle
*/

int main () {
  double x,y;
  cin >> x >> y;
  if (x == 0 && y == 0){
    cout << "inside" << endl;
    return 0;
  }
  else if (x > 1 || y > 1){
    cout << "outside" << endl;
    return 0;
  }
  double cos = x*x / (x*x + y*y);
  double sin = y*y / (x*x + y*y);
  double length = (x*x + y*y);
  if ((cos == 0 && (y == 1 || y == -1)) || cos == -1 || cos == 1) cout << "border" << endl;
  else if (length <= 1) cout << "inside" << endl;
  else cout << "outside" << endl;
}
