#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

/*
  Rational Number operations using normal operators
*/
rational::rational (int n, int d) {
  nom = n;
  den = d;
}


rational operator + (const rational &x, const rational &y) {
  rational t((x.nom * y.den + y.nom * x.den) / rational::gcd((x.nom * y.den + y.nom * x.den) , (x.den * y.den)) , (x.den * y.den) / rational::gcd((x.nom * y.den + y.nom * x.den) , (x.den * y.den)));
  return t;
}


rational operator - (const rational &x, const rational &y){
  rational t((x.nom * y.den - y.nom * x.den) / rational::gcd((x.nom * y.den - y.nom * x.den) , (x.den * y.den)) , (x.den * y.den) / rational::gcd((x.nom * y.den - y.nom * x.den) , (x.den * y.den)));
  return t;
}


rational operator * (const rational &x, const rational &y){
  rational t((x.nom * y.nom) / rational::gcd((x.nom * y.nom) , (x.den * y.den)), (x.den * y.den) / rational::gcd((x.nom * y.nom) , (x.den * y.den)));
  return t;
}


rational operator / (const rational &x, const rational &y){
  rational t((x.nom * y.den ) / rational::gcd((x.nom * y.den) , (x.den * y.nom)) , (x.den * y.nom) / rational::gcd((x.nom * y.den) , (x.den * y.nom)));
  return t;
}

std::ostream & operator << (std::ostream &out, const rational &x){
   out << x.nom <<  '/' << x.den;
   return out;
}

int rational::gcd (int a, int b){
  a = abs(a);
  b = abs(b);
  int c;
  while (a > 0 && b > 0)
    if (a > b) a = a % b;
    else       b = b % a;

  c = a + b;
  return c;
}



int main() {
	rational a(1, 2);
	rational b(3, 4);
	rational c(5, 6);
  std::cout << a << " " << b << " " << c << std::endl;
	std::cout << a + b - c << std::endl;
	std::cout << a << " should still be 1/2" << std::endl;
}