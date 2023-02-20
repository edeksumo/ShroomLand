#pragma once
#include <iostream>
#include "Window.h"
#include "MainMenuState.h"
#include <string>
class Game
{
private:
	unsigned int Wight;
	unsigned int Height;
	double Version;
	std::string Title;
	sf::RectangleShape shape;
	std::stack<State*> States;
	sf::Vector2i mousePosition;

	sf::View view;

	DataMenager dataMenager;
	ObjectMenager* objMenager;
	MainMenuState *MainMenu;

	void LoadStages();
	void Keyboard();
	void Render();
	void Begin();
	void Update();
protected:

public:
	sf::RenderWindow* Window;
	sf::Event Event;

	std::multimap<std::string, Stage> StageContainer;			//stores all stages in the game
	std::multimap<int, Tile*> TilePtrContainer;					//stores all objects in the game 
	/****************************************************/
	//Constructors/ destructor
	/****************************************************/
	Game() {
		Wight = 800;
		Height = 600;
		Version = 0.000001;
		Title = dataMenager.Lang.gameName + " " + to_string(Version) + "v";
		view.setSize(static_cast<float> (Wight), static_cast<float> (Height));
		Window = new sf::RenderWindow(sf::VideoMode(Wight, Height), Title);
		Window->setKeyRepeatEnabled(false);
		MainMenu = new MainMenuState(&StageContainer, Window, &dataMenager, objMenager, &States);
		objMenager = new ObjectMenager(&dataMenager, &TilePtrContainer);
		Begin();
		LoadStages();
		Update();
	};
	~Game() {
		delete Window;
		delete MainMenu;
		delete objMenager;
	};
};

