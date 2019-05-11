/**
 *  @file gauss.hpp
 *  @brief Class implmentation for gauss
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include "abstract_matrix.h"
#include "vector.h"
#include "Array.h"
#include "SingularError.h"
#include "matrix.h"
#include <math.h>
#include "DimensionError.h"

#include <iostream>
using namespace std;

template <typename T>
Vector<T> Gauss<T>::operator()(const Abstract_Matrix<T>& A, Vector<T> b) const
{
  if(b.size() != A.num_rows())
    throw DimensionError(A.num_rows());
  if(A.num_rows() != A.num_cols())
    throw MatrixDimError(A.num_rows(), A.num_cols());
  //Ax=b, vector to solve for
  Vector<T> x(b.size());
  Matrix<T> matrix(A);
  int n = matrix.num_rows(); // n x n matrix
  Array<T> s(n); //need n spots for row maximums
  Array<unsigned int> l(n);
  int i, j, k;
  double smax = 0;
  double xmult = 0;
  double absolute_a = 0;
  double r = 0;
  double rmax = 0;
  double tolerance = 0.005;

  //Scalding vector
  for(i = 0; i < n; i++)
  {
    l[i] = i;
    smax = 0;
    for(j = 0; j < n; j++)
    {
      absolute_a = fabs(matrix(i, j));
      if(absolute_a > smax)
        smax = absolute_a;
    }
    s[i] = smax;
  }
  //steps
  for(k = 0; k < n-1; k++)
  {
    //choose pivot equation
    rmax = 0;
    j=k;
    for(i = k; i < n; i++)
    {
      if(fabs(s[l[i]]) < tolerance)
        throw SingularError();
      r = fabs(matrix(l[i], k) / s[l[i]]);
      if (r > rmax)
      {
        rmax = r;
        j = i;
      }
    }
    //interchance indecies
    std::swap(l[j], l[k]);
    //Eliminate
    for(i=k+1; i < n; i++)
    {
      if(fabs(matrix(l[k], k)) < tolerance)
        throw SingularError();
      xmult = matrix(l[i], k) / matrix(l[k], k);
      //Prevent modification of Upper Triangular matricies
      //std::cout << "test" << std::endl;
      if(matrix(l[i], k) != xmult)
        matrix.get_elem(l[i], k) = xmult;
      for(j = k+1; j < n; j++)
      {
        //Added to prevent modification of Upper triangular matrcies
        //std::cout << l[i] << " " << j << std::endl;
        if(matrix(l[i], j) != matrix(l[i], j) - (xmult*matrix(l[k], j)))
          matrix.get_elem(l[i], j) = matrix(l[i], j) - (xmult*matrix(l[k], j));
      }
    }
  }

  //Start forward elimination
  for(k = 0; k < n-1; k++)
  {
    for(i = k+1; i < n; i++)
    {
      b[l[i]] -= matrix(l[i], k)*b[l[k]];
    }
  }

  //Start backwards solving
  double ss = 0;
  for(i = n-1; i >= 0; i--)
  {
    ss = b[l[i]];
    for(j = i+1; j < n; j++)
    {
      ss -= matrix(l[i], j)*x[j];
    }
    if(fabs(matrix(l[i], i)) < tolerance)
      throw SingularError();
    x[i] = ss / matrix(l[i], i);
  }

  return x;
}

template <typename T>
Vector<T> Gauss<T>::operator()(Symmetric_Matrix<T>& matrix, Vector<T> b) const
{

  // if (mat.num_rows() != b.size()) {
  //   throw sizeErr(b.getSize());
  // }
  //
  // double tolerance = 0.00001;
  //
  // int dimension = b.getSize();
  // Matrix<T> A(mat);
  //
  // for (int i = 0; i < dimension; i++) {
  //   T pivotVal = A(i, i);
  //   for (int j = i; j < dimension && j < i + 4; j++) {
  //     A.get_elem(i, j) = A(i, j) / pivotVal;
  //   }
  //   b[i] = b[i] / pivotVal;
  //   for (int j = i+1; j < dimension && j < i + 4; j++) {
  //     if (fabs(A(j, i)) > tolerance && fabs(b[i]) > tolerance) b[j] -= A(j, i) * b[i];
  //     if (fabs(A(j, i)) > tolerance) {
  //       for(int k = 0; k < dimension; k++) {
  //         A.get_elem(i, k) -= A(j, i)*A(j, k);
  //       }
  //     }
  //   }
  // }
  //
  // for (int i = dimension - 1; i > 0; i--) {
  //   for (int j = i-1; j > -1 && i - j > 4; j--) {
  //     if (fabs(b[i]) > tolerance && fabs(A(j, i))) b[j] -= b[i] * A(j, i);
  //   }
  // }
  //
  // return b;





  if(b.size() != matrix.num_rows())
    throw DimensionError(matrix.num_rows());
  if(matrix.num_rows() != matrix.num_cols())
    throw MatrixDimError(matrix.num_rows(), matrix.num_cols());
  //Ax=b, vector to solve for
  Vector<T> x(b.size());
  //Matrix<T> matrix(A);
  int n = matrix.num_rows(); // n x n matrix
  Array<T> s(n); //need n spots for row maximums
  Array<unsigned int> l(n);
  int i, j, k;
  double smax = 0;
  double xmult = 0;
  double absolute_a = 0;
  double r = 0;
  double rmax = 0;
  double tolerance = 0.005;

  //Scalding vector
  for(i = 0; i < n; i++)
  {
    l[i] = i;
    smax = 0;
    for(j = 0; j < n; j++)
    {
      absolute_a = fabs(matrix(i, j));
      if(absolute_a > smax)
        smax = absolute_a;
    }
    s[i] = smax;
  }
  //steps
  for(k = 0; k < n-1; k++)
  {
    //choose pivot equation
    rmax = 0;
    j=k;
    for(i = k; i < n; i++)
    {
      if(fabs(s[l[i]]) < tolerance)
        throw SingularError();
      r = fabs(matrix(l[i], k) / s[l[i]]);
      if (r > rmax)
      {
        rmax = r;
        j = i;
      }
    }
    //interchance indecies
    std::swap(l[j], l[k]);
    //Eliminate
    for(i=k+1; i < n; i++)
    {
      if(fabs(matrix(l[k], k)) < tolerance)
        throw SingularError();
      xmult = matrix(l[i], k) / matrix(l[k], k);
      //Prevent modification of Upper Triangular matricies
      //std::cout << "test" << std::endl;
      if(matrix(l[i], k) != xmult)
        matrix.get_elem(l[i], k) = xmult;
      for(j = k+1; j < n; j++)
      {
        //Added to prevent modification of Upper triangular matrcies
        //std::cout << l[i] << " " << j << std::endl;
        if(matrix(l[i], j) != matrix(l[i], j) - (xmult*matrix(l[k], j)))
          matrix.get_elem(l[i], j) = matrix(l[i], j) - (xmult*matrix(l[k], j));
      }
    }
  }

  //Start forward elimination
  for(k = 0; k < n-1; k++)
  {
    for(i = k+1; i < n; i++)
    {
      if (fabs(matrix(l[i], k)) > tolerance && fabs(b[l[k]]) > tolerance) b[l[i]] -= matrix(l[i], k)*b[l[k]];
    }
  }

  //Start backwards solving
  double ss = 0;
  for(i = n-1; i >= 0; i--)
  {
    ss = b[l[i]];
    for(j = i+1; j < n; j++)
    {
      if (fabs(matrix(l[i], j)) > tolerance && fabs(x[j]) > tolerance) ss -= matrix(l[i], j)*x[j];
    }
    if(fabs(matrix(l[i], i)) < tolerance)
      throw SingularError();
    x[i] = ss / matrix(l[i], i);
  }

  return x;
}
