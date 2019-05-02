/**
 *  @file FiniteDiff.hpp
 *  @brief Class defintion for FiniteDiff
 *  @author Tanner Wendland
 *  @author Alex Sanchez
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
  m_matrix = Symmetric_Matrix<T_ret>(size);

  for(int i = 0; i < size; i++)
  {
    m_matrix.get_elem(i, i) = 1;
    if(i < size-1 && ((i+1) % (m_numDivs-1) != 0))
    {
      m_matrix.get_elem(i, i+1) = -0.25;
    }
    if(i < size-(m_numDivs-1))
    {
      m_matrix.get_elem(i+(m_numDivs-1), i) = -0.25;
    }
  }
  return;
}

template <typename T_ret, typename T_funcPtr>
void FiniteDiff<T_ret, T_funcPtr>::initVector()
{
  int size = static_cast<int>(pow(m_numDivs-1, 2));
  //side lengths pf domain are both PI long
  double h = M_PI/m_numDivs;
  double x = 0;
  double y = 0;
  //bools for stencil
  //left, down, right , up
  bool l, d, r, u;

  m_vector = Vector<T_ret>(size);

  for(int i = 0; i < size; i++)
  {
    x+=h;
    //wrap
    if(!(i % (m_numDivs-1)))
    {
      x = h;
      y += h;
    }
    l = (x == h);
    d = (y == h);
    //top of the square used in PI, also the right side
    r = (x == M_PI-h);
    u = (y == M_PI-h);

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
  //std::cout << m_vector << std::endl;
  return;
}

template <typename T_ret, typename T_funcPtr>
void FiniteDiff<T_ret, T_funcPtr>::doGauss() const
{
  Vector<T_ret> vec(m_gauss(m_matrix, m_vector));
  for(int i = m_numDivs-1; i > 0; i--)
  {
    for(int j = 0; j < m_numDivs-1; j++)
    {
      std::cout << std::fixed << std::setprecision(8) << vec[(i-1)*(m_numDivs-1)+j] << " ";
    }
    std::cout << std::endl;
  }
}

template <typename T_ret, typename T_funcPtr>
void FiniteDiff<T_ret, T_funcPtr>::doCholesky() const
{
  Vector<T_ret> vec(m_cholesky(m_matrix, m_vector));
  //std::cout << vec << std::endl;
  for(int i = m_numDivs-1; i > 0; i--)
  {
    for(int j = 0; j < m_numDivs-1; j++)
    {
      std::cout << std::fixed << std::setprecision(8) << vec[(i-1)*(m_numDivs-1)+j] << " ";
    }
    std::cout << std::endl;
  }
}

template <typename T_ret, typename T_funcPtr>
void FiniteDiff<T_ret, T_funcPtr>::tupleOutput() const
{
  double x = 0.0;
  double y = 0.0;
  double h = M_PI/m_numDivs;
  Vector<T_ret> vec(m_cholesky(m_matrix, m_vector));
  for(unsigned int i = 0; i < pow(m_numDivs-1, 2); i++)
  {
    x += h;
    if(!(i % (m_numDivs-1)))
    {
      x = h;
      y += h;
    }
    std::cout << std::fixed << std::setprecision(8) << x << ", " << y << ", " << vec[i] << std::endl;
  }
  return;
}
