#ifndef GAUSS_H
#define GAUSS_H

/**
 *  @file gauss.h
 *  @brief Class defintion for gauss
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include <iostream>
#include "abstract_matrix.h"
#include "symmetric_matrix.h"
#include "vector.h"

///
/// \class Gauss
/// \brief This class is the gaussian elimination algorithm implemented as a class
///

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

  //! Solves the system and returns the vector x
  /// \pre m must be nonsingular. m must be square. m_b must be the size of m_A.num_rows().
  /// \post Solves system of linear equations and returns the vectors x in Ax = b. Throws error if m is singular, if m is not a square matrix, and if b is not the size of m.num_rows()
  /// @param matrix of type const Symmetric_Matrix<T>&
  /// @param b of type const Vector<T>& b
  Vector<T> operator()(Symmetric_Matrix<T>& matrix, Vector<T> b) const;
};

#include "gauss.hpp"

#endif
