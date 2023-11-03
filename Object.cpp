#include "Object.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

bool Object::isSolid()
{
	return solid;
}

void Object::setObjectCenterOrigin()
{
	setObjectCenterOrigin(sf::Vector2f(0.f, 0.f));
}

void Object::setObjectCenterOrigin(sf::Vector2f a_offset)
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f - TILE_SIZE / 2 + a_offset.x, sprite.getLocalBounds().height - TILE_SIZE / 2 + a_offset.y);
	hitbox.setOrigin(hitbox.getLocalBounds().width / 2.f - TILE_SIZE / 2 + a_offset.x, hitbox.getLocalBounds().height - TILE_SIZE / 2 + a_offset.y);
}
