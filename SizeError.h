#ifndef SIZEERROR_H
#define SIZEERROR_H
/**
 *  @file norm.h
 *  @brief Class definition for SizeError
 *  @author Tanner Wendland
*/

class SizeError
{
public:
  //!Constructor
  /*!
  * Pre-condition: Parameter i is of type int
  * \n Post-condition: stores i as error
  */
  SizeError(int i) : error(i){}
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
