#include "Button.h"
/****************************************************/
//Private
/****************************************************/
bool Button::onEnter()
{
	return false;
}

bool Button::onQuit()
{
	return false;
}


bool Button::isPressed()
{
	if (buttonState == ButtonState::Pressed)
		return true;
	return false;
}


/****************************************************/
//Protected
/****************************************************/
bool Button::mouseEnter(sf::Vector2i* a_mousePos)
{
	if (buttonState == ButtonState::Pressed) {
		return false;
	}
	if ((screenPositionRect.left <= a_mousePos->x) && (screenPositionRect.width >= a_mousePos->x))
		if ((screenPositionRect.top <= a_mousePos->y) && (screenPositionRect.height >= a_mousePos->y)) {
			buttonState = ButtonState::Selected;
			return true;
		}
	return false;
}

bool Button::mouseQuit(sf::Vector2i* a_mousePos)
{
	if ((buttonState != ButtonState::Selected))
		return false;
	if ((screenPositionRect.left >= a_mousePos->x) || (screenPositionRect.width < a_mousePos->x) || ((screenPositionRect.top >= a_mousePos->y) || (screenPositionRect.height <= a_mousePos->y))) {
		buttonState = ButtonState::Free;
		return true;
	}
	return false;
}

bool Button::pressed(sf::Vector2i* a_mousePos)
{
	if (isSwitch) {
		if ((buttonState == ButtonState::Selected) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::pressed)) {
			buttonState = ButtonState::Pressed;
			return true;
		}
		if ((screenPositionRect.left <= a_mousePos->x) && (screenPositionRect.width >= a_mousePos->x)) {
			if ((screenPositionRect.top <= a_mousePos->y) && (screenPositionRect.height >= a_mousePos->y)) {
				if ((buttonState == ButtonState::Pressed) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::pressed)) {
					buttonState = ButtonState::Selected;
					return false;
				}
			}
		}
	}
	else {
		if ((buttonState == ButtonState::Selected) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::pressed)) {
			buttonState = ButtonState::Pressed;
			return true;
		}
		if ((buttonState == ButtonState::Pressed || (buttonState == ButtonState::Hold) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold))) {
			buttonState = ButtonState::Hold;
			return true;
		}

		if ((buttonState == ButtonState::Pressed || buttonState == ButtonState::Hold)
			&& (Keyboard::checkMouseButtonState(sf::Mouse::Left) != Keyboard::KeyState::hold) || (Keyboard::checkMouseButtonState(sf::Mouse::Left) != Keyboard::KeyState::pressed)) {
			buttonState = ButtonState::Free;
			return false;
		}

	}
	return false;
}
void Button::setTransparency()
{
	if (lastButtonState == buttonState)
		return;
	if (buttonState == ButtonState::Selected) {
		selector.setFillColor(sf::Color(0, 0, 0, 50));
	}
	else if (buttonState == ButtonState::Pressed || buttonState == ButtonState::Hold) {
		selector.setFillColor(sf::Color(0, 0, 0, 100));
	}
	lastButtonState = buttonState;
}
void Button::drawSelector(sf::RenderTarget* a_target)
{
	if ((buttonState == ButtonState::Selected) || (buttonState == ButtonState::Pressed || buttonState == ButtonState::Hold))
		a_target->draw(selector);
}
/****************************************************/
//Public
/****************************************************/

void Button::Update(sf::Vector2i* a_mousePos) {
	//std::cout << "== BUTTON == Update Func" << std::endl;
	
	pressed(a_mousePos);
	mouseEnter(a_mousePos);
	mouseQuit(a_mousePos);
}

void Button::Render(sf::RenderTarget* a_target) {
	view = a_target->getView();
	keepOnPosition();
	a_target->draw(background);
	a_target->draw(text);
	setTransparency();
	drawSelector(a_target);
	renderShadow(a_target);
	//std::cout << "== BUTTON == Render Func" << std::endl;
}