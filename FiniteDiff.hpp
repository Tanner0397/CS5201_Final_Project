/**
 *  @file fucniton.ppp
 *  @brief Class defintion for FiniteDiff
 *  @author Tanner Wendland
*/

template <typename T_ret, typename T_funcPtr>
FiniteDiff<T_ret, T_funcPtr>::FiniteDiff(int n, const Function<T_ret, T_funcPtr>& f)
{
  m_numDivs = n;
  m_func = f;
  initMatrix();
  initVector();
}

template <typename T_ret, typename T_funcPtr>
void FiniteDiff<T_ret, T_funcPtr>::initMatrix()
{
  int size = (m_numDivs-1)^2;
  m_matrix = Matrix(size, size);

  for(int i = 0; i < size; i++)
  {
    m_matrix.get_elem(i, i) = 1;
    if(i < size-1 && (i+1) % (m_numDivs-1) != 0)
    {
      m_matrix.get_elem(i+1, i) = -0.25;
      m_matrix.get_elem(i, i+1) = -0.25;
    }
    if(i < size-(m_numDivs-1))
    {
      m_matrix.get_elem(i+(m_numDivs-1), i) = -0.25;
      m_matrix.get_elem(i, i+(m+m_numDivs-1)) = 0.25;
    }
  }
  return;
}

template <typename T_ret, typename T_funcPtr>
void FiniteDiff<T_ret, T_funcPtr>::initVector()
{
  int size = (m_numDivs-1)^2;
  double h = 1.0/m_numDivs;
  double x = 0;
  double y = 0;
  bool l, b, r, t;

  m_vector = Vector(size);

  for(int i = 0; i < size, i++)
  {

  }
}
