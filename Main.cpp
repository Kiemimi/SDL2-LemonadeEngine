#include "RenderWindow.h"
#include "Entity.h"

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

	Entity background0(0, 0, backgroundTexture);

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
		window.render(background0);
		window.display();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}