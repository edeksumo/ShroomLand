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
	if (buttonState == ButtonState::Pressed) {
		buttonState = ButtonState::Hold;
		return true;
	}
	return false;
}
/****************************************************/
//Protected
/****************************************************/
bool Button::mouseEnter(sf::Vector2i* a_mousePos)
{
	if (buttonState == ButtonState::Pressed || buttonState == ButtonState::Hold) {
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

	if ((buttonState == ButtonState::Selected) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::pressed)) {
		buttonState = ButtonState::Pressed;
		if (isSwitch) {
			if (state == SwitchState::off) {
				state = SwitchState::on;
				//std::cout << "on";
			}
			else {
				state = SwitchState::off;
				//std::cout << "off";
			}
		}
		//std::cout << "pressed";
		return true;
	}
	if ((buttonState == ButtonState::Pressed || (buttonState == ButtonState::Hold)) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold)) {
		buttonState = ButtonState::Hold;
		//std::cout << "hold";
		return true;
	}
	if ((buttonState == ButtonState::Hold) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold)) {
		buttonState = ButtonState::Hold;
		//std::cout << "hold";
		return true;
	}

	if ((buttonState == ButtonState::Pressed || buttonState == ButtonState::Hold) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::free)) {
		buttonState = ButtonState::Free;
		//std::cout << "free";
		return false;
	}
	if ((buttonState != ButtonState::Free) && (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::released)) {
		buttonState = ButtonState::Free;
			//std::cout << "free";
			return false;
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
void Button::setText(std::string a_text)
{
	text.setString(a_text);
	auto textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height);
	text.setPosition(position.x + textPosition.x, position.y + textPosition.y);
}

void Button::setButtonState(Button::ButtonState a_state)
{
	buttonState = a_state;
}

void Button::Update(sf::Vector2i* a_mousePos) {
	//std::cout << "== BUTTON == Update Func" << std::endl;
	
	pressed(a_mousePos);
	mouseEnter(a_mousePos);
	mouseQuit(a_mousePos);
}

void Button::Render(sf::RenderTarget* a_target) {
	view = a_target->getView();
	p_rTarget = a_target;
	keepOnPosition();
	a_target->draw(backgroundSprite);
	if (hasBorders) {
		a_target->draw(upperDecorLine);
		a_target->draw(lowerDecorLine);
		a_target->draw(leftDecorLine);
		a_target->draw(rightDecorLine);
		a_target->draw(upperDecorLeftCorn);
		a_target->draw(lowerDecorLeftCorn);
		a_target->draw(upperDecorRightCorn);
		a_target->draw(lowerDecorRightCorn);
	}
	a_target->draw(text);
	setTransparency();
	drawSelector(a_target);
	//std::cout << "== BUTTON == Render Func" << std::endl;
}