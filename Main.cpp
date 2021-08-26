//Just get our header files that have classes that make our code tidier, and some libraries that'll handle some functions for us
#include "RenderWindow.h"
#include "Entity.h"
#include "Utils.h"
#include "Maths.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

int main(int argv, char* args[])
{
	//If SDL fails to initialise then throw an error
	if (SDL_Init(SDL_INIT_VIDEO) > 0) 
	{
		std::cout << "SDL_Init has failed. SDL_ERROR: " << SDL_GetError() << std::endl;
	} 

	//If SDL_Image fails to initialise then throw an error
	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG_INIT has failed. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	//Spawn the window that we'll render to
	RenderWindow window("LemonadeEngine 1.0", 1280, 720);

	//Create references to our assets
	SDL_Texture* backgroundTexture = window.loadTexture("Assets/Images/Bg_Background.png");
	SDL_Texture* grassTexture = window.loadTexture("Assets/Images/Sp_Grass1.png");
	SDL_Texture* playerIdle = window.loadTexture("Assets/Images/SPR_player.png");

	//Create a standard vector that indexes all of our assets, including size and position
	std::vector<Entity> entities = {Entity(Vector2f(0, 0), backgroundTexture, Vector2f(1280, 720))};

	//For loop that generates ground tile assets along the floor, saves more space than manually putting them into the vector
	for (int i = 0; i < 100; i++) {
		Entity newVector(Vector2f(128 * i, 656), grassTexture, Vector2f(128, 64));
		entities.push_back(newVector);
	}					

	//This sets up the main game loop, and can help close out memory leaks as a stop measure
	bool gameRunning = true;

	//Creating an instance of SDL_Events, this allows us to take inputs and events and run code based on them
	SDL_Event event;

	//References Utils.h which creates a deltaTime equivalent system for the game, and caps the framerate to the refresh rate of the monitor
	float currentTime = utils::hireTimeInSeconds();
	float accumulator = 0.0f;
	const float timeStep = 0.01f;

	float p_x = 0.0f;
	float p_y = 0.0f;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	//While the game is running
	while (gameRunning)
	{
		//Get how many ticks have passed since the start of the game
		int startTick = SDL_GetTicks();

		//Gets how much time has passed in milliseconds since the start of the game
		float newTime = utils::hireTimeInSeconds();

		//Time between frames is determined by how quickly the code loop operates
		float frameTime = newTime - currentTime;

		//Catches the time up to make it consistent between loops through the code
		currentTime = newTime;

		//Adds the frame time to a timer called accumulator that handles the consistent game loop
		accumulator += frameTime;
		
		Entity Player(Vector2f(p_x, p_y), playerIdle, Vector2f(64, 64), flipType);

		if (p_y < 656 - 48) {
			int velocity = p_y + 10;
			float acceleration = velocity * frameTime;
			p_y += acceleration;
		}
		else {
			p_y = 656 - 48;
		}

		//While the game is running
		while (accumulator >= timeStep) 
		{
			//Look for an SDL event
			while (SDL_PollEvent(&event))
			{
				//If we find an event for SDL_QUIT
				if (event.type == SDL_QUIT)
				{
					//Set gameRunning to false, closing the game loop.
					gameRunning = false;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_a:
						p_x -= 10 * timeStep * 50;
						flipType = SDL_FLIP_VERTICAL;
						std::cout << flipType << std::endl;
						break;
					case SDLK_d:
						p_x += 10 * timeStep * 50;
						flipType = SDL_FLIP_VERTICAL;
						std::cout << flipType << std::endl;
						break;
					case SDLK_SPACE:
						p_y -= 100;
						break;
					}
				}
			}
			//Count time to check if the game is actively running
			accumulator -= timeStep;
		}

		//This acts as our deltaTime, a number that we can multiply variables by to ensure consistency no matter what the frame rate of the game is
		const float alpha = accumulator / timeStep;
	
		//Clears the screen to render the new frame, preventing unintended renderer behavior.
		window.clear();

		//Loops through every index in the standard vector
		for (Entity& ent : entities) 
		{
			//Renders all of our standard vector with entity indexes to the screen for display
			window.render(ent);
			window.render(Player);
		}
		
		//Displays the window with objects rendered to it
		window.display();
		int frameTicks = SDL_GetTicks() - startTick;

		//Handles the Vsync for the game
		if (frameTicks < 1000 / window.getRefreshRate()) 
		{
			//Delay the game in-between frames
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}
	}

	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDLK_q]) {
		std::cout << "please work" << std::endl;
	}

	//When the gameRunning loop ends, clean up the window
	window.cleanUp();
	
	//Exit SDL
	SDL_Quit();

	//Mandatory return 0 statement that SDL requires, this doesn't do anything
	return 0;
}