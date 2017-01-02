/*********************************************************************
 ** Program Filename: Space.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: The declaration of an abstract class Space. Each space has four
 ** pointers to other spaces. Each space holds a special function where
 ** an ant is able to deposit pollen and a special action occurs.
 ** Input: Pointer to each space are set in a different class that has
 ** spaces. There is also a bool parameter for the special function.
 ** Output: Pointers to spaces are returned, the names of the spaces and
 ** items the spaces hold are returned, and several boolean variables are
 ** returned.
 *********************************************************************/

#include "Space.hpp"

Space::Space(string spaceNameIn, string itemIn)
{
   east = NULL;
   west = NULL;
   north = NULL;
   south = NULL;
   spaceName = spaceNameIn;
   item = itemIn;
   deposit = false;
}

string Space::getName()
{
   return spaceName;
}

string Space::getItem()
{
   return item;
}

bool Space::getDeposit()
{
   return deposit;
}

void Space::setEast(Space* spaceIn)
{
   east = spaceIn;
}

void Space::setWest(Space* spaceIn)
{
   west = spaceIn;
}

void Space::setNorth(Space* spaceIn)
{
   north = spaceIn;
}

void Space::setSouth(Space* spaceIn)
{
   south = spaceIn;
}

Space* Space::getEast()
{
   return east;
}

Space* Space::getWest()
{
   return west;
}

Space* Space::getNorth()
{
   return north;
}

Space* Space::getSouth()
{
   return south;
}

