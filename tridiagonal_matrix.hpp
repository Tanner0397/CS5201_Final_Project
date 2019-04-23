/**
 *  @file tridiagonal_matrix.hpp
 *  @brief Class defintion for tridiagonal matrix
 *  @author Tanner Wendland
*/

#include <utility>
#include <cmath>
#include "Array.h"
#include "vector.h"
#include "RangeError.h"
#include "DimensionError.h"
#include "MatrixDimError.h"
#include "ModificationError.h"

template <typename T>
Tridiagonal_Matrix<T>::Tridiagonal_Matrix(unsigned int n)
{
  m_n = n;
  m_total_elements = 3*n-2;
  m_elements = Array<T>(m_total_elements);
}

template <typename T>
Tridiagonal_Matrix<T>::Tridiagonal_Matrix(Tridiagonal_Matrix<T>&& m)
{
  m_n = std::move(m.m_n);
  m_total_elements = std::move(m.m_total_elements);
  m_elements = std::move(m.m_elements);
}

template <typename T>
Tridiagonal_Matrix<T>::Tridiagonal_Matrix(const Tridiagonal_Matrix<T>& m)
{
  m_n = m.m_n;
  m_total_elements = m.m_total_elements;
  m_elements = m.m_elements;
}

template <typename T>
Tridiagonal_Matrix<T>::Tridiagonal_Matrix(const Abstract_Matrix<T>& m)
{
  if(m.num_rows() != m.num_cols())
    throw MatrixDimError(m.num_rows(), m.num_cols());
  m_n = m.num_cols();
  m_total_elements = 3*m_n-2;
  m_elements = Array<T>(m_total_elements);
  double tolerance = 0.005;
  for(unsigned int i = 0; i < m_n; i++)
  {
    for(unsigned int j = 0; j < m_n; j++)
    {
      if((i > j + 1 || j > i + 1) && fabs(m(i, j)) >= tolerance)
      {
        throw ModificationError();
      }
      else if(!(i > j + 1 || j > i + 1))
      {
        get_elem(i, j) = m(i, j);
      }
    }
  }
}

template <typename T>
Tridiagonal_Matrix<T> Tridiagonal_Matrix<T>::operator+(const Tridiagonal_Matrix<T>& m) const
{
  if(m_n != m.m_n)
    throw MatrixDimError(m_n, m_n);
  Tridiagonal_Matrix<T> temp(m_total_elements);
  for(unsigned int i = 0; i < m_n; i++)
    temp.m_elements[i] = m_elements[i] + m.m_elements[i];
  return temp;
}

template <typename T>
Matrix<T> Tridiagonal_Matrix<T>::operator+(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows() || m_n != m.num_cols())
    throw MatrixDimError(m_n, m_n);
  Matrix<T> temp(m_n, m_n);
  for(unsigned int i = 0; i < m_total_elements; i++)
    for(unsigned int j = 0; j < m_total_elements; j++)
      temp.get_elem(i, j) = operator()(i, j) + m(i, j);
  return temp;
}

template <typename T>
Tridiagonal_Matrix<T> Tridiagonal_Matrix<T>::operator-(const Tridiagonal_Matrix<T>& m) const
{
  return (*this)+(-m);
}

template <typename T>
Matrix<T> Tridiagonal_Matrix<T>::operator-(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows() || m_n != m.num_cols())
    throw MatrixDimError(m_n, m_n);
  Matrix<T> temp(m_n, m_n);
  for(unsigned int i = 0; i < m_total_elements; i++)
    for(unsigned int j = 0; j < m_total_elements; j++)
      temp.get_elem(i, j) = operator()(i, j) - m(i, j);
  return temp;
}

template <typename T>
Tridiagonal_Matrix<T> Tridiagonal_Matrix<T>::operator-() const
{
  Tridiagonal_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_total_elements; i++)
    temp.m_elements[i] = -m_elements[i];
  return temp;
}

template <typename T>
Tridiagonal_Matrix<T> Tridiagonal_Matrix<T>::operator*(double factor) const
{
  Tridiagonal_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_total_elements; i++)
    temp.m_elements = factor*m_elements[i];
  return temp;
}

template <typename T>
Matrix<T> Tridiagonal_Matrix<T>::operator*(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows())
    throw MatrixDimError(m.num_rows(), m_n);
  Matrix<T> result(m_n, m.num_cols());
  for(unsigned int i = 0; i < m_n; i++)
  {
    for(unsigned int j = 0; j < m.num_cols(); j++)
    {
      for(unsigned int k = 0; k < m_n; k++)
      {
        result.get_elem(i, j) += operator()(i, k)* m(k, j);
      }
    }
  }
  return result;
}

template <typename T>
Tridiagonal_Matrix<T> Tridiagonal_Matrix<T>::transpose() const
{
  Tridiagonal_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    for(unsigned int j = 0; j < m_n; j++)
      if(i <= j+1 && j <= i+1)
        temp.get_elem(i, j) = operator()(j, i);
  return temp;
}

template <typename T>
Vector<T> Tridiagonal_Matrix<T>::operator*(const Vector<T>& v) const
{
  if(m_n != v.size())
    throw MatrixDimError(m_n, m_n);
  Matrix<T> temp(v.size(), 1);
  temp.set_col(0, v);
  return ((*this)*temp).col_vector(0);
}

template <typename T>
Tridiagonal_Matrix<T>& Tridiagonal_Matrix<T>::operator=(Tridiagonal_Matrix<T> m)
{
  swap((*this), m);
  return (*this);
}

template <typename T>
Vector<T> Tridiagonal_Matrix<T>::col_vector(unsigned int index) const
{
  if(!(index >= 0 && index < m_n))
    throw RangeError(index);
  Vector<T> temp(m_n);
  //The nth column vector will have it's only non-zero entry in the nth position of the vector
  for(unsigned int i = 0; i < m_n; i++)
    temp[i] = operator()(i, index);
  return temp;
}

template <typename T>
unsigned int Tridiagonal_Matrix<T>::num_rows() const
{
  return m_n;
}

template <typename T>
unsigned int Tridiagonal_Matrix<T>::num_cols() const
{
  return m_n;
}

template <typename T>
T Tridiagonal_Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
  if(!(row >= 0 && row < m_n))
    throw RangeError(row);
  if(!(col >= 0 && col < m_n))
    throw RangeError(col);

  if(row > col+1 || col > row+1)
    return 0;

  unsigned int index = row*3;
  if(row > col)
    index--;
  else if(row < col)
    index++;

  return m_elements[index];
}

template <typename T>
T& Tridiagonal_Matrix<T>::get_elem(unsigned int row, unsigned int col)
{
  if(!(row >= 0 && row < m_n))
    throw RangeError(row);
  if(!(col >= 0 && col < m_n))
    throw RangeError(col);

  if(row > col+1 || col > row+1)
    throw ModificationError();

  unsigned int index = row*3;
  if(row > col)
    index--;
  else if(row < col)
    index++;

  return m_elements[index];
}

template <typename T>
Vector<T> Tridiagonal_Matrix<T>::main_diag() const
{
  Vector<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
  {
    temp[i] = operator()(i, i);
  }
  return temp;
}

template <typename T>
Vector<T> Tridiagonal_Matrix<T>::lower_diag() const
{
  Vector<T> temp(m_n);
  for(unsigned int i = 1; i < m_n; i++)
  {
    temp[i] = operator()(i, i-1);
  }
  return temp;
}

template <typename T>
Vector<T> Tridiagonal_Matrix<T>::upper_diag() const
{
  Vector<T> temp(m_n);
  for(unsigned int i = 0; i < m_n-1; i++)
    temp[i] = operator()(i, i+1);
  return temp;
}
