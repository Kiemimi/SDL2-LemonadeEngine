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

	std::vector<Entity> entities = {Entity(Vector2f(0, 0), backgroundTexture, Vector2f(1280, 720)),
									Entity(Vector2f(0, 656), grassTexture, Vector2f(64, 64)),
									Entity(Vector2f(64, 656), grassTexture, Vector2f(64, 64)),
									Entity(Vector2f(64 + (1 * 64), 656), grassTexture, Vector2f(64, 64)),
									Entity(Vector2f(64 + (2 * 64), 656), grassTexture, Vector2f(64, 64)),
									Entity(Vector2f(64 + (3 * 64), 656), grassTexture, Vector2f(64, 64)),
									Entity(Vector2f(64 + (4 * 64), 656), grassTexture, Vector2f(64, 64)),
									Entity(Vector2f(64 + (5 * 64), 656), grassTexture, Vector2f(64, 64)),
									Entity(Vector2f(64 + (6 * 64), 656), grassTexture, Vector2f(64, 64)),
									Entity(Vector2f(64 + (7 * 64), 656), grassTexture, Vector2f(64, 64)),
									};
									

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
			for (int i = 0; i < entities.size(); i++){
				//Entity newVector(Vector2f(32, 430), grassTexture);
				//entities.push_back(newVector);
				window.render(ent);
			}
		}

		window.display();
		
		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / window.getRefreshRate()) 
		{
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}

		Vector2f print();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}