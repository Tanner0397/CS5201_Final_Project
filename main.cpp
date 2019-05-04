///
/// \file main.cpp
/// \brief This file contains the driver function
/// \author Tanner Wendland
/// \author Alex Sanchez
///


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include "matrix.h"
#include "FileError.h"
#include "gauss.h"
#include "MatrixDimError.h"
#include "upper_matrix.h"
#include "lower_matrix.h"
#include "symmetric_matrix.h"
#include "cholesky.h"
#include "DomainError.h"
//#include "function.h"
#include "FiniteDiff.h"
#include <time.h>

//Obtain math constants
/*! A constant for the tolerance of a double */
#define TOLERANCE 1.0E-30

using namespace std;

///
/// \fn double BCfunc(double x, double y)
/// \brief This function defines the boundary functions of the PDE
/// \pre none
/// \post The funciton value at (x, y) on the boundary is returned
/// \throws DomainError if x-M_PI > TOLERANCE || x < 0
/// \throws DomainError if y-M_PI > TOLERANCE || y < 0
/// \returns the value of (x, y) on the boundary of the PDE
///

double BCfunc(double x, double y)
{
  if(x-M_PI > TOLERANCE || x < 0)
    throw DomainError();
  if(y-M_PI > TOLERANCE || y < 0)
    throw DomainError();
  double value = 0;
  if(fabs(x) < TOLERANCE)
    value = sin(y);
  else if(fabs(y) < TOLERANCE)
    value = sin(x);
  return value;
}

/*! A pointer to a function that takes 2 doubles and returns a double */
typedef double(*funcPtr)(double, double);

///
/// \fn int main(int argc, char** argv)
/// \pre none
/// \post the program has completed
/// \param argc is the number of arguments in the command line
/// \param argv is an array containing the arguments from the command line
///

int main(int argc, char** argv)
{
  try
  {

    if(argc != 2)
    {
      cerr << "Invalid Paramaters. Please use \"./driver n\" where n is a positive integer." << endl;
      return 1;
    }
    int divs = stoi(argv[1]);
    if(divs < 1)
    {
      cerr << "Number of divisions must be positive" << endl;
      return 1;
    }

    clock_t clock1;
    clock_t clock2;

    FiniteDiff<double, BCfunc> solver(divs);

    //--- Gaussian Partial Pivoting ---
    clock1=clock();
    cout << "Guassian Partial Pivoting Solution: " << endl;
    solver.doGauss();
    clock1=clock()-clock1;
    cout << "Time Taken: " << (1000*clock1)/CLOCKS_PER_SEC << " ms." << endl;
    // --- end Guassian Partial Pivoting ---

    // --- Cholesky Decomposition ---
    clock2=clock();
    cout << "\n\nCholesky Decomposition Solution: " << endl;
    solver.doCholesky();
    clock2=clock()-clock2;
    cout << "Time Taken: " << (1000*clock2)/CLOCKS_PER_SEC << " ms." << endl;

    //solver.tupleOutput();




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
  catch(DomainError e)
  {
    cerr << "Input outside the domain of the function" << endl;
  }
  catch(...)
  {
    cerr << "Default Exception" << endl;
    return 1;
  }

  return 0;
}
