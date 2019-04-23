#ifndef ARRAY_H
#define ARRAY_H
/**
 *  @file array.h
 *  @brief definition of array class
 *  @author Tanner Wendland
*/

#include <utility>

template <typename T>
class Array{
private:
  unsigned int m_n; ///!< Size of array
  std::unique_ptr<T[]> m_data; //!< pointer of type T, that will be an array of data
public:
  //! Default Constructor
  /// \pre None
  /// \post Array object of size 0 is created
  Array();
  //! Constructor
  /// \pre n is an unsigned integer
  /// \post Array Object of size n is created
  /// @param n of type unsigned integer
  Array(unsigned int n);
  //! Copy Constructor
  /// \pre T must hvae the operator= defined such that T = T
  /// \post Calling Object is a copy of ary
  /// @param ary of type const Array<T>&
  Array(const Array<T>& ary);
  //! Move Constructor
  /// \pre None
  /// \post rvalue passed is now an lvalue
  /// @param ary of type Array<T>&&
  Array(Array<T>&& ary);
  //! T& [] Operator
  /// \pre i must be an unsigned integer between 0 and m_n-1
  /// \post returns T& of the i'th locations in the Array. Throws error if i does not satisfy 0 <= i < m_n
  /// @param n of type unsigned integer
  T& operator[](unsigned int i);
  //! const T& [] Operator
  /// \pre i mist be an unsigned integer between 0 and m_n-1
  /// \post returns const T& of the i'th location in the Array. Throws error if i does not satisfy 0 <= i < m_n
  /// @param n of type unsigned integer
  const T& operator[](unsigned int i) const;
  //! Assignment Operator
  /// \pre None
  /// \post calling object is a copy of ary
  /// @param ary of type Array<T>
  Array<T>& operator=(Array<T> ary);
  //! Returns size of array
  /// \pre None
  /// \post Returns unsigned int that is the size of the array
  unsigned int size();
  //! Swap Functions
  /// \pre None
  /// \post Swaps the contents of a1 with a2
  /// @param a1 of type Array<T>&
  /// @param a2 of type Array<T>&
  friend void swap(Array& a1, Array& a2)
  {
    std::swap(a1.m_n, a2.m_n);
    std::swap(a1.m_data, a2.m_data);
  }

};

#include "Array.hpp"

#endif
