#include "Keyboard.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
static std::array<Keyboard::KeyState, sf::Keyboard::KeyCount> keyState;
static std::array<Keyboard::KeyState, sf::Mouse::ButtonCount> mouseButtonState;
void Keyboard::setKeyState(sf::Keyboard::Key a_key)
{
	if (a_key > sf::Keyboard::KeyCount)
		return;

	if (sf::Keyboard::isKeyPressed(a_key)) {
		if (keyState[a_key] == Keyboard::KeyState::free) {
			keyState[a_key] = Keyboard::KeyState::pressed;
			return;
		}
		if (keyState[a_key] == Keyboard::KeyState::pressed) {
			keyState[a_key] = Keyboard::KeyState::hold;
			return;
		}
		if (keyState[a_key] == Keyboard::KeyState::hold) {
			return;
		}
	}
	else if(keyState[a_key] != Keyboard::KeyState::free){
		if (keyState[a_key] == Keyboard::KeyState::released) {
			keyState[a_key] = Keyboard::KeyState::free;
			return;
		}
		if (keyState[a_key] == Keyboard::KeyState::hold) {
			keyState[a_key] = Keyboard::KeyState::released;
			return;
		}
	}
}

void Keyboard::setMouseButtonState(sf::Mouse::Button a_button)
{
	if (a_button > sf::Mouse::ButtonCount)
		return;

	if (sf::Mouse::isButtonPressed(a_button)) {
		if (mouseButtonState[a_button] == Keyboard::KeyState::free) {
			mouseButtonState[a_button] = Keyboard::KeyState::pressed;
			return;
		}
		if (mouseButtonState[a_button] == Keyboard::KeyState::pressed) {
			mouseButtonState[a_button] = Keyboard::KeyState::hold;
			return;
		}
		if (mouseButtonState[a_button] == Keyboard::KeyState::hold) {
			return;
		}
	}
	else if (mouseButtonState[a_button] != Keyboard::KeyState::free) {
		if (mouseButtonState[a_button] == Keyboard::KeyState::released) {
			mouseButtonState[a_button] = Keyboard::KeyState::free;
			return;
		}
		if (mouseButtonState[a_button] == Keyboard::KeyState::hold) {
			mouseButtonState[a_button] = Keyboard::KeyState::released;
			return;
		}
	}
}

Keyboard::KeyState Keyboard::checkKeyState(sf::Keyboard::Key a_key)
{
	return keyState[a_key];
}

Keyboard::KeyState Keyboard::checkMouseButtonState(sf::Mouse::Button a_button)
{
	return mouseButtonState[a_button];
}

void Keyboard::keyAndButtonStateSetter()
{
	setMouseButtonState(sf::Mouse::Left);
	setKeyState(sf::Keyboard::A);
	setKeyState(sf::Keyboard::Escape);
}