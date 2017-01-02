/*********************************************************************
 ** Program Filename: Beehive.hpp
 ** Author: Kyle Cross
 ** Date: 8-5-2016
 ** Description: The definition of the class Beehive. A structure is created
 ** that contains dynamically allocated spaces. Beehive has spaces and has
 ** a player. The location of the player is kept track of. The structure
 ** changes from the actions of the user in the main program. Various
 ** members of the derived spaces and player object are changed by the user
 ** during runtime.
 ** Input: The user determines which direction the player is moved in and
 ** also determines if calls are made to the derived spaces or player object.
 ** Output: Various boolean value indicating what has changed in the structure.
 ** Variables from the the player object.
 *********************************************************************/


#ifndef Beehive_hpp
#define Beehive_hpp

#include "ArcadeSpace.hpp"
#include "GenericSpace.hpp"
#include "DanceSpace.hpp"
#include "DiningSpace.hpp"
#include "Player.hpp"

class Beehive
{
private:
   Space *space1;                      //Holds pointers to derived spaces
   Space *space2;
   Space *space3;
   Space *space4;
   Space *space5;
   Space *space6;
   Space *playerLoc;                   //Holds player location
   Player player;                      //Beehive has a player
   bool bearAteSpace;                  //Indicates if space has been deleted
   bool queenDoor;                     //Indicates if links have been made
   bool keyUsed;                       //Indicates if space has been created
   
public:
   Beehive();
   void bearEatsSpace();
   bool arcadeSecretPassages();
   bool unlockQueenLair();
   bool graveyardSecretDoor();
   bool keyToWorkerBeeLair();
   bool getBearAte() { return bearAteSpace; }
   bool getQueenDoor() { return queenDoor; }
   bool getKeyUsed() { return keyUsed; }
   string getLocation() { return playerLoc->getName(); }
   bool move(char moveIn);
   void dropPollen();
   bool hasDepositedPollen() { return playerLoc->getDeposit(); }
   int getPollenCount() { return player.getPollen(); }
   void pickupSpaceItem() { player.addItem(playerLoc->getItem()); }
   void displayItems() { player.displayBackpack(); }
   void removeBackpackItem(string itemIn) { player.removeItem(itemIn); }
   bool searchBackpackItem(string itemIn) { return player.searchItem(itemIn); }
   void pickupItem(string itemIn) { player.addItem(itemIn); }
   ~Beehive();
};


#endif 
