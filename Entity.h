#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include "Maths.h"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* tex, Vector2f dim);
	Vector2f& getPos()
	{
		return pos;
	};
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};