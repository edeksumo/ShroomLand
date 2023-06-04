#pragma once

#include<SFML/Graphics.hpp>
#include "Window.h"
#include "Stage.h"
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
	sf::Event* p_event;
	std::stack<State*>* p_state;
	std::multimap<std::string, Stage>* p_stageContainer;
	std::vector<std::string>* p_stageNames;
	std::list<Window> Windows;
	std::list<Window>::iterator OpenedWindow;
	void updateOpenedWindowIt();
public:
	State() {
		p_dM = nullptr;
		p_oM = nullptr;
		p_event = nullptr;
		p_state = nullptr;
		p_window = nullptr;
		p_stageContainer = nullptr;
		p_stageNames = nullptr;
		stateQuit = false;
		nbOfOpenedWindows = 0;
	}
	bool stateQuit;

	void PushWindow(unsigned int a_id, sf::Vector2f a_pos, sf::Vector2f a_size, std::string a_text, sf::Vector2f a_textPos, sf::Color a_textColor);
	void RenderWindows(sf::RenderTarget* a_target);
	void UpdateWindows(sf::Vector2i* a_mousePos);
	virtual void Render(sf::RenderTarget *a_target) = 0;
	virtual void Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords) = 0;
};

