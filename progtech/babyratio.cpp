#ifndef CONTEST
#include "babyratio.hpp"
#include <iostream>
#endif
using namespace std;

/*
  Rational Number operations
*/


rational::rational (int n, int d) {
 nom = n;
 den = d;
}

rational rational::add (rational r) {
    rational t((nom * r.den + r.nom*den) / gcd(nom * r.den + r.nom * den , den * r.den) , (den * r.den) / gcd(nom * r.den + r.nom * den , den * r.den));
return t;
}

rational rational::sub (rational r) {
    rational t((nom * r.den - r.nom*den) / gcd((nom * r.den - r.nom*den) , (den * r.den)) , (den * r.den) / gcd((nom * r.den - r.nom*den) , (den * r.den)));
  return t;
}
rational rational::mul (rational r) {
  rational t((nom * r.nom) / gcd(nom * r.nom , den * r.den), (den * r.den) / gcd(nom * r.nom , den * r.den));
 return t;
 }

 rational rational::div (rational r) {
  rational t((nom * r.den ) / gcd(nom * r.den , den * r.nom) , (den * r.nom) / gcd(nom * r.den , den * r.nom));
  return t;
 }

 void rational::print (){
   cout << nom <<  '/' << den;
 }

 int rational::gcd(int a, int b){
    a = abs(a);
    b = abs(b);
    int c;
    while (a > 0 && b > 0){
        if (a > b) a = a % b;
        else       b = b % a;
        c = a + b;
    }
    return c;
    };


  int main() {
    rational a(1, 2);
    rational b(3, 4);
    rational c(5, 6);
    a.add(b).sub(c).print();
    cout << endl;
    a.print();
    cout << " should still be 1/2" << endl;
  }