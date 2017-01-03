

#include "Beehive.hpp"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;


class GamePlay
{
private:
   char choice;
   char move;
   Beehive play;
   string parse(string stringIn);
   char getMenuOption(char &choice, json j);
   char getDirection(char &move, json j);
   
public:
   void playGame();
};
