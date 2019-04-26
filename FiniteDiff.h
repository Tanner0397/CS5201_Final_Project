/**
 *  @file fucniton.ppp
 *  @brief Class defintion for FiniteDiff
 *  @author Tanner Wendland
*/

#ifndef FINITEDIFF_H
#define FINITEDIFF_H

#include "gauss.h"
#include "abstract_matrix.h"
#include "matrix.h"
#include "symmetric_matrix.h"
#include "cholesky.h"

template <typename T_ret, typename T_funcPtr>
class FiniteDiff
{
private:
  Symmetric_Matrix<T_ret> m_matrix;
  Vector<T_ret> m_vector;
  int m_numDivs;
  Function<T_ret, T_funcPtr> m_func;
  Gauss<T_ret> m_gauss;
  Cholesky_Decomposition<T_ret> m_cholesky;
  void initMatrix();
  void initVector();
public:
  FiniteDiff(int n, const Function<T_ret, T_funcPtr>& f);
  void doGauss() const;
  void doCholesky() const;
};

#include "FiniteDiff.hpp"

#endif
