/*********************************************************************
 ** Program Filename: Space.hpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: The declaration of an abstract class Space. Each space has four
 ** pointers to other spaces. Each space holds a special function where
 ** an ant is able to deposit pollen and a special action occurs.
 ** Input: Pointers to each space are set in a different class that has
 ** spaces. There is also a bool parameter for the special function.
 ** Output: Pointers to spaces are returned, the names of the spaces and
 ** items the spaces hold are returned, and several boolean variables are
 ** returned.
 *********************************************************************/

#ifndef Space_hpp
#define Space_hpp

#include "Player.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Space
{
protected:
   string spaceName;                      //Name of space
   string item;                           //Name of item space holds
   bool deposit;                          //Determines what value special function returns
   Space *east;                           //Pointers to other spaces
   Space *west;
   Space *north;
   Space *south;
   
public:
   Space(string spaceNameIn, string itemIn);
   void setEast(Space* spaceIn);
   void setWest(Space* spaceIn);
   void setNorth(Space* spaceIn);
   void setSouth(Space* spaceIn);
   Space* getEast();
   Space* getWest();
   Space* getNorth();
   Space* getSouth();
   string getName();
   string getItem();
   bool getDeposit();
   virtual bool depositPollen() = 0;
   virtual ~Space() {}
};

#endif 

