#include "RenderWindow.h"
#include "Entity.h"
#include <vector>

int main(int argv, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init has failed. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG_INIT has failed. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	RenderWindow window("LemonadeEngine 1.0", 1280, 720);

	SDL_Texture* backgroundTexture = window.loadTexture("Assets/Images/Bg_Background.png");

	std::vector<Entity> entities = {Entity(0, 0, backgroundTexture),
									Entity(50, 50, backgroundTexture),
									Entity(120, 120, backgroundTexture),
									Entity(150, 150, backgroundTexture)};

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT) 
			{
				gameRunning = false;
			}	
		}
		window.clear();

		for (Entity& e : entities) 
		{
			window.render(e);
		}

		window.display();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}