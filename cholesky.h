#ifndef CHOLESKY_H
#define CHOLESKY_H

/**
 *  @file Diagonal_Matrix.h
 *  @brief Class defintion for diagonal matrix
 *  @author Tanner Wendland
*/


#include "symmetric_matrix.h"
#include "vector.h"

template <typename T>
class Cholesky_Decomposition
{
public:
  //! Constructor
  /// \pre None
  /// \post Functor Cholesky object created
  Cholesky_Decomposition(){}
  //! Function Operator
  /// \pre Symmetric matrix rows (and cols) size match the size of b. M is not singular.
  /// \post Solves the system mx=b, returning x. Throws error if the size of the matrix's rows (and cols) dont match the szie of b. Throws error if M is singular.
  /// @param m of type const Symmetric_Matrix<T>&
  /// @param b of type const Vector<T>&
  Vector<T> operator()(const Symmetric_Matrix<T>& m, const Vector<T>& b) const;
};

#include "cholesky.hpp"

#endif
