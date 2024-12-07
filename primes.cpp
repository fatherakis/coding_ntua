#include <iostream>
#include <cmath>
using namespace std;
//Fermat
bool odd(int n){
  return (n % 2 == 1);
}

int power(int x, unsigned int y, int p){
  int res = 1;
  x = x % p;
  while (y > 0){
    if (y & 1) res = (res * x) % p;
    y = y >> 1;
    x = (x*x) % p;
  }
  return res;
}
int fermatTestAlgorithm(int a, int n, int p){
  if (a == 0) return 0;
  if (n == 0) return 1;
  long long y;
  if (odd(n)){
    y = a % p;
    y = (y * (fermatTestAlgorithm(a, n - 1, p) % p)) % p;
  }
  else{
    y = fermatTestAlgorithm(a, n/2, p);
    y = (y * y) % p;
  }
  return (y + p) % p;
}

bool fermatTestCheck(int n){
  int a;
  for (int i = 0; i < 30; i++){
    a = rand() % n + 1;
    if (fermatTestAlgorithm(a, n-1, n) != 1) return false;
  }
  return true;
}
//End Fermat

//Miller-Rabin

bool millerTest(int d, int n) {
  int a = 2 + rand() % (n - 4);
  int x = calc(a, d, n);
  if (x == 1  || x == n-1)
    return true;
  while (d != n-1){
    x = (x * x) % n;
    d *= 2;
    if (x == 1)      return false;
    if (x == n-1)    return true;
  }
  return false;
}

bool isPrime(int n, int k) {
  if (n <= 1 || n == 4)  return false;
  if (n <= 3) return true;
  int d = n - 1;
  while (d % 2 == 0)
    d /= 2;
  for (int i = 0; i < k; i++)
  if (!millerTest(d, n))
    return false;
  return true;
}

int main(){
  int n;
  cin >> n ;
  if (isPrime(n, 30)) cout << "is prime" << endl;
  else cout << "is a composite" << endl;
}
