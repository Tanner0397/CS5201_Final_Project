/**
 *  @file diagonal_matrix.hpp
 *  @brief Class defintion for upper matrix
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
Diagonal_Matrix<T>::Diagonal_Matrix(unsigned int n)
{
  m_n = n;
  m_elements = Array<T>(n);
}

template <typename T>
Diagonal_Matrix<T>::Diagonal_Matrix(Diagonal_Matrix<T>&& m)
{
  m_n = std::move(m.m_n);
  m_elements = std::move(m.m_elements);
}

template <typename T>
Diagonal_Matrix<T>::Diagonal_Matrix(const Diagonal_Matrix<T>& m)
{
  m_n = m.m_n;
  m_elements = m.m_elements;
}

template <typename T>
Diagonal_Matrix<T>::Diagonal_Matrix(const Abstract_Matrix<T>& m)
{
  if(m.num_rows() != m.num_cols())
    throw MatrixDimError(m.num_rows(), m.num_cols());
  m_n = m.num_cols();
  m_elements = Array<T>(m_n);
  double tolerance = 0.005;
  for(unsigned int i = 0; i < m_n; i++)
  {
    for(unsigned int j = 0; j < m_n; j++)
    {
      if(i != j && fabs(m(i, j)) >= tolerance)
        throw ModificationError();
      else
      {
        m_elements[i] = m(i, j);
      }
    }
  }
}

template <typename T>
Diagonal_Matrix<T> Diagonal_Matrix<T>::operator+(const Diagonal_Matrix<T>& m) const
{
  if(m_n != m.m_n)
    throw MatrixDimError(m_n, m_n);
  Diagonal_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    temp.m_elements[i] = m_elements[i] + m.m_elements[i];
  return temp;
}

template <typename T>
Matrix<T> Diagonal_Matrix<T>::operator+(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows() || m_n != m.num_cols())
    throw MatrixDimError(m_n, m_n);
  Matrix<T> temp(m_n, m_n);
  for(unsigned int i = 0; i < m_n; i++)
    for(unsigned int j = 0; j < m_n; j++)
      temp.get_elem(i, j) = operator()(i, j) + m(i, j);
  return temp;
}

template <typename T>
Diagonal_Matrix<T> Diagonal_Matrix<T>::operator-(const Diagonal_Matrix<T>& m) const
{
  return (*this)+(-m);
}

template <typename T>
Matrix<T> Diagonal_Matrix<T>::operator-(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows() || m_n != m.num_cols())
    throw MatrixDimError(m_n, m_n);
  Matrix<T> temp(m_n, m_n);
  for(unsigned int i = 0; i < m_n; i++)
    for(unsigned int j = 0; j < m_n; j++)
      temp.get_elem(i, j) = operator()(i, j) - m(i, j);
  return temp;
}

template <typename T>
Diagonal_Matrix<T> Diagonal_Matrix<T>::operator-() const
{
  Diagonal_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    temp.m_elements[i] = -m_elements[i];
  return temp;
}

template <typename T>
Diagonal_Matrix<T> Diagonal_Matrix<T>::operator*(double factor) const
{
  Diagonal_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    temp.m_elements[i] = factor*m_elements[i];
  return temp;
}

template <typename T>
Diagonal_Matrix<T> Diagonal_Matrix<T>::operator*(const Diagonal_Matrix<T>& m) const
{
  if(m_n != m.m_n)
    throw MatrixDimError(m_n, m_n);
  Diagonal_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    temp.m_elements[i] = m_elements[i]*m.m_elements[i];
  return temp;
}

template <typename T>
Matrix<T> Diagonal_Matrix<T>::operator*(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows())
    throw MatrixDimError(m.num_rows(), m_n);
  Matrix<T> result(m_n, m.num_cols());
  for(unsigned int i = 0; i < m_n; i++)
  {
    for(unsigned int j = 0; j < m.num_cols(); j++)
    {
      result.get_elem(i, j) += operator()(j, j)* m(j, i);
    }
  }
  return result;
}

template <typename T>
Diagonal_Matrix<T> Diagonal_Matrix<T>::transpose() const
{
  return (*this);
}

template <typename T>
Vector<T> Diagonal_Matrix<T>::operator*(const Vector<T>& v) const
{
  if(m_n != v.size())
    throw DimensionError(m_n);
  Vector<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    temp[i] = v[i]*m_elements[i];
  return temp;
}

template <typename T>
Diagonal_Matrix<T>& Diagonal_Matrix<T>::operator=(Diagonal_Matrix<T> m)
{
  swap((*this), m);
  return (*this);
}

template <typename T>
Vector<T> Diagonal_Matrix<T>::col_vector(unsigned int index) const
{
  if(!(index >= 0 && index < m_n))
    throw RangeError(index);
  Vector<T> temp(m_n);
  //The nth column vector will have it's only non-zero entry in the nth position of the vector
  temp[index] = m_elements[index];
  return temp;
}

template <typename T>
unsigned int Diagonal_Matrix<T>::num_rows() const
{
  return m_n;
}

template <typename T>
unsigned int Diagonal_Matrix<T>::num_cols() const
{
  return m_n;
}

template <typename T>
T Diagonal_Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
  if(!(row >= 0 && row < m_n))
    throw RangeError(row);
  if(!(col >= 0 && col < m_n))
    throw RangeError(col);

  if(row != col)
    return 0;

  return m_elements[row];
}

template <typename T>
T& Diagonal_Matrix<T>::get_elem(unsigned int row, unsigned int col)
{
  if(!(row >= 0 && row < m_n))
    throw RangeError(row);
  if(!(col >= 0 && col < m_n))
    throw RangeError(col);

  if(row != col)
    throw ModificationError();

  return m_elements[row];
}
