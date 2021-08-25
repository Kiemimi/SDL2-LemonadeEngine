#include "Entity.h"
#include "Maths.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f dim):pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = dim.x;
	currentFrame.h = dim.y;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}