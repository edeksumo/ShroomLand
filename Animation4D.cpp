#include "Animation4D.h"

/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

string Animation4D::getName()
{
	return name;
}

Animation* Animation4D::GetAnimation(Animation::Direction a_facing)
{
	switch (a_facing)
	{
	case Animation::Direction::up:
		return upFacingAnimation;
		break;
	case Animation::Direction::down:
		return downFacingAnimation;
		break;
	case Animation::Direction::left:
		return leftFacingAnimation;
		break;
	case Animation::Direction::right:
		return rightFacingAnimation;
		break;
	default:
		return nullptr;
		break;
	}
}
