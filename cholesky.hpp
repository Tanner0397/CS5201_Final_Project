/**
 *  @file cholesky.hpp
 *  @brief Class implmentation for cholesky decompostion
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include "vector.h"
#include "DimensionError.h"
#include "SingularError.h"
#include "lower_matrix.h"
#include "PositiveDefError.h"
#include <math.h>

template <typename T>
Vector<T> Cholesky_Decomposition<T>::operator()(const Symmetric_Matrix<T>& m, const Vector<T>& b) const
{
  double tolerance = 1.0E-30;
  if(m.num_rows() != b.size())
    throw DimensionError(b.size());
  //Symmetrix matrix is a square always so lets just grab one thing
  int n = m.num_rows();
  Lower_Matrix<T> L(n);

  //Decompose the matrix
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j <= i; j++)
    {
      double sum = 0;
      if(i == j)
      {
        for(int k = 0; k < j; k++)
          sum += pow(L(j, k), 2);
        if((m(j, j) - sum) < 0)
          throw PositiveDefError();
        L.get_elem(j, j) = sqrt(m(j, j) - sum);
      }
      else
      {
        //Evaluate L(i, j) using the diagonal of L
        for(int k = 0;  k < j; k++)
          sum += (L(i, k)*L(j, k));
        if(fabs(L(j, j)) < tolerance)
          throw SingularError();
        L.get_elem(i, j) = (m(i, j) - sum) / L(j, j);
      }
    }
  }

  //Forward
  Vector<T> y(n);
  for(int i = 0; i < n; i++)
  {
    T alpha = b[i];
    for(int j = 0; j < i; j++)
    {
      alpha -= L(i, j)*y[j];
    }
    y[i] = alpha/L(i, i);
  }

  //Backwards
  Upper_Matrix<T> LT(L.transpose());
  Vector<T> x(n);

  double ss = 0;
  for(int i = n-1; i >= 0; i--)
  {
    ss = 0;
    for(int j = i+1; j < n; j++)
    {
      ss += LT(i, j)*x[j];
    }
    if(fabs(LT(i, i)) < tolerance)
      throw SingularError();
    x[i] = (y[i] - ss) / LT(i, i);
  }

  return x;

}
