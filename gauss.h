#ifndef GAUSS_H
#define GAUSS_H

/**
 *  @file gauss.h
 *  @brief Class defintion for gauss
 *  @author Tanner Wendland
*/

#include <iostream>
#include "abstract_matrix.h"
#include "vector.h"

template <typename T>
class Gauss {
public:
  //! Constructor
  /// \pre b is is of size m.m_rows. m best be square.
  /// \post guassian object is created.
  Gauss(){};
  //! Solves the system and returns the vector x
  /// \pre m must be nonsingular. m must be square. m_b must be the size of m_A.num_rows().
  /// \post Solves system of linear equations and returns the vectors x in Ax = b. Throws error if m is singular, if m is not a square matrix, and if b is not the size of m.num_rows()
  /// @param m of type const Abstract_Matrix<T>&
  /// @param b of type const Vector<T>& b
  Vector<T> operator()(const Abstract_Matrix<T>& m, Vector<T> b) const;
};

#include "gauss.hpp"

#endif
