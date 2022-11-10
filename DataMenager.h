#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mini/ini.h"		//.ini file menager from Danijel Durakovic https://github.com/pulzed/mINI
using namespace std;
class DataMenager
{
private:

protected:

public:
	sf::Font buttonFont;
	mINI::INIStructure settingsINI;
	mINI::INIFile* settings;

	struct Lang {
		string yes = "Yes";
		string no = "No";
		string newGame = "New Game";
		string quit = "Quit";
		string settings = "Settings";
		string editor = "Editor";
		string quitDial = "Do you want quit";
		string gameName = "Schroomland";
		string save = "Save";
		string load = "Load";
		string volume = "Volume";
	};

	struct EngineNames {
		string volume = "volume";
		string settings = "settings";
		string volumeText = "volumeText";
		string volumeSlider = "volumeSlider";
		string settingsSwitch = "settingsSwitch";
	};

	struct Settings {
		int volume;
	};

	Lang Lang;
	Settings Settings;
	EngineNames EngineNames;
	sf::Texture windowsBackgroundTxt;
	sf::Texture windowsDecorLineTxt;
	sf::Texture windowsDecorCornerTxt;

	DataMenager() {
		//Texture loaders
		if(!windowsBackgroundTxt.loadFromFile("data/textures/paper background.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: paper background.png" << std::endl;

		if (!windowsDecorLineTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(893, 190, 73, 14))) {
			windowsDecorLineTxt.setRepeated(true);
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}
		if (!windowsDecorCornerTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(857, 190, 22, 22))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}
		//Settings
		settings = new mINI::INIFile("settings.ini");
		buttonFont.loadFromFile("assets/fonts/alagard.ttf");
		settings->read(settingsINI);
		std::string& volumeStr = settingsINI[EngineNames.settings][EngineNames.volume];
		Settings.volume = std::stoi(volumeStr);
	}
	~DataMenager() {
		delete settings;
	}
};

