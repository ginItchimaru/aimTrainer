#include <iostream>
#include "Game.h"


int main() {

	//Init srand							   // starts timer in seconds for the rng(random number generator)
	srand(static_cast<unsigned>(time(NULL)));  // to make sure a new number is generated everytime
												   
	//init Game class
	Game game;

	//Game loop
	while (game.running()) {
		
		//Update
		game.update();

		//Render
		game.render();
	}


	//End of application
	return 0;
}