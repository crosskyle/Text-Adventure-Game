/*********************************************************************
 ** Program Filename: DiningSpace.hpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Declaration of class DanceSpace. Derived class of Space.
 ** Sets the item that the space hold to royal jelly. A key component
 ** to winning the game.
 ** Input: Function is called.
 ** Output: Returns boolean value.
 *********************************************************************/

#ifndef DiningSpace_hpp
#define DiningSpace_hpp

#include "Space.hpp"

class DiningSpace : public Space
{
public:
   DiningSpace(string spaceNameIn, string itemIn) : Space(spaceNameIn, itemIn) {}
   bool depositPollen();
};

#endif
