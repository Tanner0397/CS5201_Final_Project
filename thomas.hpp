/**
 *  @file thomas.ppp
 *  @brief Class implmentation for thomas algorithm
 *  @author Tanner Wendland
*/

#include "tridiagonal_matrix.h"
#include "vector.h"
#include "DimensionError.h"
#include "SingularError.h"
#include <math.h>

template <typename T>
Vector<T> Thomas_Method<T>::operator()(const Tridiagonal_Matrix<T>& m, const Vector<T>& d) const
{
  //Stop divide by zero, but the tolerance must be VERY small
  double tolerance = 1.0E-30;

  if(m.num_rows() != d.size())
    throw DimensionError(m.num_rows());
  Vector<T> a = m.lower_diag();
  Vector<T> b = m.main_diag();
  Vector<T> c = m.upper_diag();
  int n = d.size();
  Vector<T> x(n);

  Vector<T> P(n);
  Vector<T> Q(n);
  x = Q;

  //Forward Pass
  int i = 0;
  double denom = b[i];
  if(fabs(denom) < tolerance)
    throw SingularError();

  P[i] = -c[i] / denom;
  Q[i] = d[i] / denom;
  for(i=1; i < n; i++)
  {
    denom = b[i]+a[i]*P[i-1];
    if(fabs(denom) < tolerance)
      throw SingularError();
    P[i] = -c[i] / denom;
    Q[i] = (d[i] - a[i]*Q[i-1]) / denom;
  }

  //Backwards Pass
  x[n-1] = Q[n-1];
  for(i=n-2; i >= 0; i--)
    x[i] = P[i]*x[i+1]+Q[i];

  return x;
}
