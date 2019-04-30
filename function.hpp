/**
 *  @file function.hpp
 *  @brief Class implmentation for fucntion
 *  @author Tanner Wendland
*/

template <typename T_ret, typename T_funcPtr>
Function<T_ret, T_funcPtr>::Function(T_funcPtr f)
{
  m_func = f;
}

template <typename T_ret, typename T_funcPtr>
T_ret Function<T_ret, T_funcPtr>::operator()(const T_ret& x, const T_ret& y)
{
  return m_func(x, y);
}
