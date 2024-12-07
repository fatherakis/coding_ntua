#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

/*
  A program where a chessboard is represented as an array while restricting access to the black tiles in the form of out of bounds error.

  NOTE: This code works only up until C++14
*/


class ChessBoardArray {
  protected:

    class Row {
      public:
        Row(ChessBoardArray &a, int i) : chessBoardArray(a), row(i) {}
        int & operator [] (int i) const {
          return chessBoardArray.select(row, i);
        }
      private:
        ChessBoardArray &chessBoardArray;
        int row;
    };

    class ConstRow {
      public:
        ConstRow(const ChessBoardArray &a, int i) : chessBoardArray(a), row(i) {}
        int operator [] (int i) const{
          return chessBoardArray.select(row,i);
        }
      private:
        const ChessBoardArray &chessBoardArray;
        int row;
    };

  private:

    int *data;
    unsigned c;
    unsigned s;
    int startr = 0, startc = 0;
    unsigned maxr,maxc;
    unsigned sizem;
    unsigned int loc(int i, int j) const throw(out_of_range) {
      int row = i - startr, column = j - startc;
      if (row < 0 || column < 0 || row >= (int)sizem || column >= (int)sizem) throw out_of_range("invalid index");
      if ((row + column + startc * 2) % 2 != 0) throw out_of_range("invalid index");
      if ((int)sizem % 2 == 0) return ((row * ((int)maxc) + column) / 2);
      return ((row * ((int)maxc) + column) / 2) + 1;
    }

  public:

    ChessBoardArray(unsigned size = 0, unsigned base = 0) : s(base), maxr(size), maxc(size), sizem(size) {
      if (s != 0){
        startr = (int) s;
        startc = (int) s;
      }
      else startr = startc = 1;
      if ((int)size % 2 == 0){
        c = (size * size) / 2;
        data = new int [c];
      }
      else{
        c = ((size * size) / 2) + 1;
        data = new int [c];
      }
      for (int i = 0; i < (int)c; ++i){
        data[i] = 0;
      }
    }
    ChessBoardArray(const ChessBoardArray &a) {
      maxr = maxc = sizem = a.maxr;
      s = a.s;
      startr = startc = a.startr;
      c = a.c;
      data = new int [c];
      for (int i = 0; i < (int)a.c; i++){
        data[i] = a.data[i];
      }
    }
    ~ChessBoardArray(){
      delete [] data;
    }
    ChessBoardArray & operator = (const ChessBoardArray &a){
      startc = startr= a.startc;
      maxc = sizem = maxr = a.maxc;
      c = a.c;
      s = a.s;
      delete [] data;
      data = new int [c];
      for (int i = 0; i < (int)c; ++i) data[i] = a.data[i];
      return *this;
    }
    int & select(int i, int j){
      if(s == 0){
        return data[loc(i+1,j+1)];
      }
      if ((int)sizem % 2 == 0){
        return data[loc(i,j)];
      }
      return data[loc(i,j) - 1];
    }
    int select(int i, int j) const{
      if(s == 0){
        return data[loc(i+1,j+1)];
      }
      if ((int)sizem % 2 == 0){
        return data[loc(i,j)];
      }
      return data[loc(i,j) - 1];
    }
    const Row operator [] (int i){
      return Row(*this,i);
    }
    const ConstRow operator [] (int i) const{
      return ConstRow(*this, i);
    }
    int choose (int i, int j) const{
      if ((int)sizem % 2 == 0){
        return data[loc(i,j)];
      }
      return data[loc(i,j)-1];
    }
    friend ostream & operator << (ostream &out, const ChessBoardArray &a){
      if (a.startr > 1){
        for (int i = a.startc; i <= (((int)a.maxc + a.startc - 1)); i++){
          for (int j = a.startc; j <= (((int)a.maxr) + a.startr - 1); j++){
            if ((i + j ) % 2 != 0) out << setw(4) << 0;
            else out << setw(4) << a.choose(i,j);
          }
          out << endl;
        }
      }
      else{
        for (int i = a.startc; i <= ((int)a.maxc); i++){
          for (int j = a.startc; j <= ((int)a.maxr); j++){
            if ((i + j ) % 2 != 0) out << setw(4) << 0;
            else out << setw(4) << a.choose(i,j);
          }
          out << endl;
        }
      }
      return out;
    }
};

int main() {
  ChessBoardArray a(4, 1);
  // size 4x4, rows and columns numbered from 1
  a[3][1] = 42;
  a[4][4] = 17;
  try{ a[2][1] = 7; }
  catch (out_of_range &e) { cout << "a[2][1] is black" << endl; }
  try{ cout << a[1][2] << endl; }
  catch (out_of_range &e) { cout << "and so is a[1][2]" << endl; }
  cout << a;
  cout << endl;
  ChessBoardArray a1(8,1);
  cout << a1;
  cout << endl;
  ChessBoardArray b(7);
  cout << b;
  ChessBoardArray a0;
  cout << a0;
  cout << endl;
  ChessBoardArray a4(4);
  a4.select(0,0) = 5;
  a4.select(3,3) = 7;
  cout << a4;
  try{ a4.select(4,0); }
  catch (out_of_range &e) { cout << "exc" << endl; }
  try{ cout << a4.select(4,1) << endl; }
  catch (out_of_range &e) { cout << "exc" << endl; }
  cout << endl;
  const ChessBoardArray a5(5,7);
  cout << a5.select(7,7) << endl;
  cout << a5.select(11,11) << endl;
  cout << a5;
  try{ a5.select(12,6); }
  catch (out_of_range &e) { cout << "exc" << endl; }
  try{ cout << a5.select(5,6) << endl; }
  catch (out_of_range &e) { cout << "exc" << endl; }
  try{ a5.select(0,0); }
  catch (out_of_range &e) { cout << "exc" << endl; }
  cout << endl;
  ChessBoardArray a6(5,2);
  a6.select(3,5) = 42;
  cout << a6;
  cout << endl;
  ChessBoardArray b1(a6);
  cout << b1;
  cout << endl;
  a6.select(4,6) = 17;
  cout << a6;
  cout << endl;
  cout << b1;
  cout << endl;
  b1.select(2,4) = 34;
  cout << a6;
  cout << endl;
  cout << b1;
  cout << endl;
  ChessBoardArray a7(5,2);
  a7.select(3,5) = 42;
  cout << a7;
  cout << endl;
  ChessBoardArray b2(2);
  cout << b2;
  cout << endl;
  b2 = a7;
  cout << b2;
  a7.select(4,6) = 17;
  cout << endl;
  cout << a7;
  cout << endl;
  cout << b2;
  b2.select(2,4) = 34;
  cout << endl;
  cout << a7;
  cout << endl;
  cout << b2;
  cout << endl;
  ChessBoardArray a8(4);
  a8[0][0] = 5;
  a8[3][3] = 7;
  cout << a8;
  try{ a8[4][0] = 9; }
  catch (out_of_range &e) { cout << "exc" << endl; }
  try{ cout << a8[4][1] << endl; }
  catch (out_of_range &e) { cout << "exc" << endl; }
  cout << endl;
  const ChessBoardArray a9(5,7);
  cout << a9[7][7] << endl;
  cout << a9[11][11] << endl;
  cout << a5;
  cout << endl;
  try{ a9.select(12,6); }
  catch (out_of_range &e) { cout << "exc" << endl; }
  try{ cout << a9.select(5,6) << endl; }
  catch (out_of_range &e) { cout << "exc" << endl; }
  try{ a9.select(0,0); }
  catch (out_of_range &e) { cout << "exc" << endl; }
  ChessBoardArray a10(4);
  a10[0][0] = 5;
  a10[3][3] = 7;
  cout << a10;
  cout << endl;
  auto r = a10[3];
  cout << r[3] << endl;
  try{ cout << r[2] << endl;}
  catch (out_of_range &e) { cout << "exc" << endl; }
  r[1] = 42;
  cout << a10;
  cout << endl;
  ChessBoardArray a11(4);
  a11[0][0] = 5;
  a11[3][3] = 7;
  const ChessBoardArray b3(a11);
  cout << b3;
  cout << endl;
  auto r1 = b3[3];
  cout << r1[3] << endl;
  try{ cout << r1[2] << endl;}
  catch (out_of_range &e) { cout << "exc" << endl; }
}
