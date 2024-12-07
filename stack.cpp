#include <iostream>
using namespace std;

/*
  Stack implementation with templates and operators
*/

template <typename T>
class stack {
  public:
    stack (int size){
      maxsize = size;
      array = new T [maxsize];
      position = -1;
    }

    stack (const stack &s){
      maxsize = s.maxsize;
      array = new T [maxsize];
      position = s.position;
      for (int i = 0; i <= s.position; i++){
      array[i] = s.array[i];
      }
    }

    //~stack (){ delete[] array;}

    const stack & operator = (const stack &s){
      int j = s.position;
      position = j;
      for (int i = 0; i <= j; i++){
        array[i] = s.array[i];
      }
      return (s);
    }
    bool empty (){return (position == -1);}

    void push (const T &x) {
      if( position > maxsize-1)
        cout << "error" << endl;
      else {
        ++position;
        array[position] = x;
      }
    }

    T pop (){
      position--;
      return (array[position + 1]);
    }

    int size () {return (position + 1);}

    friend ostream & operator << (ostream &out, const stack &s) {
      int j = s.position;
      out << '[';
      if (s.position != -1){
        for (int i = 0; i <= s.position; i++){
          out << s.array[i];
          if (j > 0) { out << ", "; j--;}
        }
      }
      out << ']';
      return out;
    }

  private:
    int maxsize;
    int position;
    T *array;

};
