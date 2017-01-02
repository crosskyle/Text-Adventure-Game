/*********************************************************************
 ** Program Filename: DanceSpace.hpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: Class DanceSpace declared. Derived space class.
 ** Returns true after 2 function calls. Queen lair is opened in Beehive
 ** class if true.
 ** Input: Function is called.
 ** Output: Returns boolean value.
 *********************************************************************/

#ifndef DanceSpace_hpp
#define DanceSpace_hpp

#include "Space.hpp"

class DanceSpace : public Space
{
private:
   int depositCount;                   //Holds number of times function was called
public:
   DanceSpace(string spaceNameIn, string itemIn) : Space(spaceNameIn, itemIn)
   {
      depositCount = 0;
   }
   bool depositPollen();
   
};

#endif
