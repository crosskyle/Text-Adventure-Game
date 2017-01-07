/*********************************************************************
 ** Program Filename: gamePlay.cpp
 ** Author: Kyle Cross
 ** Date: 1-3-2017
 ** Description: Runs a maze game where an ant is tasked with finding honey
 ** to save an ant colony. A json file is used to read the game's text to the
 ** screen. The user has the options to move, pick up items, deposit pollen,
 ** and show picked up items that are in a backpack vector. The user navigates a linked
 ** structure that is manipulated in a 'Beehive' class. The Beehive class contains
 ** different spaces and the player that navigates the spaces in the game world.
 ** Input: User chooses between a menu of options. Inputs direction of moves.
 ** Output: The state of the game is displayed.
 *********************************************************************/


#include "gamePlay.hpp"


/*********************************************************************
 ** Function: string parse(string)
 ** Description: Parses spaces in a json file so that the text reads correctly.
 *********************************************************************/

std::string GamePlay::parse(std::string stringIn) {
   std::string s = stringIn;
   s.erase(remove(s.begin(), s.end(), '\"'), s.end());
   
   return s;
}


/*********************************************************************
 ** Function: char getMenuOption(char, json)
 ** Description: Allows user to choose a menu option during gameplay.
 *********************************************************************/

char GamePlay::getMenuOption(char &choice, json j) {
   //Menu option is chosen
   std::cout << parse(j["menu"]);
   std::cin.clear();
   std::cin >> choice;
   choice = toupper(choice);
   
   //Input validation
   while (!std::cin || (choice != 'M' && choice != 'P' && choice != 'D' && choice != 'S'
                   && choice != 'L' && choice != 'Q'))
   {
      std::cout << "Enter a valid character." << std::endl;
      std::cin.ignore(10000,'\n');
      std::cin >> choice;
      choice = toupper(choice);
   }
   
   return choice;
}


/*********************************************************************
 ** Function: char getDirection(char, json)
 ** Description: Allows user to move in one of four directions during gameplay.
 *********************************************************************/

char GamePlay::getDirection(char &move, json j) {
   do
   {
      std::cin.ignore(10000,'\n');
      std::cout << parse(j["choose direction"]);
      std::cin >> move;
      move = toupper(move);
      
   } while (!std::cin || (move != 'N' && move != 'S' && move != 'E' && move != 'W'));

   return move;
}


/*********************************************************************
 ** Function: void displayLocation(json)
 ** Description: Display's player location.
 *********************************************************************/

void GamePlay::displayLocation(json j) {
   std::cout << "\nCurrent location: " << play.getLocation() << std::endl;
   
   if (play.getKeyUsed())
   {
      std::cout << parse(j["displayWorld"]["key used"][play.getLocation()]);
   }
   else if (play.getBearAte())
   {
      std::cout << parse(j["displayWorld"]["bear ate"][play.getLocation()]);
   }
   else
   {
      std::cout << parse(j["displayWorld"]["start"][play.getLocation()]);
   }
}


/*********************************************************************
 ** Function: void playGame()
 ** Description: A user chooses from a menu of options what the course
 ** of action is in the game. The user has the ability to move throughout
 ** a linked structure and alter the structure until the goal is reached.
 ** Pre-Conditions: A Space class is defined with the appropriate
 ** derived character classes. A Beehive class contains a linked structure of
 ** spaces and various functions of the player.
 *********************************************************************/

void GamePlay::playGame() {
   //Read in game text file
   std::ifstream gameText("gameText.json");
   json j;
   gameText >> j;
   
   //Starting instructions
   std::cout << parse(j["start"]);
   std::cout << parse(j["displayWorld"]["start"]["Arcade"]);   //Prints world map
   std::cout << parse(j["arcade"]["4"]);                       //Start in arcade room
   
   //Choose menu option
   getMenuOption(choice, j);
   
   //User-controlled while loop
   while (choice != 'Q')
   {
      /*************************/
      /**** Move to a space ****/
      /*************************/
      if (choice == 'M')
      {
         //Get direction player would like to move
         getDirection(move, j);
         
         //Game ends if too many moves taken
         if (play.move(move))
         {
            std::cout << parse(j["lost"]["1"]);
            break;
         }
         
         //Display current location of player
         displayLocation(j);
         
         //Game is lost if bug spray is added to backpack
         if (play.searchBackpackItem("bug spray"))
         {
            std::cout << parse(j["lost"]["2"]);
            break;
         }
         
         //Bee makes a wager in arcade
         if (play.getLocation() == "Arcade" && !play.getQueenDoor())
         {
          std::cout << parse(j["arcade"]["1"]);
         }
         
         //Bee makes wager in dining hall
         else if (play.getLocation() == "Dining hall" && !play.getBearAte())
         {
            std::cout << parse(j["dining hall"]["1"]);
         }
         
         //Bee makes wager in dance room
         else if (play.getLocation() == "Dance room" && !play.getQueenDoor())
         {
            std::cout << parse(j["dance room"]["1"]);
         }
         
         //Queen gives player a key
         else if (play.getLocation() == "Queen lair" && play.searchBackpackItem("royal jelly")
                  && !play.getBearAte())
         {
            std::cout << parse(j["queen lair"]["1"]);
            
            play.removeBackpackItem("royal jelly");         //Item removed from backpack
            play.pickupItem("key");                         //Key is added to backpack
            play.bearEatsSpace();                           //Dance room is deleted from memory
            std::cout << parse(j["displayWorld"]["bear ate"][play.getLocation()]);
         }
         
         //Queen makes a hint
         else if (play.getLocation() == "Queen lair" && !play.getBearAte())
         {
            std::cout << parse(j["queen lair"]["2"]);
         }
         
         //A new space is created
         else if (play.getLocation() == "Graveyard" && play.searchBackpackItem("key") && !play.getKeyUsed())
         {
            std::cout << parse(j["graveyard"]["1"]);
            play.graveyardSecretDoor();                     //Worker bee lair is created
            play.removeBackpackItem("key");                 //Key removed from backpack
            std::cout << parse(j["displayWorld"]["key used"][play.getLocation()]);
         }
         
         //Player is given honey
         else if (play.getLocation() == "Worker bee lair")
         {
            std::cout << parse(j["worker bee lair"]["1"]);
            play.pickupItem("honey");                       //Honey is added to backpack
         }
         
         //You won the game
         else if (play.getLocation() == "Brood lair" && play.searchBackpackItem("honey"))
         {
            std::cout << parse(j["won"]);
            break;
         }
         
         //Bees make a wager
         else if ((play.getLocation() == "Brood lair" || play.getLocation() == "Graveyard"
                   || play.getLocation() == "Queen lair") && !play.getBearAte())
         {
            std::cout << parse(j["wager"]["1"]);
         }
      }
      
      /*************************/
      /**** Pick up an item ****/
      /*************************/
      else if (choice == 'P')
      {
         play.pickupSpaceItem();                            //Item is picked up
         
         //User is given a hint
         if (play.getLocation() == "Dining hall" && !play.getQueenDoor() && !play.getBearAte())
         {
            std::cout << parse(j["hint"]["1"]);
         }
      }
      
      /************************/
      /**** Deposit pollen ****/
      /************************/
      else if (choice == 'D')
      {
         play.dropPollen();                                 //Pollen is deposited
         
         //Notified if you have opened the Queen lair
         if (play.getLocation() == "Dance room" && play.unlockQueenLair())
         {
           std::cout << parse(j["dance room"]["2"]);
         }
         
         //Given hint to pick up jelly
         else if (play.getLocation() == "Dining hall")
         {
            std::cout << parse(j["dining hall"]["2"]);
         }
         
         //Notified if you have opened secret passages from arcade
         else if (play.getLocation() == "Arcade" && !play.getQueenDoor())
         {
            if (play.arcadeSecretPassages())
               std::cout << parse(j["arcade"]["2"]);
            else
               std::cout << parse(j["arcade"]["3"]);
         }
         
         //Notified if you were given a key to unlock the worker bee lair
         else if (play.getLocation() == "Brood lair" || play.getLocation() == "Graveyard"
                  || play.getLocation() == "Queen lair")
         {
            if (play.keyToWorkerBeeLair())
            {
               std::cout << parse(j["wager"]["2"]);
               play.pickupItem("key");                      //Key added to backpack
               
               //Your key is used if you're in the graveyard
               if (play.getLocation() == "Graveyard")
               {
                  std::cout << parse(j["graveyard"]["1"]);
                  play.graveyardSecretDoor();               //Worker bee lair is created
                  play.removeBackpackItem("key");           //Key removed from backpack
               }
               std::cout << parse(j["displayWorld"]["key used"][play.getLocation()]);
            }
            else if (!play.getBearAte() && !(play.getLocation() == "Queen lair"))
            {
               std::cout << parse(j["wager"]["3"]);
            }
         }
         
         //Game is lost if all pollen is gone
         if (play.getPollenCount() < 1)
         {
            std::cout << parse(j["lost"]["3"]);
            break;
         }
         std::cout << "\nPollen left: " << play.getPollenCount() << std::endl;
      }
      
      /**********************************/
      /***** Display backpack items *****/
      /**********************************/
      else if (choice == 'S')
      {
         play.displayItems();
      }
      
      /*********************************/
      /****** Explains how to win ******/
      /*********************************/
      else if ( choice == 'L')
      {
         std::cout << parse(j["cheat"]);
      }
      
      //User chooses menu option
      getMenuOption(choice, j);
   }
}
