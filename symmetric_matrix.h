#ifndef SYMM_MATRIX_H
#define SYMM_MATRIX_H
/**
 *  @file symmetric_matrix.h
 *  @brief Class defintion for symmetric matrix
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

#include "vector.h"
#include "abstract_matrix.h"
#include "Array.h"

//Forward declare class
template <typename T>
class Matrix;

///
/// \class Symmetric_Matrix
/// \brief This class acts as a symmetric matrix
///

template <typename T>
class Symmetric_Matrix : public Abstract_Matrix<T>
{
private:
  unsigned int m_n; //!< number of rows and cols for the matrix
  unsigned int m_total_elements; //!< total number of non-zero elements in the array
  Array<T> m_elements; //!< Array of elements
public:
  //! Default Constructor
  /// \pre None
  /// \post Creates matrix with no elements
  Symmetric_Matrix():m_n(0),m_total_elements(0){}
  //! Constructor
  /// \pre None
  /// \post Creates a n x n Symmetric matrix
  /// @param n of type unsigned int
  Symmetric_Matrix(unsigned int n);
  //! Move Constructor
  /// \pre None
  /// \post creates matrix by movment rvalue reference
  /// @param m of type Symmetric_Matrix<T>&&
  Symmetric_Matrix(Symmetric_Matrix<T>&& m);
  //! Copy Constructor
  /// \pre None
  /// \post Now copy of m is created
  /// @param m of type const Symmetric_Matrix<T>&
  Symmetric_Matrix(const Symmetric_Matrix<T>& m);
  //! Copy Constructor for Abstract Base
  /// \pre m's element are in Symmetric (But the object is not nessasarly a Diagonal_Matrix object)
  /// \post New copy of m is created. Throws error if m is not of symmetric
  /// @param m of type Abstract_Matrix<T>&
  Symmetric_Matrix(const Abstract_Matrix<T>& m);
  //! Addition Operator for Symmetric
  /// \pre calling object and m must be of equal dimension. Operator+ for (T+T) must be defined
  /// \post returns the sum of the matricies. throws error if m and the calling object do not have the same dimension
  /// @param m of type const Symmetric_Matrix<T>&
  Symmetric_Matrix<T> operator+(const Symmetric_Matrix<T>& m) const;
  //! Addition operator for any other type of matrix
  /// \pre calling object and m must be of equal dimension. Operator+ for (T+T) must be defined
  /// \post returns the sum of the matrcies. Throws error if m and the calling object are of not equal dimension
  /// @param m of type const Abstract_Matrix<T>&
  virtual Matrix<T> operator+(const Abstract_Matrix<T>& m) const;
  //! Substraction operator for Symmetric
  /// \pre calling object and m must be of equal dimension. Operator- for (T-T) must be defined
  /// \post returns the difference of the matricies. throws error if m and the calling object do not have the same dimension
  /// @param m of type const Symmetric_Matrix<T>&
  Symmetric_Matrix<T> operator-(const Symmetric_Matrix<T>& m) const;
  //! Substraction operator for and other type of matrix
  /// \pre calling object and m must be of equal dimension. Operator- for (T-T) must be defined
  /// \post returns the difference of the matricies. throws error if m and the calling object do not have the same dimension
  /// @param m of type const Abstract_Matrix<T>&
  virtual Matrix<T> operator-(const Abstract_Matrix<T>& m) const;
  //! Unary operator-
  /// \pre Unary operator- for T must be defined
  /// \post Returns the matrix with all the element negated
  Symmetric_Matrix<T> operator-() const;
  //! Scalar multiplcaiton
  /// \pre operator* must be defined such that (double*T) = T
  /// \post returns the matrix with each element multiplied by factor
  /// @param factor of type double
  Symmetric_Matrix<T> operator*(double factor) const;
  //! Matrix multiplcaiton operator for any matrix
  /// \pre num_cols() for the calling object is equal to the number of rows in m
  /// \post Returns the product of the matrcies. Throws error if the number fo columns in the calling object are not equal to the rows in m
  /// @param m of type Abstract_Matrix<T>&
  virtual Matrix<T> operator*(const Abstract_Matrix<T>& m) const;
  //! Transpose of the matrix
  /// \pre None
  /// \post Retunrs the transpose of the matrix, which is the matrix itself.
  Symmetric_Matrix<T> transpose() const;
  //! Vector multiplcaiton operator
  /// \pre size of v must be the same as the number of columns in the matrix
  /// \post returns the vector b of Ax = b. Throws error if the size of v is not the same as the number of columns in the matrix
  /// @param m of type const Vector<T>&
  virtual Vector<T> operator*(const Vector<T>& m) const;
  //! Assignment operator
  /// \pre None
  /// \post Calling Object is now equal to m
  /// @param m of type Symmetric_Matrix<T>
  Symmetric_Matrix<T>& operator=(Symmetric_Matrix<T> m);
  //! Get a column vector
  /// \pre 0 <= index < num_cols()
  /// \post returns the column vector at the index. Throws error if the inequality in the precondition is not satisfied
  /// @param index of type unsigned int
  virtual Vector<T> col_vector(unsigned int index) const;
  //! Return the number of rows in the matrix
  /// \pre None
  /// \post Returns the number of rows in the matrix
  virtual unsigned int num_rows() const;
  //! Return the number of columns in the matrix
  /// \pre None
  /// \post Returns the number of columns in the matrix
  virtual unsigned int num_cols() const;
  //! Indexing operator
  /// \pre 0 <= row < num_rows() and 0 <= col < num_cols()
  /// \post Return the the specified index. Throws error if either inequalities in the pre condtiion are not satisfied
  /// @param row of type unsigned int
  /// @param col of type unsigned int
  virtual T operator()(unsigned int row, unsigned int col) const;
  //! Returns a reference to an element
  /// \pre 0 <= row < num_rows and 0 <= col < num_cols, and the element accessed must be able to be modifed without changing the matrix specification (ie Not trying to change the lower triangle of a upper triangular matrix)
  /// \post returns a reference to the specified element. Throws error if either of the inequalities are not satisfied and throws and error if the element beign indexed cannot be changed (see example in precondition)
  /// @param row of type unsigned int
  /// @param col of type unsigned int
  virtual T& get_elem(unsigned int row, unsigned int col);

  //! Swap operation
  /// \pre None
  /// \post Swaps the contents of m1 and m2
  /// @param m1 of type Symmetric_Matrix<T>&
  /// @param m2 of type Symmetric_Matrix<T>&
  friend void swap(Symmetric_Matrix<T>& m1, Symmetric_Matrix<T>& m2)
  {
    std::swap(m1.m_n, m2.m_n);
    std::swap(m1.m_total_elements, m2.m_total_elements);
    std::swap(m1.m_elements, m2.m_elements);
  }

  //! Extration operator
  /// \pre None
  /// \post places elements in stream and returns it
  /// @param os of type ostream&
  /// @param m of type const Symmetric_Matrix<T>&
  friend std::ostream& operator<<(std::ostream& os, const Symmetric_Matrix<T>& m)
  {
    for(unsigned int i = 0; i < m.m_n; i++)
    {
      for(unsigned int j = 0; j < m.m_n; j++)
      {
        os << m(i, j) << " ";
      }
      os << std::endl;
    }
    return os;
  }

  //! insertion operator
  /// \pre Input must be valid.
  /// \post inserts from istream into the matrix row by row. Throws error if Input is invalid
  /// @param in of type istream&
  /// @param m of type const Symmetric_Matrix<T>&
  friend std::istream& operator>>(std::istream& in, Symmetric_Matrix<T>& m)
  {
    double throw_away;
    for(unsigned int i = 0; i < m.m_n; i++)
    {
      for(unsigned int j = 0; j < m.m_n; j++)
      {
        if(!in || in.eof())
          throw InputError();
        if(i < j)
          in >> throw_away;
        else
          in >> m.get_elem(i, j);
      }
    }
    return in;
  }
};

#include "symmetric_matrix.hpp"
#endif
