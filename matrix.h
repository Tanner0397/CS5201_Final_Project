#ifndef MATRIX_H
#define MATRIX_H

/**
 *  @file matrix.h
 *  @brief Class defintion for matrix
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include "vector.h"
#include "abstract_matrix.h"
#include "Array.h"

//Forward declare classes
template <typename T>
class Upper_Matrix;

template <typename T>
class Lower_Matrix;

///
/// \class Matrix
/// \brief This class acts as 2D matrix
///

template <typename T>
class Matrix : public Abstract_Matrix<T>
{
private:
  unsigned int m_rows; //!< number of rows for the matrix
  unsigned int m_cols; //!< number of columns for the matrix
  Array<Vector<T>> m_row_vectors; //!< Array of row vectors
public:
  //! Default Constructor
  /// \pre None
  /// \post Matrix of 0 x 0 is constructed
  Matrix():m_rows(0), m_cols(0){}
  //! Constructor with integer parameters
  /// \pre None
  /// \post Matrix of rows x cols is constructed
  /// @param rows dof type unsigned int
  /// @param cols of type unsigned int
  Matrix(unsigned int rows, unsigned int cols);
  //! Move Constructor
  /// \pre None
  /// \post Object constructed by moving rvalue
  /// @param m of type Matrix<T>&&
  Matrix(Matrix<T>&& m);
  //! Copy Constructor
  /// \pre None
  /// \post New copy of m is created
  /// @param m of type const Matrix<T>&
  Matrix(const Matrix<T>& m);
  //! Copy constructor for Abstract_Matrix
  /// \pre None
  /// \post New copy of m is created
  /// @param m of type const Abstract_Matrix<T>&
  Matrix(const Abstract_Matrix<T>& m);
  //! indexing operator
  /// \pre index satisfies 0 <= index < m_rows
  /// \post retuns the row vector at index. Throws error if inequality isn't satisfied
  /// @param index of type unsigned int
  Vector<T>& operator[](unsigned int index);
  //! constant indexing operator
  /// \pre index satisfies 0 <= index < m_rows
  /// \post returns constant reference to row vector at index. Throws error if the inequality isn't satisfied
  /// @param index of type unsigned integer
  const Vector<T>& operator[](unsigned int index) const;
  //! Matrix addition
  /// \pre Calling object must have same dimensions as m. Operator+ (T+T) must be defined for type T
  /// \post Returns matrix with the element wise sum. Throws error if Calling Object is not the same dimensions as m
  /// @param m of type const Matrix<T>&
  virtual Matrix<T> operator+(const Abstract_Matrix<T>& m) const;
  //! Matrix Substraction
  /// \pre Calling object must have the same dimensions as m. Operator+ (T+T) must be defined for type T
  /// \post returns matrix of the element wise difference (CO - m). Throws error if Calling Object is not the same dimensions as m
  /// @param m of type const Matrix<T>&
  virtual Matrix<T> operator-(const Abstract_Matrix<T>& m) const;
  //! Matrix negation
  /// \pre Type T must have the unary operator- defined for it
  /// \post returns matrix whos element are the negation of the calling objects
  Matrix<T> operator-() const;
  //! Scalar multiplcaiton
  /// \pre T must have operator* (T*double) defined for it and still be of type T
  /// \post Returns matrix who's elements are the product of factor and the correponding element in the calling object
  /// @param factor of type double
  Matrix<T> operator*(double factor) const;
  //! Matrix multiplcation
  /// \pre Operator* (T*T) must be defined. The calling object must have the same number of columns as the number of rows in m.
  /// \post Return the result of standard matrix multiplcaiton, of dimensions m_rows x m.m_cols. Throws error if m_rows != m.m_cols
  /// @param m of type const Matrix<T>&
  virtual Matrix<T> operator*(const Abstract_Matrix<T>& m) const;
  //! Matrix Transpose
  /// \pre None
  /// \post Returns transpose of the matrix
  Matrix<T> transpose() const;
  //! Matrix multiplcaiton with a vector
  /// \pre v is a column vector of dimension m_rows
  /// \post return the vector that result from matrix multiplcaiton. Throws error if v is not of size m_rows
  /// @param v of type const Vector<T>&
  virtual Vector<T> operator*(const Vector<T>& v) const;
  //! Assignment Operator
  /// \pre None
  /// \post Calling object is a copy of m
  /// @param m of type Matrix<T>
  Matrix<T>& operator=(Matrix<T> m);
  //! Assignment operator for Abstract
  /// \pre None
  /// \post Calling object is a copy of m
  /// @param m of type const Abstract_Matrix<T>&
  Matrix<T>& operator=(const Abstract_Matrix<T>& m);
  //! Returns a column vector
  /// \pre index satisfies 0 <= index < m_cols
  /// \post retuns the column vector at index Throws error if index does not satisfy inequality
  /// @param index of type unsigned int
  virtual Vector<T> col_vector(unsigned int index) const;
  //! Set a coumn vector
  /// \pre index satisfies 0 <= index < m_cols. Assignment operator for T mustbe defined. v must be of dimension m_rows
  /// \post Calling objects column vector at index is now changed. Throws error if index inequality isnt satisfied. Throws error of v is not of size m_rows
  /// @param index of type unsigned int
  /// @param v of type const Vector<T>&
  void set_col(unsigned int index, const Vector<T>& v);
  //! Returns number of rows in matrix
  /// \pre None
  /// \post Returns number of rows in matrix
  virtual unsigned int num_rows() const;
  //! Returns number of cols in matrix
  /// \pre None
  /// \post Returns number of cols in matrix
  virtual unsigned int num_cols() const;
  //! Get element operator
  /// \pre row satisfies 0<=row<M_rows and col satisfies 0<=col<m_cols
  /// \post Returns reference to element. Throws error if any inequality in the pre condition is not satisfied
  /// @param row of type unsigned int
  /// @param col of type unsigned int
  virtual T operator()(unsigned int row, unsigned int col) const;
  //! Get element operator (const ref)
  /// \pre row satisfies 0<=row<M_rows and col satisfies 0<=col<m_cols
  /// \post Returns reference to element. Throws error if any inequality in the pre condition is not satisfied
  /// @param row of type unsigned int
  /// @param cols of type unsigned int
  virtual T& get_elem(unsigned int row, unsigned int cols);
  //! Returns the lower triangle of the matrix
  /// \pre Matrix must be square
  /// \post Reutrns the lower triangle with the diagonal of the caling object. Throws error if matrix is not square
  Lower_Matrix<T> lower_triangle() const;
  //! Reutnrs the upper triangle of the matrix
  /// \pre Matrix must be square
  /// \post Reutnr the upper triangle with the diagonal of the calling object. Throws error if the matrix is not a square
  Upper_Matrix<T> upper_triangle() const;

  //! Swap function
  /// \pre None
  /// \post m1 and m2 are swapped
  /// @param m1 of type Matrix<T>
  /// @param m2 of type Matrix<T>
  friend void swap(Matrix<T>& m1, Matrix<T>& m2)
  {
    std::swap(m1.m_rows, m2.m_rows);
    std::swap(m1.m_cols, m2.m_cols);
    std::swap(m1.m_row_vectors, m2.m_row_vectors);
    return;
  }
  //! extration operator
  /// \pre None
  /// \post places row vectors in stream and returns it
  /// @param os of type ostream&
  /// @param m of type const Matrix<T>&
  friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
  {
    for(unsigned int i = 0; i < m.m_rows; i++)
    {
      os << m.m_row_vectors[i] << std::endl;
    }
    return os;
  }
  //! insertion operator
  /// \pre Input must be valid. Read row by row.
  /// \post inserts from istream into the matrix row by row. Throws error if Input is invalid
  /// @param in of type istream&
  /// @param m of type const Matrix<T>&
  friend std::istream& operator>>(std::istream& in, Matrix<T>& m)
  {
    for(unsigned int i = 0; i < m.m_rows; i++)
    {
      if(!in || in.eof())
        throw InputError();
      in >> m.m_row_vectors[i];
    }
    return in;
  }
};

#include "matrix.hpp"

#endif
