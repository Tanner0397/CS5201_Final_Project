/**
 *  @file lower_matrix.hpp
 *  @brief Class implmentation for lower matrix
 *  @author Tanner Wendland
*/

#include <utility>
#include "Array.h"
#include "vector.h"
#include "RangeError.h"
#include "DimensionError.h"
#include "MatrixDimError.h"
#include "ModificationError.h"
#include "upper_matrix.h"

template <typename T>
Lower_Matrix<T>::Lower_Matrix(unsigned int n)
{
  m_n = n;
  m_total_elements = n*(n+1)/2;
  m_elements = Array<T>(m_total_elements);
}

template <typename T>
Lower_Matrix<T>::Lower_Matrix(const Lower_Matrix<T>& m)
{
  m_n = m.m_n;
  m_total_elements = m.m_total_elements;
  m_elements = m.m_elements;
}

template <typename T>
Lower_Matrix<T>::Lower_Matrix(const Abstract_Matrix<T>& m)
{
  if(m.num_rows() != m.num_cols())
    throw MatrixDimError(m.num_rows(), m.num_cols());
  m_n = m.num_rows();
  m_total_elements = m_n*(m_n+1)/2;
  m_elements = Array<T>(m_total_elements);
  int counter = 0;
  for(unsigned int i = 0; i < m.num_rows(); i++)
  {
    for(unsigned int j = 0; j < m.num_cols(); j++)
    {
      if(i < j && m(i, j) != 0)
        throw ModificationError();
      if(i >= j)
      {
        m_elements[i] = m(i,j);
        counter++;
      }
    }
  }
}

template <typename T>
Lower_Matrix<T>::Lower_Matrix(Lower_Matrix<T>&& m)
{
  m_n = std::move(m.m_n);
  m_total_elements = std::move(m.m_n);
  m_elements = std::move(m.m_elements);
}

template <typename T>
Lower_Matrix<T> Lower_Matrix<T>::operator+(const Lower_Matrix<T>& m) const
{
  if(m_n != m.m_n)
    throw MatrixDimError(m_n, m_n);
  Lower_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_total_elements; i++)
    temp.m_elements[i] = m_elements[i] + m.m_elements[i];
  return temp;
}

template <typename T>
Matrix<T> Lower_Matrix<T>::operator+(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows() || m_n != m.num_cols())
    throw MatrixDimError(m_n, m_n);
  Matrix<T> temp(m_n, m_n);
  for(unsigned int i = 0; i < m.num_rows(); i++)
  {
    for(unsigned int j = 0; j < m.num_cols(); j++)
    {
      temp.get_elem(i, j) = operator()(i, j) + m(i, j);
    }
  }
  return temp;
}

template <typename T>
Vector<T> Lower_Matrix<T>::col_vector(unsigned int index) const
{
  Vector<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    temp[i] = operator()(i, index);
  return temp;
}

template <typename T>
Lower_Matrix<T> Lower_Matrix<T>::operator-(const Lower_Matrix<T>& m) const
{
  return (*this) + (-m);
}

template <typename T>
Lower_Matrix<T> Lower_Matrix<T>::operator-() const
{
  Lower_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_total_elements; i++)
    temp.m_elements[i] = -m_elements[i];
  return temp;
}

template <typename T>
Matrix<T> Lower_Matrix<T>::operator-(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows() || m_n != m.num_cols())
    throw MatrixDimError(m_n, m_n);
  Matrix<T> temp(m_n, m_n);
  for(unsigned int i = 0; i < m.num_rows(); i++)
  {
    for(unsigned int j = 0; j < m.num_cols(); j++)
    {
      temp.get_elem(i, j) = operator()(i, j) - m(i, j);
    }
  }
  return temp;
}

template <typename T>
Lower_Matrix<T> Lower_Matrix<T>::operator*(double factor) const
{
  Lower_Matrix<T> temp(m_n);
  for(unsigned int i = 0; i < m_total_elements; i++)
    temp.m_elements[i] = m_elements[i]*factor;
  return temp;
}

template <typename T>
Lower_Matrix<T> Lower_Matrix<T>::operator*(const Lower_Matrix<T>& m) const
{
  if(m_n != m.m_n)
    throw MatrixDimError(m_n, m_n);
  Lower_Matrix<T> temp(m_n);
  //Multiply only using the elements on the top part of the matrix with the main diagonal
  for(unsigned int j = 0; j < m_n; j++)
  {
    for(unsigned int i = 0; i <= j; i++)
    {
      for(unsigned int k = i; k <= j; k++)
      {
        temp.get_elem(j, i) += operator()(j, k) * m(k, i);
      }
    }
  }
  return temp;
}

template <typename T>
Matrix<T> Lower_Matrix<T>::operator*(const Abstract_Matrix<T>& m) const
{
  if(m_n != m.num_rows())
    throw MatrixDimError(m.num_rows(), m_n);
  Matrix<T> result(m_n, m.num_cols());
  for(unsigned int i = 0; i < m_n; i++)
  {
    for(unsigned int j = 0; j < m.num_cols(); j++)
    {
      for(unsigned int k = 0; k < j+1; k++)
      {
        result.get_elem(i, j) += operator()(j, k)* m(k, i);
      }
    }
  }
  return result;
}

template <typename T>
Vector<T> Lower_Matrix<T>::operator*(const Vector<T>& v) const
{
  if(m_n != v.size())
    throw MatrixDimError(m_n, m_n);
  Vector<T> temp(m_n);
  for(unsigned int j = 0; j < m_n; j++)
  {
    for(unsigned int i = j; i < m_n; i++)
    {
      temp[i] += operator()(i, j)*v[j];
    }
  }
  return temp;
}

template <typename T>
Lower_Matrix<T>& Lower_Matrix<T>::operator=(Lower_Matrix<T> m)
{
  swap((*this), m);
  return *this;
}

template <typename T>
unsigned int Lower_Matrix<T>::num_rows() const
{
  return m_n;
}

template <typename T>
unsigned int Lower_Matrix<T>::num_cols() const
{
  return m_n;
}

template <typename T>
T Lower_Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
  if(!(row >= 0 && row < m_n))
    throw RangeError(row);
  if(!(col >= 0 && col < m_n))
    throw RangeError(col);

  if(row < col)
    return 0;

  //Convert the rows and cols into an index for the array of elements.
  int index = row*(row+1)/2+col;
  return m_elements[index];
}

template <typename T>
T& Lower_Matrix<T>::get_elem(unsigned int row, unsigned int col)
{
  if(!(row >= 0 && row < m_n))
    throw RangeError(row);
  if(!(col >= 0 && col < m_n))
    throw RangeError(col);


  //Dont get this since it could modified
  if(row < col)
    throw ModificationError();

  //Convert the rows and cols into an index for the array of elements.
  int index = row*(row+1)/2+col;
  return m_elements[index];
}

template <typename T>
Upper_Matrix<T> Lower_Matrix<T>::transpose() const
{
  Upper_Matrix<T> temp(m_n);
  for(unsigned int j = 0; j < m_n; j++)
  {
    for(unsigned int i = 0; i <= j; i++)
    {
      temp.get_elem(i, j) = operator()(j, i);
    }
  }
  return temp;
}
