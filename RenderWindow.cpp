#include "RenderWindow.h"
#include "Entity.h"

RenderWindow::RenderWindow(const char* title, int width, int height):window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity)
{
	SDL_Rect src;
		src.x = entity.getCurrentFrame().x;
		src.y = entity.getCurrentFrame().y;
		src.w = entity.getCurrentFrame().w;
		src.h = entity.getCurrentFrame().h;

	SDL_Rect dst;
		dst.x = entity.getPos().x * 2;
		dst.y = entity.getPos().y * 2;
		dst.w = entity.getCurrentFrame().w * 2;
		dst.h = entity.getCurrentFrame().h * 2;

	SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}
