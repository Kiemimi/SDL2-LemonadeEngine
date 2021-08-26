#include "RenderWindow.h"
#include "Entity.h"

//The absolute bare bones for rendering to a window
RenderWindow::RenderWindow(const char* title, int width, int height):window(NULL), renderer(NULL)
{
	//Create a window with some paramaters that we can tweak in Main()
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	
	//If the window fails to load, throw an error
	if (window == NULL) {
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	//Create the renderer to run on our window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

//Reference the memory address where the file path for our textures are, which will be stored in main
SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
	//Create the texture, but don't give it anything yet
	SDL_Texture* texture = NULL;

	//Get the image file from our file path and assign it to texture
	texture = IMG_LoadTexture(renderer, filePath);

	//If we can't retrieve the image, throw an error
	if (texture == NULL)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}

	//return the file path reference to the texture
	return texture;
}

//When this is called in main, destroy the window and renderer to make sure we get no memory leaks upon closing everything down
void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

//Gets the refresh rate of the display the game is running on
int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

//Wipes everything off our renderer to render new entities to it
void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

//Takes source and destination variables for displaying entities we pass through it to screen
void RenderWindow::render(Entity& entity)
{
	//Takes a rect, which holds our x and y position, and w and h dimensions, This is used to render 2D images
	SDL_Rect src;
		//Referencing entity to get the current position of our entities as the original location of the objects
		src.x = entity.getCurrentFrame().x;
		src.y = entity.getCurrentFrame().y;
		src.w = entity.getCurrentFrame().w;
		src.h = entity.getCurrentFrame().h;

	SDL_Rect dst;
		//Getting their new position to render them at the destination rect, only for our location however as we likely don't need to scale anything
		dst.x = entity.getPos().x;
		dst.y = entity.getPos().y;
		dst.w = entity.getCurrentFrame().w;
		dst.h = entity.getCurrentFrame().h;

	//Renders the textures from the source, to the destination
	SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);
}

//Send everything to the renderer
void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}
