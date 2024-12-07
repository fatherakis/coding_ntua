#include <iostream>
using namespace std;


/*
  Insert graph edges and connections to generate an Euler path if it exists
*/


int graphs[10000];
int primes[2];

int main (){
  int N, M;
  cin >> N;
  cin >> M;
  int j , k;
  for (int i = 0; i < M; i++){
    cin >> j;
    cin >> k;
    graphs[j]++;
    graphs[k]++;
  }
  int points = 0;
  int nice = 0;
  int c = 0;
  for (int i = 0; i < N; i++){
    if (graphs[i] % 2 != 0 && points > 2){
      c = 8;
    }
    else if (graphs[i] % 2 !=0){
      points++;
      if (primes[0] == 0) primes[0] = i;
      else primes[1] = i;
    }
    if (graphs[i] % 2 == 0) nice++;
  }
  if (nice == N){
    cout << "CYCLE" << endl;
  }
  else if (points == 2){
    cout << "PATH "<< min(primes[0],primes[1]) << ' ' << max(primes[0],primes[1]) << endl;
  }
  else if (c == 8){
    cout << "IMPOSSIBLE" << endl;
  }
}
