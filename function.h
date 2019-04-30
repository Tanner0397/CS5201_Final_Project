/**
 *  @file function.h
 *  @brief Class defintion for function
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

//Function wrapper pointer for a pointer that takes in 2 parameters

#ifndef FUNCTION_H
#define FUNCTION_H

///
/// \class Function
/// \brief This class acts as a function by using operator()
///

template <typename T_ret, typename T_funcPtr>
class Function
{
private:
  T_funcPtr m_func;
public:
  ///
  /// \fn Function
  /// \brief default constructor
  /// \pre none
  /// \post m_func = nullptr
  ///
  Function(){m_func = nullptr;}

  ///
  /// \fn Function(T_funcPtr f)
  /// \brief constructor
  /// \pre none
  /// \post m_func = f
  /// \param f of type T_funcPtr
  ///
  Function(T_funcPtr f);

  ///
  /// \fn T_ret operator()(const T_ret& x, const T_ret& y)
  /// \brief overloaded operator() to access the function f
  /// \pre none
  /// \post m_func(x, y) returned
  /// \return m_func(x, y)
  /// \param x is the x value for m_func
  /// \param y is the y value for m_func
  ///
  T_ret operator()(const T_ret& x, const T_ret& y);
};

#include "function.hpp"
#endif
