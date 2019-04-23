/**
 *  @file matrix.hpp
 *  @brief Class implmentation for matrix
 *  @author Tanner Wendland
*/

#include <utility>
#include "Array.h"
#include "vector.h"
#include "RangeError.h"
#include "DimensionError.h"
#include "MatrixDimError.h"

template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols)
{
  m_rows = rows;
  m_cols = cols;
  m_row_vectors = Array<Vector<T>>(m_rows);

  //Vectors must be initalized seperatly
  for(unsigned int i = 0; i < m_rows; i++)
  {
    m_row_vectors[i] = Vector<T>(m_cols);
  }
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& m)
{
  m_rows = std::move(m.m_rows);
  m_cols = std::move(m.m_cols);
  m_row_vectors = std::move(m.m_row_vectors);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
  m_rows = m.m_rows;
  m_cols = m.m_cols;
  m_row_vectors = m.m_row_vectors;
}

template <typename T>
Matrix<T>::Matrix(const Abstract_Matrix<T>& m)
{
  m_rows = m.num_rows();
  m_cols = m.num_cols();
  m_row_vectors = Array<Vector<T>>(m_rows);
  for(unsigned int i = 0; i < m_rows; i++)
  {
    m_row_vectors[i] = Vector<T>(m_cols);
    for(unsigned int j = 0; j < m_cols; j++)
    {
      m_row_vectors[i][j] = m(i, j);
    }
  }
}

template <typename T>
Vector<T>& Matrix<T>::operator[](unsigned int index)
{
  if(!(index >= 0 && index < m_row_vectors.size()))
    throw RangeError(index);
  return m_row_vectors[index];
}

template <typename T>
const Vector<T>& Matrix<T>::operator[](unsigned int index) const
{
  if(!(index >= 0 && index < m_row_vectors.size()))
    throw RangeError(index);
  return m_row_vectors[index];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Abstract_Matrix<T>& m) const
{
  if(m_rows != m.num_rows() || m_cols != m.num_cols())
    throw MatrixDimError(m_rows, m_cols);
  Matrix<T> result(m_rows, m_cols);
  for(unsigned int i = 0; i < m_rows; i++)
  {
    for(unsigned int j = 0; j < m_cols; j++)
    {
      result[i][j] = m_row_vectors[i][j] + m(i, j);
    }
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Abstract_Matrix<T>& m) const
{
  if(m_rows != m.num_rows() || m_cols != m.num_cols())
    throw MatrixDimError(m_rows, m_cols);
  Matrix<T> result(m_rows, m_cols);
  for(unsigned int i = 0; i < m_rows; i++)
  {
    for(unsigned int j = 0; j < m_cols; j++)
    {
      result[i][j] = m_row_vectors[i][j] - m(i, j);
    }
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const
{
  Matrix<T> result(m_rows, m_cols);
  for(unsigned int i = 0; i < m_rows; i++)
    result[i] = -m_row_vectors[i];
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(double factor) const
{
  Matrix<T> result(m_rows, m_cols);
  for(unsigned int i = 0; i < m_rows; i++)
    result[i] = m_row_vectors[i]*factor;
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
  Matrix<T> result(m_cols, m_rows);
  for(unsigned int i = 0; i < m_cols; i++)
    result[i] = col_vector(i);
  return result;
}

template <typename T>
Vector<T> Matrix<T>::col_vector(unsigned int index) const
{
  if(!(index >= 0 && index < m_cols))
    throw RangeError(index);
  Vector<T> result(m_rows);
  for(unsigned int i = 0; i < m_rows; i++)
    result[i] = m_row_vectors[i][index];
  return result;
}

template <typename T>
void Matrix<T>::set_col(unsigned int index, const Vector<T>& v)
{
  if(!(index >= 0 && index < m_cols))
    throw RangeError(index);
  if(v.size() != m_rows)
    throw DimensionError(v.size());
  for(unsigned int i = 0; i < m_rows; i++)
    m_row_vectors[i][index] = v[i];
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Abstract_Matrix<T>& m) const
{
  if(m_cols != m.num_rows())
    throw MatrixDimError(m.num_rows(), m_cols);
  Matrix<T> result(m_rows, m.num_cols());
  for(unsigned int i = 0; i < m_rows; i++)
  {
    for(unsigned int k = 0; k < m.num_cols(); k++)
    {
      //std::cout << m.col_vector(k) << std::endl;
      result.get_elem(i, k) = m_row_vectors[i]*m.col_vector(k);
    }
  }
  return result;
}

template <typename T>
Vector<T> Matrix<T>::operator*(const Vector<T>& v) const
{
  //use the code for matrix multiplcation, but with a matrix of v.size() x 1
  Matrix<T> temp(v.size(), 1);
  //Set the sole column to the vector passes, and then use the code for matrix multiplcaiton
  temp.set_col(0, v);
  //Return the only column vector
  return ((*this)*temp).col_vector(0);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> m)
{
  swap((*this), m);
  return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Abstract_Matrix<T>& m)
{
  m_rows = m.num_rows();
  m_cols = m.num_cols();
  m_row_vectors = Array<Vector<T>>(m_rows);
  for(unsigned int i = 0; i < m_rows; i++)
  {
    m_row_vectors[i] = Vector<T>(m_cols);
    for(unsigned int j = 0; j < m_cols; j++)
    {
      m_row_vectors[i][j] = m(i, j);
    }
  }
  return (*this);
}

template <typename T>
unsigned int Matrix<T>::num_rows() const
{
  return m_rows;
}

template <typename T>
unsigned int Matrix<T>::num_cols() const
{
  return m_cols;
}

template <typename T>
T Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
  if(!(row >= 0 && row < m_rows))
    throw RangeError(row);
  if(!(col >= 0 && col < m_cols))
    throw RangeError(col);
  return m_row_vectors[row][col];
}

template <typename T>
T& Matrix<T>::get_elem(unsigned int row, unsigned int col)
{
  if(!(row >= 0 && row < m_rows))
    throw RangeError(row);
  if(!(col >= 0 && col < m_cols))
    throw RangeError(col);
  return m_row_vectors[row][col];
}

template <typename T>
Lower_Matrix<T> Matrix<T>::lower_triangle() const
{
  if(m_rows != m_cols)
    throw MatrixDimError(m_rows, m_cols);
  Lower_Matrix<T> temp(m_rows);
  for(unsigned int j = 0; j < m_cols; j++)
  {
    for(unsigned int i = j; i < m_rows; i++)
    {
      temp.get_elem(i, j) = operator()(i, j);
    }
  }
  return temp;
}

template <typename T>
Upper_Matrix<T> Matrix<T>::upper_triangle() const
{
  if(m_rows != m_cols)
    throw MatrixDimError(m_rows, m_cols);
  Upper_Matrix<T> temp(m_rows);
  for(unsigned int j = 0; j < m_cols; j++)
  {
    for(unsigned int i = j; i < m_rows; i++)
    {
      temp.get_elem(j, i) = operator()(j, i);
    }
  }
  return temp;
}
