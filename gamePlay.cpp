

#include "gamePlay.hpp"



string GamePlay::parse(string stringIn) {
   string s = stringIn;
   s.erase(remove(s.begin(), s.end(), '\"'), s.end());
   
   return s;
}



char GamePlay::getMenuOption(char &choice, json j) {
   //Menu option is chosen
   cout << parse(j["menu"]);
   cin.clear();
   cin >> choice;
   choice = toupper(choice);
   
   //Input validation
   while (!cin || (choice != 'M' && choice != 'P' && choice != 'D' && choice != 'S'
                   && choice != 'L' && choice != 'Q'))
   {
      cout << "Enter a valid character." << endl;
      cin.ignore(10000,'\n');
      cin >> choice;
      choice = toupper(choice);
   }
   
   return choice;
}



char GamePlay::getDirection(char &move, json j) {
   do
   {
      cin.ignore(10000,'\n');
      cout << parse(j["choose direction"]);
      cin >> move;
      move = toupper(move);
      
   } while (!cin || (move != 'N' && move != 'S' && move != 'E' && move != 'W'));

   return move;
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
   ifstream gameText("/Users/kylecross/Desktop/text-adventure-game/text-adventure-game/gameText.json");
   json j;
   gameText >> j;
   
   //Starting instructions
   cout << parse(j["start"]);
   cout << parse(j["displayWorld"]);                     //Prints world map
   cout << parse(j["arcade"]["4"]);                      //Start in arcade room
   
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
         cout << parse(j["displayWorld"]);
         
         getDirection(move, j);
         
         //Game ends if too many moves taken
         if (play.move(move))
         {
            cout << parse(j["lost"]["1"]);
            break;
         }
         cout << "\nCurrent location: " << play.getLocation() << endl;
         
         //Game is lost if bug spray is added to backpack
         if (play.searchBackpackItem("bug spray"))
         {
            cout << parse(j["lost"]["2"]);
            break;
         }
         
         //Bee makes a wager in arcade
         if (play.getLocation() == "Arcade" && !play.getQueenDoor())
         {
          cout << parse(j["arcade"]["1"]);
         }
         
         //Bee makes wager in dining hall
         else if (play.getLocation() == "Dining hall" && !play.getBearAte())
         {
            cout << parse(j["dining hall"]["1"]);
         }
         
         //Bee makes wager in dance room
         else if (play.getLocation() == "Dance room" && !play.getQueenDoor())
         {
            cout << parse(j["dance room"]["1"]);
         }
         
         //Queen gives player a key
         else if (play.getLocation() == "Queen lair" && play.searchBackpackItem("royal jelly")
                  && !play.getBearAte())
         {
            cout << parse(j["queen lair"]["1"]);
            
            play.removeBackpackItem("royal jelly");         //Item removed from backpack
            play.pickupItem("key");                         //Key is added to backpack
            play.bearEatsSpace();                           //Dance room is deleted from memory
         }
         
         //Queen makes a hint
         else if (play.getLocation() == "Queen lair" && !play.getBearAte())
         {
            cout << parse(j["queen lair"]["2"]);
         }
         
         //A new space is created
         else if (play.getLocation() == "Graveyard" && play.searchBackpackItem("key") && !play.getKeyUsed())
         {
            cout << parse(j["graveyard"]["1"]);
            play.graveyardSecretDoor();                     //Worker bee lair is created
            play.removeBackpackItem("key");                 //Key removed from backpack
         }
         
         //Player is given honey
         else if (play.getLocation() == "Worker bee lair")
         {
            cout << parse(j["worker bee lair"]["1"]);
            play.pickupItem("honey");                       //Honey is added to backpack
         }
         
         //You won the game
         else if (play.getLocation() == "Brood lair" && play.searchBackpackItem("honey"))
         {
            cout << parse(j["won"]);
            break;
         }
         
         //Bees make a wager
         else if ((play.getLocation() == "Brood lair" || play.getLocation() == "Graveyard"
                   || play.getLocation() == "Queen lair") && !play.getBearAte())
         {
            cout << parse(j["wager"]["1"]);
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
            cout << parse(j["hint"]["1"]);
         }
      }
      
      /************************/
      /**** Deposit pollen ****/
      /************************/
      else if (choice == 'D')
      {
         play.dropPollen();                                 //Pollen is deposited
         
         //Notified if you have opend the Queen lair
         if (play.getLocation() == "Dance room" && play.unlockQueenLair())
         {
            cout << parse(j["dance room"]["2"]);
         }
         
         //Given hint to pick up jelly
         else if (play.getLocation() == "Dining hall")
         {
            cout << parse(j["dining hall"]["2"]);
         }
         
         //Notified if you have opened secret passages from arcade
         else if (play.getLocation() == "Arcade" && !play.getQueenDoor())
         {
            if (play.arcadeSecretPassages())
               cout << parse(j["arcade"]["2"]);
            else
               cout << parse(j["arcade"]["3"]);
         }
         
         //Notified if you were given a key to unlock the worker bee lair
         else if (play.getLocation() == "Brood lair" || play.getLocation() == "Graveyard"
                  || play.getLocation() == "Queen lair")
         {
            if (play.keyToWorkerBeeLair())
            {
               cout << parse(j["wager"]["2"]);
               play.pickupItem("key");                      //Key added to backpack
               
               //Your key is used if you're in the graveyard
               if (play.getLocation() == "Graveyard")
               {
                  cout << parse(j["graveyard"]["1"]);
                  play.graveyardSecretDoor();               //Worker bee lair is created
                  play.removeBackpackItem("key");           //Key removed from backpack
               }
            }
            else if (!play.getBearAte())
            {
               cout << parse(j["wager"]["3"]);
            }
         }
         
         //Game is lost if all pollen is gone
         if (play.getPollenCount() < 1)
         {
            cout << parse(j["lost"]["3"]);
            break;
         }
         cout << "\nPollen left: " << play.getPollenCount() << endl;
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
         cout << parse(j["cheat"]);
      }
      
      //User chooses menu option
      getMenuOption(choice, j);
   }
}
