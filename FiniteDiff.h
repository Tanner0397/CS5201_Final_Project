/**
 *  @file fucniton.ppp
 *  @brief Class defintion for FiniteDiff
 *  @author Tanner Wendland
*/

#ifndef FINITEDIFF_H
#DEFINE FINITEDIFF_H

#include "gauss.h"
#include "abstract_matrix.h"
#include "matrix.h"
#include "symmetric_matrix.h"

template <template T_ret, class T_funcPtr>
class Finite_Diff
{
private:
  Matrix<T_ret> m_matrix;
  Vector<T_ret> m_vector;
  int m_numDivs;
  Function<T_ret, T_funcPtr> m_func;
  Guass<T_ret> m_gauss;
  void initMatrix();
  void initVector();
public:
  Finite_Diff(int n, const Function<T_ret, T_funcPtr>& f);
  Vector<T_ret> compute();
};

#include "Finite_Diff.hpp"

#endif
