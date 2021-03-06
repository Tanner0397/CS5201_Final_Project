#ifndef RANGEERROR_H
#define RANGEERROR_H
/**
 *  @file RangeError.h
 *  @brief Class definition for RangeError
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

///
/// \class RangeError
/// \brief This class is an exception handling class that is to be thrown
///        when there is an error involving the range
///

class RangeError
{
public:
  //!Constructor
  /*!
  * Pre-condition: Parameter i is of type int
  * \n Post-condition: stores i as error
  */
  RangeError(int i) : error(i){}
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
