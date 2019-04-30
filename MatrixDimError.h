#ifndef MATRIXDIMERROR_H
#define MATRIXDIMERROR_H
/**
 *  @file MatrixDimError.h
 *  @brief Class definition for MatrixDimError
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

///
/// \class MatrixDimError
/// \brief This class is an exception handling class that is to be thrown
///        when there is an error involving matrix dimensions
///

class MatrixDimError
{
public:

  ///
  /// \fn MatrixDimError
  /// \brief constructor
  /// \pre none
  /// \post bad_row = i and bad_col = n
  /// \param i is assigned to bad_row
  /// \param n is assigned to bad_col
  ///
  MatrixDimError(int i, int n) : bad_row(i), bad_col(n){}

  ///
  /// \fn int get_bad_col()
  /// \brief returns bad_col
  /// \pre none
  /// \post bad_col is returned
  /// \return bad_col
  ///
  int get_bad_col() const {return bad_col;}

  ///
  /// \fn int get_bad_row()
  /// \brief returns bad_row
  /// \pre none
  /// \post bad_row is returned
  /// \return bad_row
  ///
  int get_bad_row() const {return bad_row;}
private:
  int bad_row; //!< Error subscript row
  int bad_col; //!< Error subscript col
};

#endif
