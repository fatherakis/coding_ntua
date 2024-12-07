#include <iostream>
#include <cmath>
using namespace std;

/*
  A program implementing polynomial equations with evaluation and addition & multiplication between them
*/


class Polynomial {
  protected:
    class Term {
      public:
        int exponent;
        int coefficient;
        Term *next;
        Term(int exp, int coeff, Term *n) : exponent(exp), coefficient(coeff), next(n) {}
        friend class Polynomial;
    };
    Term *begin;
  private:
    int size = 0;
    Polynomial &mult(Term* point ,const Polynomial &q){
      Term* current;
      current = q.begin;
      while (current != nullptr){
        addTerm(point->exponent + current->exponent , point->coefficient * current->coefficient);
        current = current->next;
      }
      return *this;
    }
  public:
    Polynomial() {
      begin = new Term(0,0,nullptr);
    }  //node equivilent
    Polynomial(const Polynomial &p){
      Term *current;
      begin = new Term(0,0,nullptr);
      size = 0;
      current = p.begin;
      while (current != nullptr){
        addTerm(current->exponent, current->coefficient);
        current = current->next;
      }
    }
    ~Polynomial(){
      delete begin;
    } 
    Polynomial & operator = (const Polynomial &p){
      begin = new Term(0,0,nullptr);
      size = 0;
      Term *referance;
      referance = p.begin;
      while (referance->next != nullptr){
        addTerm(referance->exponent , referance->coefficient);
        referance = referance->next;
      }
      return *this;
    }
    void addTerm(int expon, int coeff){
      Term *current;
      current = begin;
      Term *previous;
      while (current != nullptr){
        if (coeff == 0) return;
        else {
          if(begin == nullptr){
            Term *temp = new Term (expon,coeff,nullptr);
            begin = temp;
            return;
          }
          if (current->exponent == expon){
            current->coefficient += coeff;
            if (current->coefficient == 0){
              if (current == begin){
                begin = begin->next;
                return;
              }
              else{
                previous->next = current->next;
                return;
              }
            }
            return;
          }
          if (expon > current->exponent){
            if (current == begin){
              //current = begin;
              Term *temp = new Term (expon,coeff,begin);
              //temp->next->next = current->next;
              begin = temp;
              return;
            }
            else {
              Term *temp = new Term (expon,coeff,current);
              previous->next = temp;
              return;
            }
          }
          if(current->next == nullptr){
            Term *temp = new Term (expon,coeff,nullptr);
            current->next = temp;
            return;
          }
        }
        previous = current;
        current = current->next;
      }
      return;
    }
    double evaluate(double x){
      Term *current;
      double result = 0;
      current = begin;
      while (current != nullptr){
        result += ((current->coefficient) * pow(x, current->exponent));
        current = current->next;
      }
      return result;
    } //should work fine
    friend Polynomial operator+ (const Polynomial &p, const Polynomial &q){
      Term *currentp;
      Polynomial R;
      Term *currentq;
      currentp = p.begin;
      currentq = q.begin;
      while (currentp != nullptr){
        R.addTerm(currentp->exponent, currentp->coefficient);
        currentp = currentp->next;
      }
      while (currentq != nullptr){
        R.addTerm(currentq->exponent, currentq->coefficient);
        currentq = currentq->next;
      }
      return R;
    }
    friend Polynomial operator* (const Polynomial &p, const Polynomial &q){
      Term *point;
      point = p.begin;
      Polynomial P;
      while(point != nullptr){
        P.mult(point,q);
        point = point->next;
      }
      return P;
    } // w/out non sorted fix
    friend ostream & operator << (ostream &out, const Polynomial &p){
      Term *current;
      current = p.begin;
      if (p.begin == nullptr){
        out << 0;
        return out;
      }
      if (p.begin->next == nullptr){
        if (p.begin->coefficient == 0) out << 0;
        else {
          //if (p.begin->coefficient == 1 && p.begin->exponent != 0) continue;
          if (p.begin->coefficient > 0) {
            if (p.begin->exponent != 0) {
              if(p.begin->coefficient != 1) out << p.begin->coefficient;
            }
            else out << p.begin->coefficient;
          }
          else if (p.begin->coefficient < 0){
            out << "- " << abs(p.begin->coefficient);
          }
          if (p.begin->exponent != 0) out << 'x';
          if (p.begin->exponent != 0 && p.begin->exponent != 1){
            out << '^' << p.begin->exponent;
          }
        }
        return out;
      }
      while(current != nullptr){
        if (current == p.begin){
          if (current->coefficient < 0){
            out << "- ";
            if (current->exponent == 0) out << abs(current->coefficient);
            if (current->exponent != 0){
              if (current->coefficient != -1) out << abs(current->coefficient);
              out << "x";
              if (current->exponent != 1){
                out << "^" << current->exponent;
              }
            }
          }
          if (current->coefficient > 0){
            if (current->exponent == 0) out << current->coefficient;
            if (current->exponent != 0){
              if (current->coefficient != 1) out << current->coefficient;
              out << "x";
              if (current->exponent != 1){
                out << "^" << current->exponent;
              }
            }
          }
        }
        else{
          if (current->coefficient < 0){
            out << " - ";
            if (current->exponent == 0) out << abs(current->coefficient);
            if (current->exponent != 0){
              if (current->coefficient != -1) out << abs(current->coefficient);
              out << "x";
              if (current->exponent != 1){
                out << "^" << current->exponent;
              }
            }
          }
          if (current->coefficient > 0){
            out << " + ";
            if (current->exponent == 0) out << abs(current->coefficient);
            if (current->exponent != 0){
              if (current->coefficient != 1) out << current->coefficient;
              out << "x";
              if (current->exponent != 1){
                out << "^" << current->exponent;
              }
            }
          }
        }
        current = current->next;
      }
      return out;
    } 
};
int main() {
  //default
  Polynomial p;
  p.addTerm(2, 1);
  p.addTerm(1, 2);
  p.addTerm(0, 1);
  Polynomial q;
  q.addTerm(1, 1);
  q.addTerm(0, 2);
  cout << "P(x) = " << p << endl;
  cout << "P(0) = " << p.evaluate(0) << endl;
  cout << "Q(x) = " << q << endl;
  cout << "Q(1) = " << q.evaluate(1) << endl;
  cout << "(P+Q)(x) = " << p + q << endl;
  cout << "(P*Q)(x) = " << p * q << endl;
}
