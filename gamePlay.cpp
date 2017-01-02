

#include "gamePlay.hpp"

void GamePlay::printWorld()
{
   cout << " _______________________\n";
   cout << "|           |           |\n";
   cout << "|   Arcade    Brood lair|\n";
   cout << "|_____  ____|____  _____|\n";
   cout << "|           |           |\n";
   cout << "|Dance Room   Graveyard |\n";
   cout << "|_____  ____|____  _____|\n";
   cout << "|           |           |\n";
   cout << "|Queen lair  Dining hall|\n";
   cout << "|___________|___________|\n\n";
}

void GamePlay::playGame()
{
   ifstream a("/Users/kylecross/Desktop/text-adventure-game/text-adventure-game/gameText.json");
   json j;
   a >> j;
   
   Beehive play;
   char choice;                                    //Holds menu choice
   char move;                                      //Holds move direction
   
   //Starting instructions
   cout << parse(j["start"]["instructions1"]);
   printWorld();                                   //Prints world map
   cout << "Starting Location: " << play.getLocation() << endl << endl;
   cout << parse(j["start"]["instructions2"]);
   
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
   
   //User-controlled while loop
   while (choice != 'Q')
   {
      //Move to a space
      if (choice == 'M')
      {
         printWorld();
         
         //User inputs direction until valid
         do
         {
            cin.ignore(10000,'\n');
            cout << parse(j["choose direction"]);
            cin >> move;
            move = toupper(move);
            
         } while (!cin || (move != 'N' && move != 'S' && move != 'E' && move != 'W'));
         
         //Game ends if too many moves taken
         if (play.move(move))
         {
            cout << parse(j["ending"]["1"]);
            break;
         }
         cout << "\nCurrent location: " << play.getLocation() << endl << endl;
         
         //Game is lost if bug spray is added to backpack
         if (play.searchBackpackItem("bug spray"))
         {
            cout << parse(j["ending"]["2"]);
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
            cout << "\"If you deposit one pollen grain, we'll let you pick up ";
            cout << "something the queen might like.\"\n" << endl;
         }
         //Bee makes wager in dance room
         else if (play.getLocation() == "Dance room" && !play.getQueenDoor())
         {
            cout << "\"If you give us 2 pollen grains we'll open the doors ";
            cout << "to the queen lair!\"\n" << endl;
         }
         //Queen gives player a key
         else if (play.getLocation() == "Queen lair" && play.searchBackpackItem("royal jelly")
                  && !play.getBearAte())
         {
            cout << "The queen took your royal jelly and gave you a key. ";
            cout << "The key works where bees go to die. ";
            cout << "\n\"You MUST give some honey to the brood ";
            cout << "before you leave the beehive.\"\n\n";
            cout << "Wait! The beehive is shaking!!! A hungry bear ate the ";
            cout << "dance room!!!" << endl;
            
            play.removeBackpackItem("royal jelly");         //Item removed from backpack
            play.pickupItem("key");                         //Key is added to backpack
            play.bearEatsSpace();                           //Dance room is deleted from memory
         }
         //Queen makes a hint
         else if (play.getLocation() == "Queen lair" && !play.getBearAte())
         {
            cout << "\"I need royal jelly. Can you find some for me?\"\n" << endl;
         }
         //A new space is created
         else if (play.getLocation() == "Graveyard" && play.searchBackpackItem("key") && !play.getKeyUsed())
         {
            cout << "You used your key to open the door to the worker bees! ";
            cout << "The passage to the worker bees has opened. Go east.\n" << endl;
            
            play.graveyardSecretDoor();                     //Worker bee lair is created
            play.removeBackpackItem("key");                 //Key removed from backpack
         }
         //Player is given honey
         else if (play.getLocation() == "Worker bee lair")
         {
            cout << "\"Here's some honey! Give some to the brood before you leave.\"\n";
            cout << "Go north to reach the brood." << endl;
            
            play.pickupItem("honey");                       //Honey is added to backpack
         }
         //You won the game
         else if (play.getLocation() == "Brood lair" && play.searchBackpackItem("honey"))
         {
            cout << "\"Thanks for the honey!\"\nYou saved your ant colony!!!\n" << endl;
            break;
         }
         //Bees make a wager
         else if ((play.getLocation() == "Brood lair" || play.getLocation() == "Graveyard"
                   || play.getLocation() == "Queen lair") && !play.getBearAte())
         {
            cout << parse(j["wager"]["1"]);
         }
      }
      
      //Pick up an item
      else if (choice == 'P')
      {
         play.pickupSpaceItem();                            //Item is picked up
         
         //User is given a hint
         if (play.getLocation() == "Dining hall" && !play.getQueenDoor() && !play.getBearAte())
         {
            cout << parse(j["hint"]["1]"]);
         }
      }
      
      //Deposit pollen
      else if (choice == 'D')
      {
         play.dropPollen();                                 //Pollen is deposited
         
         //Notified if you have opend the Queen lair
         if (play.getLocation() == "Dance room" && play.unlockQueenLair())
         {
            cout << "\nYou have unlocked the doors to the Queen lair!" << endl;
         }
         //Given hint to pick up jelly
         else if (play.getLocation() == "Dining hall")
         {
            cout << "\nPick up the royal jelly." << endl;
         }
         //Notified if you have opened secret passages from arcade
         else if (play.getLocation() == "Arcade" && !play.getQueenDoor())
         {
            if (play.arcadeSecretPassages())
            {
               cout << parse(j["arcade"]["2"]);
            }
            else
            {
               cout << "\nYou lost pollen." << endl;
            }
         }
         //Notified if you were given a key to unlock the worker bee lair
         else if (play.getLocation() == "Brood lair" || play.getLocation() == "Graveyard"
                  || play.getLocation() == "Queen lair")
         {
            if (play.keyToWorkerBeeLair())
            {
               cout << "\nYou won the bet!";
               cout << "You were given a key to access the worker bee lair from the graveyard!" << endl;
               cout << "Wait! The beehive is shaking!!! A hungry bear ate the dance room!!!" << endl;
               
               play.pickupItem("key");                      //Key added to backpack
               
               //Your key is used if you're in the graveyard
               if (play.getLocation() == "Graveyard")
               {
                  cout << "\nYou used your key to open the door to the worker bees! ";
                  cout << "The passage to the worker bees has opened. Go east." << endl;
                  
                  play.graveyardSecretDoor();               //Worker bee lair is created
                  play.removeBackpackItem("key");           //Key removed from backpack
               }
            }
            else if (!play.getBearAte())
               cout << "You lost the bet :(" << endl;
         }
         
         //Game is lost if all pollen is gone
         if (play.getPollenCount() < 1)
         {
            cout << "\nYou lost all of your pollen. You lost.\n" << endl;
            break;
         }
         
         cout << "\nPollen left: " << play.getPollenCount() << endl << endl;
      }
      
      //Show backpack items
      else if (choice == 'S')
      {
         play.displayItems();
      }
      
      //Tells you how to win
      else if ( choice == 'L')
      {
         cout << "\nDISCLAIMER: This tells you how to win.\n" << endl;
         cout << "Go to the dining hall. Deposit one pollen grain. Then pickup an item there. ";
         cout << "Next go to the dance room and deposit two pollen grains. ";
         cout << "The queen lair will become unlocked. ";
         cout << "Next go to the queen lair. The queen gave you a key. Go to the graveyard. ";
         cout << "Your key opened the worker bee lair. Next go east to the worker bee lair. ";
         cout << "You were given honey. Go north to the brood lair to win.\n" << endl;
      }
      
      //User chooses menu option
      cout << parse(j["menu"]);
      cin >> choice;
      choice = toupper(choice);
      
      while (!cin || (choice != 'M' && choice != 'P' && choice != 'D' && choice != 'S'
                      && choice != 'L' && choice != 'Q'))
      {
         cout << "Enter a valid character." << endl;
         cin.ignore(10000,'\n');
         cin >> choice;
         choice = toupper(choice);
      }
   }
}
