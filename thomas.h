#ifndef THOMAS_H
#define THOMAS_H

/**
 *  @file thomas.h
 *  @brief Class defintion for thomas algorithm
 *  @author Tanner Wendland
*/

#include "tridiagonal_matrix.h"
#include "vector.h"

template <typename T>
class Thomas_Method
{
public:
  //! Constructor
  /// \pre None
  /// \post Function object for Thomas algorithm is created
  Thomas_Method(){}
  //! Function Operator
  /// \pre m's rows and cols's must be the same size of d. M is not singular.
  /// \post Solves the system mx=b, returning x. Throws error if m's rows and cols are not the same size of d. Throws error of m is singular.
  /// @param m of type const Tridiagonal_Matrix<T>&
  /// @param d of type const Vector<T>&
  Vector<T> operator()(const Tridiagonal_Matrix<T>& m, const Vector<T>& d) const;
};

#include "thomas.hpp"

#endif
