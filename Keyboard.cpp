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
static Keyboard::MouseWheel wheelDelta;

void Keyboard::print(std::string a_text, bool a_nextLine)
{
	std::cout << a_text;
	if (a_nextLine)
		std::cout << std::endl;
}

void Keyboard::print(int a_text, bool a_nextLine)
{
	print(std::to_string(a_text), a_nextLine);
}

void Keyboard::setKeyState(sf::Keyboard::Key a_key, KeyState a_state)
{
	if (a_key > sf::Keyboard::KeyCount)
		return;

	if (a_state != KeyState::none) {
		keyState[a_key] = a_state;
		return;
	}

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

void Keyboard::setMouseButtonState(sf::Mouse::Button a_button, KeyState a_state)
{
	if (a_button > sf::Mouse::ButtonCount)
		return;

	if (a_state != KeyState::none) {
		mouseButtonState[a_button] = a_state;
		return;
	}

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
	setMouseButtonState(sf::Mouse::Right);
	setKeyState(sf::Keyboard::A);
	setKeyState(sf::Keyboard::Escape);
	setKeyState(sf::Keyboard::Up);
	setKeyState(sf::Keyboard::Down);
	setKeyState(sf::Keyboard::Left);
	setKeyState(sf::Keyboard::Right);
	setKeyState(sf::Keyboard::Space);
	setKeyState(sf::Keyboard::BackSpace);
	setKeyState(sf::Keyboard::Home);
	setKeyState(sf::Keyboard::LShift);
}

void Keyboard::resetWheel()
{
	wheelDelta = Keyboard::MouseWheel::free;
}

void Keyboard::resetButtons()
{
	setMouseButtonState(sf::Mouse::Left, KeyState::free);
	setMouseButtonState(sf::Mouse::Right, KeyState::free);
	setKeyState(sf::Keyboard::A, KeyState::free);
	setKeyState(sf::Keyboard::Escape, KeyState::free);
	setKeyState(sf::Keyboard::Up, KeyState::free);
	setKeyState(sf::Keyboard::Down, KeyState::free);
	setKeyState(sf::Keyboard::Left, KeyState::free);
	setKeyState(sf::Keyboard::Right, KeyState::free);
	setKeyState(sf::Keyboard::Space, KeyState::free);
	setKeyState(sf::Keyboard::BackSpace, KeyState::free);
	setKeyState(sf::Keyboard::Home, KeyState::free);
	setKeyState(sf::Keyboard::LShift, KeyState::free);
}

void Keyboard::setWheelState(sf::Event *a_event)
{
	if (a_event->mouseWheel.delta < 0)
		wheelDelta = Keyboard::MouseWheel::down;
	else if (a_event->mouseWheel.delta > 0)
		wheelDelta = Keyboard::MouseWheel::up;
	else
		wheelDelta = Keyboard::MouseWheel::free;
}

Keyboard::MouseWheel Keyboard::mouseWheel()
{
	return wheelDelta;
}
