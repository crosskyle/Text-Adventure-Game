/*********************************************************************
 ** Program Filename: ArcadeSpace.hpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Declaration of class ArcadeSpace. Derived from Space.
 ** Returns true 50% of the time. New links are made in the Beehive class if true.
 ** Input: Function is called.
 ** Output: Returns boolean value.
 *********************************************************************/

#ifndef ArcadeSpace_hpp
#define ArcadeSpace_hpp

#include "Space.hpp"

class ArcadeSpace : public Space
{
public:
   ArcadeSpace(std::string spaceNameIn, std::string itemIn) : Space(spaceNameIn, itemIn) {}
   bool depositPollen();
};

#endif 
