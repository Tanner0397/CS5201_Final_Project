/**
 *  @file vector.hpp
 *  @brief Class implmentation for Vector
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <string>
#include <sstream>
#include "Array.h"
#include "SizeError.h"
#include "DimensionError.h"

template <typename T>
Vector<T>::Vector()
{
  m_n = 0;
  m_elements = Array<T>(0);
}

template <typename T>
Vector<T>::Vector(unsigned int n)
{
  m_n = n;
  m_elements = Array<T>(m_n);
}

template <typename T>
Vector<T>::Vector(unsigned int n, T init)
{
  m_n = n;
  m_elements = Array<T>(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    m_elements[i] = init;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v)
{
  m_n = v.m_n;
  m_elements = v.m_elements;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& v)
{
  m_elements = std::move(v.m_elements);
  m_n = std::move(v.m_n);
}

template <typename T>
T& Vector<T>::operator[](unsigned int index)
{
  return m_elements[index];
}

template <typename T>
const T& Vector<T>::operator[](unsigned int index) const
{
  return m_elements[index];
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& v) const
{
  //Check to see if calling object has the same number of elements as v
  if(m_n != v.m_n)
  {
    //THROW SIZE ERROR
    throw DimensionError(m_n);
  }

  Vector<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
  {
    temp[i] = m_elements[i]+v.m_elements[i];
  }
  return temp;
}

template <typename T>
Vector<T> Vector<T>::operator-() const
{
  const double TOLERANCE = 0.005;
  Vector<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
  {
    if(fabs(m_elements[i] - 0.0) > TOLERANCE)
      temp[i] = -m_elements[i];
    else
      temp[i] = m_elements[i];
  }
  return temp;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& v) const
{
  return ((*this) + (-v));
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> v)
{
  swap((*this), v);
  return (*this);
}

template <typename T>
double Vector<T>::operator~() const
{
  return sqrt((*this)*(*this));
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& v) const
{
  if(m_n != v.m_n)
    throw DimensionError(m_n);
  bool result = true;
  const double tolerance = 0.005;
  for(unsigned int i = 0; i < m_n; i++)
    if(!(fabs(m_elements[i]-v[i]) < tolerance))
      result = false;
  return result;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& v) const
{
  return !((*this) == v);
}

template <typename T>
double Vector<T>::operator*(const Vector<T>& v) const
{
  double sum = 0;
  if(m_n != v.m_n)
    throw DimensionError(m_n);
  for(unsigned int i = 0; i < m_n; i++)
    sum += m_elements[i]*v[i];
  return sum;
}

template <typename T>
Vector<T> Vector<T>::operator*(const T& factor) const
{
  Vector<T> temp(m_n);
  for(unsigned int i = 0; i < m_n; i++)
  {
    temp[i] = factor*m_elements[i];
  }
  return temp;
}

template <typename T>
Vector<T> Vector<T>::reduce(unsigned int first_n)
{
  if(first_n > m_n)
  {
    throw SizeError(first_n);
  }
  Vector<T> new_v(first_n);
  for(unsigned int i = 0; i < first_n; i++){
    new_v[i] = (*this)[i];
  }
  return new_v;
}

template <typename T>
bool Vector<T>::is_multiple(const Vector<T>& v)
{
  const double tolerance = 0.005;
  if(m_n != v.m_n)
    throw DimensionError(m_n);
  //assume to be true until shown otherwise
  bool result = true;

  //We must look for the first element in v that is not zero
  //If we dont find one, then v is the zero vector and is automatucally a scalar
  //of the calling object.
  int v_first_nonzero_index = -1;
  for(unsigned int i = 0; i < m_n; i++)
  {
    if(!(fabs(v[i]-0.0) < tolerance))
    {
      v_first_nonzero_index = i;
      break;
    }
  }

  if(v_first_nonzero_index >= 0)
  {
    //v is not the zero vector.
    double factor = m_elements[v_first_nonzero_index] / v[v_first_nonzero_index];
    for(unsigned int i = 0; i < m_n; i++)
    {
      if(!(fabs(v[i]*factor-m_elements[i]) < tolerance))
        result = false;
    }
  }
  else
  {
    //v is the zero vector
    //the calling object will only be dependent on the zero fector if
    //the calling object is also the zero vector.
    bool is_zero = true;
    for(unsigned int i = 0; i < m_n; i++)
      if(!(fabs(m_elements[i]) < tolerance))
        is_zero = false;
    result = is_zero;
  }
  return result;
}

template <typename T>
unsigned int Vector<T>::size() const
{
  return m_n;
}

template <typename T>
std::string Vector<T>::column_format() const
{
  std::ostringstream out;
  out.precision(8);
  for(unsigned int i = 0; i < m_n; i++)
    out << m_elements[i] << std::endl;
  return out.str();
}
