#include "RenderWindow.h"
#include "Entity.h"
#include "Utils.h"
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

	std::vector<Entity> entities = {Entity(Vector2f(0, 0), backgroundTexture),
									Entity(Vector2f(50, 50), backgroundTexture),
									Entity(Vector2f(100, 100), backgroundTexture),
									Entity(Vector2f(150, 150), backgroundTexture)};

	bool gameRunning = true;

	SDL_Event event;

	float currentTime = utils::hireTimeInSeconds();
	float accumulator = 0.0f;
	const float timeStep = 0.01f;

	while (gameRunning)
	{
		int startTick = SDL_GetTicks();
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= timeStep) 
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					gameRunning = false;
				}
			}

			accumulator -= timeStep;
		}

		const float alpha = accumulator / timeStep;
		
		window.clear();

		for (Entity& e : entities) 
		{
			window.render(e);
		}

		window.display();
		
		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / window.getRefreshRate()) 
		{
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}