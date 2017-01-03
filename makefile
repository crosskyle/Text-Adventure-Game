#Kyle Cross
#Final Project CS 162

all: game

game: main.o ArcadeSpace.o Beehive.o DanceSpace.o DiningSpace.o GenericSpace.o gamePlay.o Player.o Space.o
	clang++ -std=c++11 -stdlib=libc++ main.o ArcadeSpace.o Beehive.o DanceSpace.o DiningSpace.o GenericSpace.o gamePlay.o Player.o Space.o -o game

main.o: main.cpp
	clang++ -std=c++11 -stdlib=libc++ -c main.cpp

ArcadeSpace.o: ArcadeSpace.cpp
	clang++ -std=c++11 -stdlib=libc++ -c ArcadeSpace.cpp

Beehive.o: Beehive.cpp
	clang++ -std=c++11 -stdlib=libc++ -c Beehive.cpp

DanceSpace.o: DanceSpace.cpp
	clang++ -std=c++11 -stdlib=libc++ -c DanceSpace.cpp

DiningSpace.o: DiningSpace.cpp
	clang++ -std=c++11 -stdlib=libc++ -c DiningSpace.cpp

GenericSpace.o: GenericSpace.cpp
	clang++ -std=c++11 -stdlib=libc++ -c GenericSpace.cpp

gamePlay.o: gamePlay.cpp
	clang++ -std=c++11 -stdlib=libc++ -c gamePlay.cpp

Player.o: Player.cpp
	clang++ -std=c++11 -stdlib=libc++ -c Player.cpp

Space.o: Space.cpp
	clang++ -std=c++11 -stdlib=libc++ -c Space.cpp

clean:
	rm *.o game
