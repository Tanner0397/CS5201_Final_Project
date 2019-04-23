#ifndef MATRIXDIMERROR_H
#define MATRIXDIMERROR_H
/**
 *  @file DimensionError.h
 *  @brief Class definition for DimensionError
 *  @author Tanner Wendland
*/

class MatrixDimError
{
public:

  MatrixDimError(int i, int n) : bad_row(i), bad_col(n){}

  int get_bad_col() const {return bad_col;}
  int get_bad_row() const {return bad_row;}
private:
  int bad_row; //!< Error subscript row
  int bad_col; //!< Error subscript col
};

#endif
