#include "RenderWindow.h"
#include "Entity.h"
#include "Utils.h"
#include "Maths.h"
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
	SDL_Texture* grassTexture = window.loadTexture("Assets/Images/Sp_Grass1.png");

	std::vector<Entity> entities =  {Entity(Vector2f(0, 0), backgroundTexture, Vector2f(1280, 720)),
									};

	for (int i = 0; i < 100; i++) {
		Entity newVector(Vector2f(128 * i, 656), grassTexture, Vector2f(128, 64));
		entities.push_back(newVector);
	}					

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

		for (Entity& ent : entities) 
		{
			window.render(ent);
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