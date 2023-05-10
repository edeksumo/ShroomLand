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
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f - TILE_SIZE / 2, sprite.getLocalBounds().height - TILE_SIZE / 2);
	hitbox.setOrigin(sprite.getLocalBounds().width / 2.f - TILE_SIZE / 2, sprite.getLocalBounds().height - TILE_SIZE / 2);
}
