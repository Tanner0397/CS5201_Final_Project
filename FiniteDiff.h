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

template <typename T_ret, typename T_funcPtr>
class FiniteDiff
{
private:
  Matrix<T_ret> m_matrix;
  Vector<T_ret> m_vector;
  int m_numDivs;
  Function<T_ret, T_funcPtr> m_func;
  Gauss<T_ret> m_gauss;
  void initMatrix();
  void initVector();
public:
  FiniteDiff(int n, const Function<T_ret, T_funcPtr>& f);
  Vector<T_ret> doGauss() const;
};

#include "FiniteDiff.hpp"

#endif
