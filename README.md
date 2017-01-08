# text-adventure-game

A text adventure game. The player is an ant navigating through a beehive in search of honey that will save the ant's colony from collapse.

The game is implemented with an object-oriented approach. There are multiple derived space classes that allow the player to interact with each space differently as the player navigates the beehive. The spaces are linked to each other in a beehive class that holds all the spaces in a linked structure. The beehive class also has a player class that keeps track of multiple player attributes. The player has a backpack to pickup items throught the game and a set amount of pollen grains that are used to interact with the spaces in the beehive. A game loop is implemented in a gameplay class.

The game text is located in a separate file in JSON format. The json.hpp file, which holds a C++ JSON library, is included to allow the game text file to be read in.
