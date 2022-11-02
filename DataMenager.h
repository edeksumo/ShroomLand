#pragma once
#include <SFML/Graphics.hpp>
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
	struct Settings {
		int volume;
	};
	Lang Lang;
	Settings Settings;
	DataMenager() {
		settings = new mINI::INIFile("settings.ini");
		buttonFont.loadFromFile("assets/fonts/alagard.ttf");

		settings->read(settingsINI);

		std::string& volumeStr = settingsINI["settings"]["volume"];

		Settings.volume = std::stoi(volumeStr);
	}
	~DataMenager() {
		delete settings;
	}
};

