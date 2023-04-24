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
void Sprite::animation()
{
	animFrame++;
	auto& r = sprite.getTextureRect();
	if (animFrame == 20)
		sprite.setTextureRect(sf::IntRect(r.left + 256, r.top, r.width, r.height));
	if (animFrame == 20)
		animFrame = 0;
}
void Sprite::SetPosition(GridCell a_pos)
{
	posOnGrid = a_pos;
	sprite.setPosition(sf::Vector2f(a_pos.x * TILE_SIZE, a_pos.y * TILE_SIZE));
}

void Sprite::flipSprite()
{
	auto r = sprite.getTextureRect();
	sprite.setTextureRect(sf::IntRect(r.left + r.width, r.top, -r.width, r.height));
}

GridCell Sprite::GetGridPosition()
{
	return posOnGrid;
}

void Sprite::Render(sf::RenderTarget* a_target)
{
	a_target->draw(sprite);
}
