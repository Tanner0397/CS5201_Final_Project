/**
 *  @file FiniteDiff.hpp
 *  @brief Class defintion for FiniteDiff
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include <math.h>

template <typename T_ret, double T_func(double, double)>
FiniteDiff<T_ret, T_func>::FiniteDiff(int n)
{
  m_numDivs = n;
  initMatrix();
  initVector();
}

template <typename T_ret, double T_func(double, double)>
void FiniteDiff<T_ret, T_func>::initMatrix()
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

template <typename T_ret, double T_func(double, double)>
void FiniteDiff<T_ret, T_func>::initVector()
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
      m_vector[i]+=T_func(x-h, y);
    if(d)
      m_vector[i]+=T_func(x, y-h);
    if(r)
      m_vector[i]+=T_func(x+h, y);
    if(u)
      m_vector[i]+=T_func(x, y+h);
  }
  m_vector = m_vector * 0.25;
  //std::cout << m_vector << std::endl;
  return;
}

template <typename T_ret, double T_func(double, double)>
void FiniteDiff<T_ret, T_func>::doGauss() const
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

template <typename T_ret, double T_func(double, double)>
void FiniteDiff<T_ret, T_func>::doCholesky() const
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
