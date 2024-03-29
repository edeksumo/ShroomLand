#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
class Keyboard
{
public:
	enum class KeyState : int {
		none = -1,
		free = 0,
		pressed,
		hold,
		released
	};
	enum class MouseWheel {
		free = 0,
		up,
		down
	};
	
	static void print(std::string a_text, bool a_nextLine = true);
	static void print(int a_text, bool a_nextLine = true);
	static void setKeyState(sf::Keyboard::Key a_key, KeyState a_state = KeyState::none);
	static void setMouseButtonState(sf::Mouse::Button a_button, KeyState a_state = KeyState::none);
	static Keyboard::KeyState checkKeyState(sf::Keyboard::Key a_key);
	static Keyboard::KeyState checkMouseButtonState(sf::Mouse::Button a_button);
	static void keyAndButtonStateSetter();
	static void resetWheel();
	static void resetButtons();
	static void setWheelState(sf::Event* a_event);
	static Keyboard::MouseWheel mouseWheel();
};

