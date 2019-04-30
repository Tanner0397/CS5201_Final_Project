#ifndef VECTOR_H
#define VECTOR_H
/**
 *  @file vector.h
 *  @brief Class definition for Vector
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include <iostream>
#include <string>
#include "Array.h"
#include "InputError.h"

///
/// \class Vector
/// \brief This class acts as a vector
///

template <typename T>
class Vector {
private:
  Array<T> m_elements; //!< Array of elements for the vector
  unsigned int m_n; //!< Number of elements in the vector

public:
  //! Default Constructor
  /// \pre None
  /// \post Vector of dim 0 and array of size 0 is created
  Vector();
  //! Construstor
  /// \pre None
  /// \post A Zero vector of size n is created
  /// @param n of type unsigned int
  Vector(unsigned int n);
  ///! Constructor
  /// \pre T must have operator= defined such that T = T
  /// \post A vector of size n with init being it's only value is created
  /// @param n of type unsigned int
  /// @param init oif type T
  Vector(unsigned int n, T init);
  ///! Copy Constructor
  /// \pre Array<T> must have the operator = defined
  /// \post A copy of v is constructed
  /// @param v of type const Vector<T>&
  Vector(const Vector<T>& v);
  //! Move Constructor
  /// \pre None
  /// \post rvalue passed is moved to be an lvalue
  /// @param v of type Vectot<T>&&
  Vector(Vector<T>&& v);
  //! Addition binary operator between 2 vectors
  /// \pre Calling object and v must have the same value for m_n, T must have operator+ defined such that T + T
  /// \post New vector that is the element wise sum is returned
  /// @param v of type const Vector<T>&
  Vector<T> operator+(const Vector<T>& v) const;
  //! Substraction binary operator between 2 vectors
  /// \pre Calling object and v must have the same value for m_n, T must have operator= defined such that T = T
  /// \post New vector that is the element wise difference is returned, throws error if v is not the same size of the calling object
  /// @param v of type const Vector<T>&
  Vector<T> operator-(const Vector<T>& v) const;
  //! Negation unary operator for a single vector
  /// \pre type T must have unary operator- defined, T must have operator= defined such that T = T
  /// \post New vector that is the element wize opposite is returned, throws error if v is not the same size of the calling object
  Vector<T> operator-() const;
  //! Dot product of two vectors
  /// \pre calling object and v must have the same value for m_n, Binary operator* must be defined for T (T*T), and the resulting type from T*T (denoted as M) should have the operator + defined such that (M+M), and M must be able to be represented as a double
  /// \post returns a double that is the dot product of teh calling object and v (inner product <v1,v2>)
  /// @param v of type const Vector<T>&
  double operator*(const Vector<T>& v) const;
  //! Scalar multiplication of vectors
  /// \pre Calling object and v must have the same value for m_n, T must have the binary operator* defined such that (T*T) is of type T.
  /// \post new vector that is the scalar mutiple the calling object by factor is returned, throws error of v is not the size of the calling object
  /// @param factor of type const T&
  Vector<T> operator*(const T& factor) const;
  //! Element accessor
  /// \pre index is an unsigned integer between 0 and m_n-1, Array must have the operator [] defined
  /// \post returns reference to the vectors element at index
  /// @param index of type unsigned int
  T& operator[](unsigned int index);
  //! Element getter (calling object not mutable in this version)
  /// \pre index is an unsigned integer between 0 and m_n-1, Array must have the operator [] defined
  /// \post returns const reference to the vectors element at index
  /// @param index of type unsigned int
  const T& operator[](unsigned int index) const;
  //! Assignment Operator
  /// \pre None
  /// \post calling object is now a copy of v
  /// @param v of type Vector<T>
  Vector<T>& operator=(Vector<T> v);
  //! Magnitude of vector
  /// \pre Binary operator* must be defined for T, and their results muyst be able to be represented as a double
  /// \post Returns double that is the length of the vector (sqrt(v*v)) or (sqrt(<v, v>))
  double operator~() const;
  //! Operator that determines of calling object is equal to v
  /// \pre Calling object and v must have the same value for m_n, Binary operator must be define for T, and T must be able to be represented as a double
  /// \post Returns trie of they are equal within acceptable tolerance, false otherwise. Throws error if v is not the same size of the calling object
  /// @param v of type const Vecotr<T>&
  bool operator==(const Vector<T>& v) const;
  //! Operator that determines of calling object is not equal to v
  /// \pre Calling object and v must have the same value for m_n, Binary operator must be define for T, and T must be able to be represented as a double
  /// \post Returns true if they are not equal within acceptable tolerance, false otherwise. Throws error if v is not the same size of the calling object
  /// @param v of type const Vector<T>&
  bool operator!=(const Vector<T>& v) const;
  //! Returns a vector that is a copy of the calling object, but with only the first n elements
  /// \pre first_n is an unsigned integer between 1 and m_n
  /// \post Returns vector with eh first n element of the calling object. Throws error if the first_n lies outside the range as defined in the pre_condition
  /// @param first_n of type unsigned int
  Vector<T> reduce(unsigned int first_n);
  //! Determines of v is a mutiple of the calling object
  /// \pre Calling object and v must have the same value for m_n, Binary operators /, * must be defined for T, T must be able to be represented as a double.
  /// \post Returns true of v is a scalar multiple of the calling object. Throws error of v is not the same size of the calling object
  /// @param v of type const Vector<T>&
  bool is_multiple(const Vector<T>& v);
  //! Returns size of vector
  /// \pre None
  /// \post returns unsigned int of the number of element in the vector
  unsigned int size() const;
  //! String in column vector format
  /// \pre operator<< must be defined for type T
  /// \post returns string formated to represent column vector
  std::string column_format() const;
  //! Swap function
  /// \pre None
  /// \post v1's data is swapped with v2's
  /// @param v1 of type Vector<T>&
  /// @param v2 of type Vector<T>&
  friend void swap(Vector<T>& v1, Vector<T>& v2)
  {
    std::swap(v1.m_elements, v2.m_elements);
    std::swap(v1.m_n, v2.m_n);
  }
  //! insertion operator
  /// \pre operator<< defined for T
  /// \post Entry of elements in inserted into ostream reference
  /// @param os of type ostream&
  /// @param v of type const Vector<T>&
  friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
  {
    for(unsigned int i = 0; i < v.m_n; i++)
      os << v.m_elements[i] << " ";
    return os;
  }
  //! extration operator
  /// \pre operator>> defined for T
  /// \post m_n values are inserted into the vector in that order given by istream
  /// @param in of type istream&
  /// @param v of type Vector<T>&
  friend std::istream& operator>>(std::istream& in, Vector<T>& v)
  {
    for(unsigned int i = 0; i < v.m_n; i++)
    {
      if(!in)
      {
        InputError n;
        throw n;
      }
      in >> v[i];
    }
    return in;
  }
};

#include "vector.hpp"

#endif
