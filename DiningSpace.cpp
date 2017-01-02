/*********************************************************************
 ** Program Filename: DiningSpace.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Definition of the special function of class DanceSpace.
 ** Sets the item that the space hold to royal jelly. A key component
 ** to winning the game.
 ** Input: Function is called.
 ** Output: Returns boolean value.
 *********************************************************************/

#include "DiningSpace.hpp"

bool DiningSpace::depositPollen()
{
   item = "royal jelly";
   
   deposit = true;
   
   return deposit;
}
