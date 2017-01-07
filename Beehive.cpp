/*********************************************************************
 ** Program Filename: Beehive.cpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: The definition of the class Beehive. A structure is created
 ** that contains dynamically allocated spaces. Beehive has spaces and has
 ** a player. The location of the player is kept track of. The structure
 ** changes from the actions of the user in the main program. Various
 ** members of the derived spaces and player object are changed by the user
 ** during runtime.
 ** Input: The user determines which direction the player is moved in and
 ** also determines if calls are made to the derived spaces.
 ** Output: Various boolean value indicating what has changed in the structure.
 ** Variables from the the player object are also output.
 *********************************************************************/

#include "Beehive.hpp"

Beehive::Beehive()
{
   //Assign pointers of derived spaces to pointers of spaces
   space1 = new ArcadeSpace("Arcade", "coins");
   space2 = new GenericSpace("Brood lair", "snake oil");
   space3 = new DanceSpace("Dance room", "Tae-bo dvd");
   space4 = new GenericSpace("Graveyard", "bug spray");
   space5 = new GenericSpace("Queen lair", "snake oil");
   space6 = new DiningSpace("Dining hall", "twigs");
   
   //Assign links to connect the starting structure
   space1->setEast(space2);
   space1->setSouth(space3);
   
   space2->setWest(space1);
   space2->setSouth(space4);
   
   space3->setEast(space4);
   space3->setNorth(space1);
   
   space4->setWest(space3);
   space4->setNorth(space2);
   space4->setSouth(space6);
   
   space6->setNorth(space4);
   
   //Player starting location is space 1
   playerLoc = space1;
   
   bearAteSpace = false;                     //Indicates that space3 has not been deleted
   queenDoor = false;
   keyUsed = false;                          //Indicates that space holding worker bee lair
                                             //Has not been allocated
}

/*********************************************************************
 ** Function: void bearEatsSpace()
 ** Description: Deletes a pointer to space3.
 ** Pre-Conditions: New space3 cannot be allocated until this function is called.
 ** Post-Conditions: New space3 can be allocated. Links must be assigned.
 ** Player can't move into queen lair.
 *********************************************************************/

void Beehive::bearEatsSpace()
{
   //Space is deleted if it has not yet been deleted
   if (!bearAteSpace)
   {
      delete space3;
      space3 = NULL;
      
      space1->setSouth(NULL);
      space4->setWest(NULL);
      space5->setNorth(NULL);
      
      bearAteSpace = true;                   //Indicates space has been deleted
   }
}

/*********************************************************************
 ** Function: bool arcadeSecretPassages()
 ** Description: Assigns new links within structure.
 ** Pre-Conditions: Player cannot move in certain directions.
 ** Post-Conditions: Player can now move in more directions.
 *********************************************************************/

bool Beehive::arcadeSecretPassages()
{
   //New links made if call to function is true
   if (space1->getDeposit())
   {
      space1->setNorth(space5);
      space1->setWest(space6);
      space5->setSouth(space1);
      space6->setEast(space1);
      space5->setEast(space6);
      space6->setWest(space5);
      
      queenDoor = true;
      
      return true;
   }
   else
   {
      //New links not made and more pollen is taken away
      for (int i = 0; i < 4; i++)
      {
         player.decrementPollen();
      }
      return false;
   }
}

/*********************************************************************
 ** Function: bool unlockQueenLair()
 ** Description: Assigns new links within structure.
 ** Pre-Conditions: Player cannot move in certain directions.
 ** Post-Conditions: Player can now move in more directions.
 *********************************************************************/

bool Beehive::unlockQueenLair()
{
   //New links made if call to function is true
   if (space3->getDeposit())
   {
      space3->setSouth(space5);
      space5->setEast(space6);
      space5->setNorth(space3);
      space6->setWest(space5);
      
      queenDoor = true;                      //Indicates Queen door is unlocked
      
      return true;
   }
   return false;
}

/*********************************************************************
 ** Function: bool graveyardSecretDoor()
 ** Description: Allocates new space. New links made.
 ** Pre-Conditions: Player cannot move in certain directions.
 ** Post-Conditions: Player can now move in more directions and to a new space.
 *********************************************************************/

bool Beehive::graveyardSecretDoor()
{
   ////New space allocated and new links made if call to function is true
   if (keyUsed == false)
   {
      space3 = new GenericSpace("Worker bee lair", "honey");
      space3->setWest(space4);
      space3->setNorth(space2);
      space3->setSouth(space2);
      space3->setEast(space2);
      space4->setEast(space3);
      
      keyUsed = true;                        //Indicates new space has been created
      
      return true;
   }
   
   return false;
}

/*********************************************************************
 ** Function: bool keyToWorkerBeeLair()
 ** Description: Deletes a space, creates new links and adds item to backpack.
 ** Pre-Conditions: Player cannot move in certain directions.
 ** Post-Conditions: Player can now move in more directions and to a new space.
 *********************************************************************/

bool Beehive::keyToWorkerBeeLair()
{
   if (playerLoc->getDeposit() && !bearAteSpace)
   {
      bearEatsSpace();                       //deletes space
      
      space5->setEast(space6);               //new links made
      space6->setWest(space5);
      
      return true;
   }
   else
      return false;
}

/*********************************************************************
 ** Function: bool move()
 ** Description: Moves player location to user specifed space and decrements turn.
 ** Determines if game ends if no turns are left.
 ** Pre-Conditions: Spaces should be allocated.
 *********************************************************************/

bool Beehive::move(char moveIn)
{
   //Moves player north, south, east, or west
   if (playerLoc->getEast() && moveIn == 'E')
   {
      playerLoc = playerLoc->getEast();
   }
   else if (playerLoc->getWest() && moveIn == 'W')
   {
      playerLoc = playerLoc->getWest();
   }
   else if (playerLoc->getNorth() && moveIn == 'N')
   {
      playerLoc = playerLoc->getNorth();
   }
   else if (playerLoc->getSouth() && moveIn == 'S')
   {
      playerLoc = playerLoc->getSouth();
   }
   else
   {
      std::cout << "\nDOOR IS LOCKED." << std::endl;
   }
   
   //Determines if any turns are left
   player.decrementTurn();
   
   if (player.getTurn() < 1)
      return true;
   
   return false;
}

/*********************************************************************
 ** Function: void dropPollen(bool)
 ** Description: Makes call to virtual function of Space. Decrements pollen.
 ** Pre-Conditions: There should be pollen left
 ** Post-Conditions: Use hasDepositedPollen to determine outcome of function call.
 *********************************************************************/

void Beehive::dropPollen()
{
   playerLoc->depositPollen();
   
   player.decrementPollen();
}

Beehive::~Beehive()
{
    delete space1;
    delete space2;
    delete space3;
    delete space4;
    delete space5;
    delete space6;
}

