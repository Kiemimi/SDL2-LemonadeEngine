#include "Entity.h"
#include "Maths.h"

//Takes some variables that we can send to create the entity and render it with whatever variables we need
Entity::Entity( Vector2f p_pos, 
				SDL_Texture* p_tex, 
				Vector2f dim,
				SDL_RendererFlip flip):pos(p_pos), tex(p_tex)
{
	//In this case, we make a rect with two bottom variables we can use to initiate their position from Main
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = dim.x;
	currentFrame.h = dim.y;
}

//We can use this to retrieve and change the reference to our texture (this restricts it's access to make debugging easier, as we know only one class can change it's value)
SDL_Texture* Entity::getTex()
{
	return tex;
}

//Read above, this is the same for the rect holding it's transform values
SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
