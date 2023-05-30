#include "Sprite.h"
unsigned int Sprite::ID_COUNTER = 0;
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void Sprite::SetPosition(GridCell a_pos)
{
	posOnGrid = a_pos;
	sprite.setPosition(sf::Vector2f(a_pos.x * TILE_SIZE, a_pos.y * TILE_SIZE));
	if (hasHitbox) {
		hitbox.setPosition(sprite.getPosition().x + hitboxPos.x, sprite.getPosition().y + hitboxPos.y);
	}
}

void Sprite::SetPosition(sf::Vector2f a_pos)
{
	sprite.setPosition(sf::Vector2f(a_pos.x, a_pos.y));
	if (hasHitbox) {
		hitbox.setPosition(sprite.getPosition().x + hitboxPos.x, sprite.getPosition().y + hitboxPos.y);
	}
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

sf::FloatRect Sprite::getHitboxWorldRect()
{
	return hitbox.getGlobalBounds();
}

void Sprite::Render(sf::RenderTarget* a_target)
{
	a_target->draw(sprite);
	if (hasHitbox)
		if (p_dM->Settings.hitboxes)
			a_target->draw(hitbox);
}
