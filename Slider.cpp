#include "Slider.h"
/****************************************************/
//Private
/****************************************************/
void Slider::calculateEachPos()
{
	sliderPosVec.resize(maxValue + 1);
	sliderPosVec[0] = background.getLocalBounds().left + 5;
	for (int i = 1; i <= maxValue; i++) {
		sliderPosVec[i] = sliderPosVec[0] + i * pxPerVal;
	}
	for (int i = 0; i <= maxValue; i++) {
		std::cout << sliderPosVec[i] << " ";
	}
	//sliderPosVec[maxValue] = background.getPosition().x;;
}
bool Slider::isSliderSelected(sf::Vector2i* a_mousePos)
{
	if ((screenPositionRect.left <= a_mousePos->x) && (screenPositionRect.width >= a_mousePos->x)) {
		if ((screenPositionRect.top <= a_mousePos->y) && (screenPositionRect.height >= a_mousePos->y)) {
				return true;
		}
	}
	return false;
}
void Slider::slider(sf::Vector2i* a_mousePos)
{
	if (isHold) {
		if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold) {
			if (mouseX != a_mousePos->x) {
				tempOffset = a_mousePos->x - mouseX;
				if (tempOffset < 5)
					tempOffset = 5;
				if (tempOffset > sliderPosVec[maxValue])
					tempOffset = sliderPosVec[maxValue];
				for (int i = 0; i <= maxValue; i++) {
					if (tempOffset == static_cast<int>(sliderPosVec[i])) {
						sliderOffset = tempOffset;
					}
				}
				value = sliderOffset / pxPerVal;
				if (value >maxValue)
					value = maxValue;
				std::cout << tempOffset << " ";

				screenPositionRect = sf::FloatRect(sliderShape.getLocalBounds().left + relativePosition.x + 5 + sliderOffset, sliderShape.getLocalBounds().top + relativePosition.y + 5, sliderShape.getLocalBounds().left + sliderShape.getSize().x + relativePosition.x + 5 + sliderOffset,
					sliderShape.getLocalBounds().top + sliderShape.getSize().y + relativePosition.y + 5);
			}
		}
	}
	if (isSliderSelected(a_mousePos) && Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::pressed) {
		mouseX = a_mousePos->x - tempOffset;
		//mouseX = a_mousePos->x;

		//std::cout << a_mousePos->x;

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
		screenPositionRect = sf::FloatRect(sliderShape.getLocalBounds().left + relativePosition.x + 5 + sliderOffset, sliderShape.getLocalBounds().top + relativePosition.y + 5, sliderShape.getLocalBounds().left + sliderShape.getSize().x + relativePosition.x + 5 + sliderOffset,
			sliderShape.getLocalBounds().top + sliderShape.getSize().y + relativePosition.y + 5);
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
	keepOnPosition();
	a_target->draw(background);
	a_target->draw(sliderShape);
	renderShadow(a_target);

	//std::cout << "== SWITCH == Render Func" << std::endl;
}
