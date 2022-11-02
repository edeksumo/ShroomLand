#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
class Keyboard
{
public:
	enum class KeyState : int {
		free = 0,
		pressed,
		hold,
		released
	};
	static void setKeyState(sf::Keyboard::Key a_key);
	static void setMouseButtonState(sf::Mouse::Button a_button);
	static Keyboard::KeyState checkKeyState(sf::Keyboard::Key a_key);
	static Keyboard::KeyState checkMouseButtonState(sf::Mouse::Button a_button);
	static void keyAndButtonStateSetter();
};

