#pragma once

#include<SFML/Graphics.hpp>
#include "Window.h"
#include "ObjectMenager.h"
#include <list>
class State
{
private:
	void Keyboard();
	void defaultButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it);
	int nbOfOpenedWindows;
protected:
	sf::Window* p_window;
	DataMenager* p_dM;
	ObjectMenager* p_oM;
	std::stack<State*>* p_state;
	std::multimap<std::string, Stage>* p_stageContainer;
	std::list<Window> Windows;
	std::list<Window>::iterator OpenedWindow;
	void updateOpenedWindowIt();
public:
	State() {
		p_dM = nullptr;
		p_oM = nullptr;
		p_state = nullptr;
		p_window = nullptr;
		p_stageContainer = nullptr;
		stateQuit = false;
		nbOfOpenedWindows = 0;
	}
	bool stateQuit;

	void PushWindow(unsigned int a_id, sf::Vector2f a_pos, sf::Vector2f a_size, std::string a_text, sf::Vector2f a_textPos, sf::Color a_textColor);
	void RenderWindows(sf::RenderTarget* a_target);
	void UpdateWindows(sf::Vector2i* a_mousePos);
	virtual void Render(sf::RenderTarget *a_target) = 0;
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
};

