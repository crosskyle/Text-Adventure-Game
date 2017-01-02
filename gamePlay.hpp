

#include "Beehive.hpp"
#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <fstream>
#include <string>


 
class GamePlay
{
public:
   string parse(string stringIn) {
      string s = stringIn;
      s.erase(remove(s.begin(), s.end(), '\"'), s.end());
      
      return s;
   }
   void printWorld();
   void playGame();
};
