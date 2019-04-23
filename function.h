/**
 *  @file fucniton.ppp
 *  @brief Class defintion for fucntion
 *  @author Tanner Wendland
*/

//Function wrapper pointer for a pointer that takes in 2 parameters

#ifndef FUNCTION_H
#define FUNCTION_H

template <typename T_ret, typename T_funcPtr>
class Function
{
private:
  T_funcPtr m_func;
public:
  Function(){m_func = nullptr;}
  Function(T_funcPtr f);
  T_ret operator()(const T_ret& x, const T_ret& y);
};

#include "function.hpp"
#endif
