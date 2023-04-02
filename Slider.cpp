#include "Slider.h"
/****************************************************/
//Private
/****************************************************/
void Slider::calculateEachPos()
{
	sliderPosVec.resize(maxValue + 1);
	sliderPosVec[0] = backgroundSprite.getLocalBounds().left;
	for (int i = 1; i <= maxValue; i++) {
		sliderPosVec[i] = sliderPosVec[0] + i * pxPerVal;
	}
}

bool Slider::isSliderSelected(sf::Vector2i* a_mousePos)
{
	if ((screenPositionRect.left <= a_mousePos->x) && (screenPositionRect.width >= a_mousePos->x)) {
		if ((screenPositionRect.top <= a_mousePos->y) && (screenPositionRect.height >= a_mousePos->y)) {
			drawSelector = true;
				return true;
		}
	}
	drawSelector = false;
	return false;
}

void Slider::slider(sf::Vector2i* a_mousePos)
{
	if (isHold) {
		if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold) {
			if (mouseX != a_mousePos->x) {
				tempOffset = a_mousePos->x - mouseX;
				if (tempOffset < 0) 
					tempOffset = 0;
				if (tempOffset > sliderPosVec[maxValue])
					tempOffset = sliderPosVec[maxValue];
				for (int i = 0; i <= maxValue; i++) {
					//if (tempOffset == static_cast<int>(sliderPosVec[i])) {
						sliderOffset = tempOffset;
					//}
				}
				value = (sliderOffset) / pxPerVal;
				if (value > maxValue)
					value = maxValue;

				screenPositionRect = sf::FloatRect(sliderShapeSprite.getLocalBounds().left + relativePosition.x + sliderOffset, sliderShapeSprite.getLocalBounds().top + relativePosition.y, sliderShapeSprite.getLocalBounds().left +
					sliderShapeSprite.getLocalBounds().width + relativePosition.x + sliderOffset, sliderShapeSprite.getLocalBounds().top + sliderShapeSprite.getLocalBounds().height + relativePosition.y);
			}
		}
	}
	if (isSliderSelected(a_mousePos) && Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::pressed) {
		mouseX = a_mousePos->x - tempOffset;
		isHold = true;
	}
	if (isHold && Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::released) {
		isHold = false;
	}
}

void Slider::setOffset()
{
	if (!isHold) {
		sliderOffset = static_cast<int>(sliderPosVec[value]);
		tempOffset = sliderOffset;
		screenPositionRect = sf::FloatRect(sliderShapeSprite.getLocalBounds().left + relativePosition.x + sliderOffset, sliderShapeSprite.getLocalBounds().top + relativePosition.y, sliderShapeSprite.getLocalBounds().left +
			sliderShapeSprite.getLocalBounds().width + relativePosition.x + sliderOffset, sliderShapeSprite.getLocalBounds().top + sliderShapeSprite.getLocalBounds().height + relativePosition.y);
	}
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void Slider::setValue(int a_val)
{
	value = a_val;
}

int Slider::getValue()
{
	return value;
}

int Slider::getMaxValue()
{
	return maxValue;
}

void Slider::Update(sf::Vector2i* a_mousePos)
{
	setOffset();
	slider(a_mousePos);
	//std::cout << "== SWITCH == Update Func" << std::endl;
}

void Slider::Render(sf::RenderTarget* a_target)
{
	view = a_target->getView();
	p_rTarget = a_target;
	keepOnPosition();
	a_target->draw(backgroundSprite);
	a_target->draw(sliderDecorLeft);
	a_target->draw(SliderDecorRight);
	a_target->draw(sliderShapeSprite);
	if ((isHold) || (drawSelector))
		a_target->draw(shadow);


	//std::cout << "== SWITCH == Render Func" << std::endl;
}
