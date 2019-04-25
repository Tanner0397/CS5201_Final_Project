/**
 *  @file fucniton.ppp
 *  @brief Class defintion for FiniteDiff
 *  @author Tanner Wendland
*/

#include <math.h>

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
  int size = static_cast<int>(pow(m_numDivs-1, 2));
  //Penta Diagonal Matrix
  m_matrix = Matrix<T_ret>(size, size);
  double delta_x = 1.0/m_numDivs;
  double delta_y = 1.0/m_numDivs;

  for(int i = 0; i < size; i++)
  {
    m_matrix.get_elem(i, i) = -2*(1/pow(delta_x, 2) + 1/pow(delta_y, 2));
    if(i < size-1 && ((i+1) % (m_numDivs-1) != 0))
    {
      m_matrix.get_elem(i+1, i) = 1/pow(delta_x, 2);
      m_matrix.get_elem(i, i+1) = 1/pow(delta_x, 2);
    }
    if(i < size-(m_numDivs-1))
    {
      m_matrix.get_elem(i+(m_numDivs-1), i) = 1/pow(delta_y, 2);
      m_matrix.get_elem(i, i+(m_numDivs-1)) = 1/pow(delta_y, 2);
    }
  }
  return;
}

template <typename T_ret, typename T_funcPtr>
void FiniteDiff<T_ret, T_funcPtr>::initVector()
{
  int size = static_cast<int>(pow(m_numDivs-1, 2));
  double h = 1.0/m_numDivs;
  double x = 0;
  double y = 0;
  //boosls for stencil
  //left, down, right , up
  bool l, d, r, u;

  m_vector = Vector<T_ret>(size);

  for(int i = 0; i < size; i++)
  {
    x+=h;
    if(!(i % (m_numDivs-1)))
    {
      x = h;
      y += h;
    }
    l = (x == h);
    d = ( y== h);
    r = (x == 1-h);
    u = (y == 1-h);

    //Compute
    if(l)
      m_vector[i]+=m_func(x-h, y);
    if(d)
      m_vector[i]+=m_func(x, y-h);
    if(r)
      m_vector[i]+=m_func(x+h, y);
    if(u)
      m_vector[i]+=m_func(x, y+h);
  }
  m_vector = m_vector * 0.25;
  return;
}

template <typename T_ret, typename T_funcPtr>
Vector<T_ret> FiniteDiff<T_ret, T_funcPtr>::doGauss() const
{
  return m_gauss(m_matrix, m_vector);
}
