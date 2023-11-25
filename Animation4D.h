#pragma once
#include "Animation.h"
class Animation4D
{
private:
	string name;
	Animation* upFacingAnimation;
	Animation* downFacingAnimation;
	Animation* leftFacingAnimation;
	Animation* rightFacingAnimation;
protected:

public:
	Animation4D() {
		name = "";
		upFacingAnimation = nullptr;
		downFacingAnimation = nullptr;
		leftFacingAnimation = nullptr;
		rightFacingAnimation = nullptr;
	}
	Animation4D(string m_name, Animation* m_upFacingAnimation, Animation* m_downFacingAnimation, Animation* m_leftFacingAnimation, Animation* m_rightFacingAnimation) {
		name = m_name;
		upFacingAnimation = m_upFacingAnimation;
		downFacingAnimation = m_downFacingAnimation;
		leftFacingAnimation = m_leftFacingAnimation;
		rightFacingAnimation = m_rightFacingAnimation;
	}
	string getName();
	Animation* GetAnimation(Animation::Direction a_facing);
};

