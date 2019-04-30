/**
 *  @file Array.hpp
 *  @brief implementation of array class
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include <utility>
#include "RangeError.h"

template <typename T>
Array<T>::Array()
{
  m_n = 0;
  m_data = nullptr;
}

template <typename T>
Array<T>::Array(unsigned int n)
{
  m_n = n;
  m_data = std::make_unique<T[]>(n);
}

template <typename T>
Array<T>::Array(const Array& ary)
{
  m_n = ary.m_n;
  //If we're constructing, we dont need to delete m_data;
  m_data = std::make_unique<T[]>(m_n);
  for(unsigned int i = 0; i < m_n; i++)
  {
    m_data[i] = ary.m_data[i];
  }
}

template <typename T>
Array<T>::Array(Array<T>&& ary)
{
  m_n = std::move(ary.m_n);
  m_data = std::move(ary.m_data);
}

template <typename T>
T& Array<T>::operator[](unsigned int i)
{
  if(!(i>=0 && i<m_n))
    throw RangeError(i);
  return m_data[i];
}

template <typename T>
const T& Array<T>::operator[](unsigned int i) const
{
  if(!(i>=0 && i<m_n))
  {
    throw RangeError(i);
  }
  return m_data[i];
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T> ary)
{
  //Old data will be handled by destructor
  swap((*this), ary);
  return (*this);
}

template <typename T>
unsigned int Array<T>::size()
{
  return m_n;
}
