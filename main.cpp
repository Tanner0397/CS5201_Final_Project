#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "matrix.h"
#include "FileError.h"
#include "gauss.h"
#include "MatrixDimError.h"
#include "upper_matrix.h"
#include "lower_matrix.h"
#include "diagonal_matrix.h"
#include "symmetric_matrix.h"
#include "tridiagonal_matrix.h"
#include "thomas.h"
#include "cholesky.h"

using namespace std;


int main(int argc, char** argv)
{
  string filename = "";
  try
  {
    if(argc < 2)
      throw FileError();
    filename = argv[1];
  }
  catch (FileError e)
  {
    cerr << "Error: No file specified. " << endl;
    return 1;
  }
  ifstream file(filename);
  if(!file.is_open())
  {
    cout << "File does not exist. Exiting. " << endl;
    return 1;
  }
  //obtain matrix A and column vector b
  if(file.peek() == ifstream::traits_type::eof())
  {
    cout << "File empty. Exiting." << endl;
    return 1;
  }
  unsigned int rows;//, cols;
  file >> rows;
  //We're assuming a square matrix for the program
  //cols = rows;

  //Read as normal matrix
  Diagonal_Matrix<double> A(rows);
  Vector<double> b(rows);

  file >> A;
  file >> b;

  file >> rows;
  Tridiagonal_Matrix<double> B(rows);
  file >> B;
  try
  {
    // Vector<double> x;
    // try
    // {
    //   Symmetric_Matrix<double> SYMM(A);
    //   Cholesky_Decomposition<double> cholesky;
    //   x = cholesky(SYMM, b);
    //   cout << "A's Type: 0" << endl;
    //   cout << "A * A^T:" << endl << SYMM*SYMM.transpose() << endl;
    //   cout << "x: " << endl << x.column_format() << endl;
    //   cout << "A * x: " << endl << (SYMM*x).column_format() << endl;
    // }
    // catch(ModificationError e)
    // {
    //   //This is a Tridiagonal matrix that is not symmetric
    //   Tridiagonal_Matrix<double> TRI(A);
    //   Thomas_Method<double> thomas;
    //   x = thomas(TRI, b);
    //   cout << "A's Type: 1" << endl;
    //   cout << "A * A^T:" << endl << TRI*TRI.transpose() << endl;
    //   cout << "x: " << endl << x.column_format() << endl;
    //   cout << "A * x: " << endl << (TRI*x).column_format() << endl;
    // }

    cout << A*B << endl;

  }
  catch(MatrixDimError e)
  {
    cerr << "Matrix Dimension Error -- rows: " << e.get_bad_row() << " -- cols: " << e.get_bad_col() << endl;
  }
  catch(InputError e)
  {
    cerr << "Invalid Input" << endl;
  }
  catch(DimensionError e)
  {
    cerr << "Vector b invalid size" << endl;
  }
  catch(SingularError e)
  {
    cerr << "Matrix A is singular, cannot solve system" << endl;
  }
  catch(RangeError e)
  {
    cerr << "Index [" << e.badSubscript() << "] is out of range" << endl;
  }
  catch(PositiveDefError e)
  {
    cerr << "Error: Matrix Given is not Positive Definite, Cholesky Decomposition is not possible" << endl;
  }


  return 0;
}
