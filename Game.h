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
	sf::Vector2f worldPos;

	sf::View view;

	DataMenager dataMenager;
	ObjectMenager* objMenager;
	MainMenuState *MainMenu;
	Camera* MainCamera;

	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime;
	sf::Time currentTime;


	void LoadStages();
	void Keyboard();
	void Render();
	void Begin();
	void secondThead();
	void Update();
protected:

public:
	sf::RenderWindow* Window;
	sf::Event Event;

	std::multimap<std::string, Stage> StageContainer;			//stores all stages in the game
	std::vector<std::string> StageNames;						//stores all stage names
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
		objMenager = new ObjectMenager(&dataMenager);
		MainCamera = new Camera(Window, sf::Vector2f(800.f, 600.f));
		LoadStages();
		MainMenu = new MainMenuState(&StageContainer, &StageNames, Window, Window, MainCamera, &dataMenager, objMenager, &States, &Event);
		previousTime = clock.getElapsedTime();

		MainCamera->ActiveCamera();
		Begin();
		//LoadStages();
		Update();
	};
	~Game() {
		delete Window;
		delete MainMenu;
		delete objMenager;
		delete MainCamera;
	};
};

