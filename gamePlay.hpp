

#include "Beehive.hpp"
#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <fstream>
#include <string>

class GamePlay
{
private:
   Beehive play;
   string parse(string stringIn);
   char chooseMenuOption(char &choice);
   void printWorld();
   
public:
   void playGame();
};
