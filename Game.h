#pragma once
#include <iostream>
#include "Window.h"
#include "MainMenuState.h"
class Game
{
private:
	unsigned int Wight;
	unsigned int Height;
	std::string Title;
	sf::RectangleShape shape;
	std::stack<State*> States;
	sf::Vector2i mousePosition;

	sf::View view;

	DataMenager dataMenager;
	MainMenuState *MainMenu;

	void Keyboard();
	void Render();
	void Begin();
	void Update();
protected:

public:
	sf::RenderWindow* Window;
	sf::Event Event;
	/****************************************************/
	//Constructors/ destructor
	/****************************************************/
	Game() {
		Wight = 800;
		Height = 600;
		Title = "ShroomLand 0.0.1v";
		view.setSize(static_cast<float> (Wight), static_cast<float> (Height));
		Window = new sf::RenderWindow(sf::VideoMode(Wight, Height), Title);
		Window->setKeyRepeatEnabled(false);
		MainMenu = new MainMenuState(Window, &dataMenager, &States);
		Begin();
		Update();
	};
	~Game() {
		delete Window;
		delete MainMenu;
	};
};

