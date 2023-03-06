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

	struct SaveFormat {
		string SaveFileName = "Stages.dat";
		string StageDefiner = "STAGE";
		string ObjectDefiner = "OBJ";
		string TileDefiner = "TILE";
		string BackTileDefiner = "BACK_TILE";
	};

	struct StagesNames {
		string Overworld = "Owerwold";
		string House_01 = "House_01";
	};

	Lang Lang;
	Settings Settings;
	EngineNames EngineNames;
	SaveFormat SaveFormat;
	StagesNames StagesNames;		//unused for now
	/****************************************************/
	//Obj textures
	/****************************************************/
	sf::Texture grassTileSet;
	sf::Texture dirtTileSet;
	sf::Texture sandTileSet;
	sf::Texture gravelTileSet;
	sf::Texture forrestTileSet;
	sf::Texture waterTileSet;
	/****************************************************/
	//GUI textures
	/****************************************************/
	sf::Texture windowsBackgroundTxt;
	sf::Texture windowsDecorLineTxt;
	sf::Texture windowsDecorCornerTxt;

	sf::Texture buttonBackgroundTxt;
	sf::Texture buttonDecorLineTxt;
	sf::Texture buttonDecorCornerTxt;

	sf::Texture switchBackgroundTxt;
	sf::Texture switchBackgroundTickTxt;

	sf::Texture sliderTxt;
	sf::Texture sliderBackgroundTxt;
	sf::Texture sliderDecorTxt;

	DataMenager() {
		//Texture loaders
		/****************************************************/
		//Obj textures
		/****************************************************/
		if (!grassTileSet.loadFromFile("data/textures/grass.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: grass.png" << std::endl;
		if (!dirtTileSet.loadFromFile("data/textures/dirt.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: dirt.png" << std::endl;
		if (!sandTileSet.loadFromFile("data/textures/sand.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: sand.png" << std::endl;
		if (!gravelTileSet.loadFromFile("data/textures/gravel.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: gravel.png" << std::endl;
		if (!forrestTileSet.loadFromFile("data/textures/forrest.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: forrest.png" << std::endl;
		if (!waterTileSet.loadFromFile("data/textures/water.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: water.png" << std::endl;
		waterTileSet.setRepeated(true);
		/****************************************************/
		//GUI textures
		/****************************************************/
		if(!windowsBackgroundTxt.loadFromFile("data/textures/paper background.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: paper background.png" << std::endl;

		if (!windowsDecorLineTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(893, 190, 73, 14))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}
		windowsDecorLineTxt.setRepeated(true);

		if (!windowsDecorCornerTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(857, 190, 22, 22))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}

		if (!buttonBackgroundTxt.loadFromFile("data/textures/wood background.png")) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: wood background.png" << std::endl;
		}
		if (!buttonDecorLineTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(900, 401, 74, 8))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}
		buttonDecorLineTxt.setRepeated(true);

		if (!buttonDecorCornerTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(868, 401, 14, 14))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}

		if (!switchBackgroundTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(150, 85, 20, 20))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}
		if (!switchBackgroundTickTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(175, 85, 20, 20))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}

		if (!sliderTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(815, 20, 16, 28))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}
		if (!sliderBackgroundTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(802, 63, 192, 28))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: RPG_GUI_v1.png" << std::endl;
		}
		sliderBackgroundTxt.setRepeated(true);
		if (!sliderDecorTxt.loadFromFile("data/textures/RPG_GUI_v1.png", sf::IntRect(561, 18, 25, 28))) {
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

