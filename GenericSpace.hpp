/*********************************************************************
 ** Program Filename: GenericSpace.hpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Declaration class GenericSpace. Derived from Space class.
 ** Returns true 10% of the time. Structure is changed in the Beehive class if true.
 ** Input: Function is called.
 ** Output: Returns boolean value.
 *********************************************************************/

#ifndef GenericSpace_hpp
#define GenericSpace_hpp

#include "Space.hpp"

class GenericSpace : public Space
{
public:
   GenericSpace(std::string spaceNameIn, std::string itemIn) : Space(spaceNameIn, itemIn) {}
   bool depositPollen();
};

#endif 
