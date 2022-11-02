#pragma once

#include <iostream>
#include<SFML/Graphics.hpp>
#include "Window.h"
#include <list>
class State
{
private:
	void Keyboard();
	void defaultButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it);
protected:
	sf::Window* p_window;
	DataMenager* p_dM;
	std::stack<State*>* p_state;
	std::list<Window> Windows;

public:
	State() {
		p_dM = nullptr;
		p_state = nullptr;
		p_window = nullptr;
		stateQuit = false;
	}

	bool stateQuit;

	void PushWindow(unsigned int a_id, sf::Vector2f a_pos, sf::Vector2f a_size, sf::Color a_color, std::string a_text, sf::Vector2f a_textPos, sf::Color a_textColor);
	void RenderWindows(sf::RenderTarget* a_target);
	void UpdateWindows(sf::Vector2i* a_mousePos);
	virtual void Render(sf::RenderTarget *a_target) = 0;
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
};

