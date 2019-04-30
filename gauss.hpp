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
