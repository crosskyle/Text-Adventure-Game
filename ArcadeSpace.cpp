/*********************************************************************
 ** Program Filename: ArcadeSpace.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Definition of the special function of class ArcadeSpace.
 ** Returns true 50% of the time. New links are made in the Beehive class if true.
 ** Input: Function is called.
 ** Output: Returns boolean value.
 *********************************************************************/

#include "ArcadeSpace.hpp"

bool ArcadeSpace::depositPollen()
{
   int random = (rand() % 2) + 1;
   
   //50% chance random is true
   if (random == 1)
      deposit = true;

   return deposit;
}
