/*********************************************************************
 ** Program Filename: DanceSpace.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Definition of the special function of class DanceSpace.
 ** Returns true after 2 function calls. Queen lair is opened in Beehive
 ** class if true.
 ** Input: Function is called.
 ** Output: Returns boolean value.
 *********************************************************************/

#include "DanceSpace.hpp"

bool DanceSpace::depositPollen()
{
   ++depositCount;
   
   item = "Tae-bo xtreme dvd";
   
   if (depositCount == 2)
      deposit = true;
   
   return deposit;
}
