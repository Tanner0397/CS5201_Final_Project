/**
 *  @file FiniteDiff.h
 *  @brief Class defintion for FiniteDiff
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#ifndef FINITEDIFF_H
#define FINITEDIFF_H

#include "gauss.h"
#include "abstract_matrix.h"
#include "matrix.h"
#include "symmetric_matrix.h"
#include "cholesky.h"

///
/// \class FiniteDiff
/// \brief This class implements the finite difference method using both
///        gaussian elimination and cholesky decomposition
///

template <typename T_ret, double T_func(double, double)>
class FiniteDiff
{
private:
  Symmetric_Matrix<T_ret> m_matrix;
  Vector<T_ret> m_vector;
  int m_numDivs;
  //Function<T_ret, T_funcPtr> m_func;
  Gauss<T_ret> m_gauss;
  Cholesky_Decomposition<T_ret> m_cholesky;
  void initMatrix();
  void initVector();
public:
  ///
  /// \fn FiniteDiff(int n, const Function<T_ret, T_funcPtr>& f)
  /// \brief constructor
  /// \pre none
  /// \post m_numDivs = n and m_func = f
  /// \param n is the desired number of divisions
  /// \param f is the funciton
  ///
  FiniteDiff(int n);

  ///
  /// \fn void doGauss() const
  /// \brief does gaussian elimination on the matrix
  /// \pre gaussian elimination must be valid for the given matrix
  /// \post gaussian elimination is performed on the matrix
  ///
  void doGauss() const;

  ///
  /// \fn void doCholesky() const
  /// \brief does cholesky decomposition on the matrix
  /// \pre cholesky decomposition must be valid for the given matrix
  /// \post cholesky decomposition is performed on the matrix
  ///
  void doCholesky() const;
};

#include "FiniteDiff.hpp"

#endif
