#ifndef DIMENSIONERROR_H
#define DIMENSIONERROR_H
/**
 *  @file DimensionError.h
 *  @brief Class definition for DimensionError
 *  @author Tanner Wendland
*/

class DimensionError
{
public:
  //!Constructor
  /*!
  * Pre-condition: Parameter i is of type int
  * \n Post-condition: stores i as error
  */
  DimensionError(int i) : error(i){}
  //! Obtain error subscript
  /*!
  * Pre-condition: None
  * \n Post-condition: Returns error subscript
  */
  int badSubscript() const {return error;}
private:
  int error; //!< Error subscript
};

#endif
