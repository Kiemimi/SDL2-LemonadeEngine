#include "Entity.h"
#include "Maths.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex):pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 512;
	currentFrame.h = 256;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

