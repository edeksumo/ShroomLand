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

void Object::resetLastPosition()
{
	lastPos = GetPosition();
}

bool Object::isSolid()
{
	return solid;
}

void Object::SetFacing(Animation::Direction a_facing)
{
	facing = a_facing;
}

Animation::Direction Object::GetFacing()
{
	return facing;
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

void Object::setState(Object::ObjectState a_state)
{
	state = a_state;
}

Object::ObjectState Object::getState()
{
	return state;
}

void Object::detectFacing()
{
	auto pos = GetPosition();
	if (pos.x > lastPos.x) {
		facing = Animation::Direction::right;
	}
	else if (pos.x < lastPos.x) {
		facing = Animation::Direction::left;
	}
	if (pos.y > lastPos.y) {
		facing = Animation::Direction::down;
	}
	else if (pos.y < lastPos.y) {
		facing = Animation::Direction::up;
	}
}

void Object::stateDetector()
{
	auto pos = GetPosition();
	if (pos != lastPos) {
		state = Object::ObjectState::moving;
	}
	else {
		state = Object::ObjectState::idle;
	}
}

void Object::animationControler()
{
	switch (state)
	{
	case Object::ObjectState::idle:
		GetAnimationMenager()->PlayAnimation("Idle", GetFacing());
		break;
	case Object::ObjectState::moving:
		GetAnimationMenager()->PlayAnimation("Walk", GetFacing());
		break;
	default:
		GetAnimationMenager()->PlayAnimation("Idle", GetFacing());
		break;
	}
}