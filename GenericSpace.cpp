/*********************************************************************
 ** Program Filename: GenericSpace.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Definition of the special function of class GenericSpace.
 ** Returns true 10% of the time. Structure is changed in the Beehive class if true.
 ** Input: Function is called.
 ** Output: Returns boolean value.
 *********************************************************************/

#include "GenericSpace.hpp"

bool GenericSpace::depositPollen()
{
   int random = (rand() % 10) + 1;
   
   if (random == 1)
      deposit = true;
   
   return deposit;
}
