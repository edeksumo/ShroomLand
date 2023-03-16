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
void Sprite::SetPosition(GridCell a_pos, int a_shifted)
{
	posOnGrid = a_pos;
	sprite.setPosition(sf::Vector2f(a_pos.x * 32, a_pos.y * 32));
	
	if(a_shifted == 0)
		sprite.setPosition(sf::Vector2f((a_pos.x * 32) - 16, (a_pos.y * 32) - 16));	//left up
	else if (a_shifted == 1)
		sprite.setPosition(sf::Vector2f(a_pos.x * 32, (a_pos.y * 32) - 16));	//up
	if (a_shifted == 2)
		sprite.setPosition(sf::Vector2f((a_pos.x * 32) + 16, (a_pos.y * 32) - 16));	// right up
	else if (a_shifted == 3)
		sprite.setPosition(sf::Vector2f(a_pos.x * 32 + 16, (a_pos.y * 32)));	//right
	else if (a_shifted == 4)
		sprite.setPosition(sf::Vector2f(a_pos.x * 32 + 16, (a_pos.y * 32) + 16));	//right down 
	else if (a_shifted == 5)
		sprite.setPosition(sf::Vector2f(a_pos.x * 32, (a_pos.y * 32) + 16));	//down
	else if (a_shifted == 6)
		sprite.setPosition(sf::Vector2f((a_pos.x * 32) - 16, (a_pos.y * 32) + 16));	//left down
	else if (a_shifted == 7)
		sprite.setPosition(sf::Vector2f((a_pos.x * 32) - 16, a_pos.y * 32));	//left
	

}

void Sprite::setShift(Sprite::shifted a_shift)
{
	shift = a_shift;
}

void Sprite::flipSprite()
{
	auto r = sprite.getTextureRect();
	sprite.setTextureRect(sf::IntRect(r.left + r.width, r.top, -r.width, r.height));
}

Sprite::shifted Sprite::getShift()
{
	return shift;
}

GridCell Sprite::GetGridPosition()
{
	return posOnGrid;
}

void Sprite::Render(sf::RenderTarget* a_target)
{
	a_target->draw(sprite);
}
