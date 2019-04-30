#ifndef SIZEERROR_H
#define SIZEERROR_H
/**
 *  @file SizeError.h
 *  @brief Class definition for SizeError
 *  @author Tanner Wendland
 *  @author Alex Sanchez
*/

///
/// \class SizeError
/// \brief This class is an exception handling class that is to be thrown
///        when there is an error involving size
///

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
