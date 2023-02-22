#include "Sprite.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void Sprite::SetPosition(Grid a_pos)
{
	posOnGrid = a_pos;
	sprite.setPosition(sf::Vector2f(a_pos.x * 32, a_pos.y* 32));
}

Grid Sprite::GetGridPosition()
{
	return posOnGrid;
}

void Sprite::Render(sf::RenderTarget* a_target)
{
	a_target->draw(sprite);
}
