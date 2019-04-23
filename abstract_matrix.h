#ifndef ABSTRACT_MATRIX_H
#define ABSTRACT_MATRIX_H

/**
 *  @file abstract_matrix.h
 *  @brief Class defintion for abstract
 *  @author Tanner Wendland
*/

#include "vector.h"

//forward declare classes
template <typename T>
class Matrix;

template <typename T>
class Abstract_Matrix
{
public:
  //! Indexing operator
  /// \pre 0 <= row < num_rows() and 0 <= col < num_cols()
  /// \post Return the the specified index. Throws error if either inequalities in the pre condtiion are not satisfied
  /// @param row of type unsigned int
  /// @param col of type unsigned int
  virtual T operator()(unsigned int row, unsigned int col) const = 0;
  //! Returns a reference to an element
  /// \pre 0 <= row < num_rows and 0 <= col < num_cols, and the element accessed must be able to be modifed without changing the matrix specification (ie Not trying to change the lower triangle of a upper triangular matrix)
  /// \post returns a reference to the specified element. Throws error if either of the inequalities are not satisfied and throws and error if the element beign indexed cannot be changed (see example in precondition)
  /// @param row of type unsigned int
  /// @param col of type unsigned int
  virtual T& get_elem(unsigned int row, unsigned int col) = 0;
  //! Vector multiplcaiton operator
  /// \pre size of v must be the same as the number of columns in the matrix
  /// \post returns the vector b of Ax = b. Throws error if the size of v is not the same as the number of columns in the matrix
  /// @param v of type const Vector<T>&
  virtual Vector<T> operator*(const Vector<T>& v) const = 0;
  //! Get a column vector
  /// \pre 0 <= index < num_cols()
  /// \post returns the column vector at the index. Throws error if the inequality in the precondition is not satisfied
  /// @param index of type unsigned int
  virtual Vector<T> col_vector(unsigned int index) const = 0;
  //! Return the number of rows in the matrix
  /// \pre None
  /// \post Returns the number of rows in the matrix
  virtual unsigned int num_rows() const = 0;
  //! Return the number of columns in the matrix
  /// \pre None
  /// \post Returns the number of columns in the matrix
  virtual unsigned int num_cols() const = 0;
  //! Matrix multiplcation
  /// \pre Operator* (T*T) must be defined. The calling object must have the same number of columns as the number of rows in m.
  /// \post Return the result of standard matrix multiplcaiton, of dimensions m_rows x m.m_cols. Throws error if m_rows != m.m_cols
  /// @param m of type const Matrix<T>&
  virtual Matrix<T> operator*(const Abstract_Matrix<T>& m) const = 0;
  //! Matrix addition
  /// \pre Calling object must have same dimensions as m. Operator+ (T+T) must be defined for type T
  /// \post Returns matrix with the element wise sum. Throws error if Calling Object is not the same dimensions as m
  /// @param m of type const Matrix<T>&
  virtual Matrix<T> operator+(const Abstract_Matrix<T>& m) const = 0;
  //! Matrix Substraction
  /// \pre Calling object must have the same dimensions as m. Operator+ (T+T) must be defined for type T
  /// \post returns matrix of the element wise difference (CO - m). Throws error if Calling Object is not the same dimensions as m
  /// @param m of type const Matrix<T>&
  virtual Matrix<T> operator-(const Abstract_Matrix<T>& m) const = 0;

};

#endif
