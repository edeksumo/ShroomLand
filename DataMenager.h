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
		string hitboxes = "Show Hitboxes:";
	};

	struct EngineNames {
		string volume = "volume";
		string settings = "settings";
		string volumeText = "volumeText";
		string volumeSlider = "volumeSlider";
		string hitboxSwitch = "hitboxSwitch";
	};

	struct Settings {
		int volume;
		bool hitboxes;
	};

	struct SaveFormat {
		string SaveFileName = "Stages.dat";
		string StageDefiner = "STAGE";
		string ObjectDefiner = "OBJ";
		string TileDefiner = "TILE";
		string BackTileDefiner = "BACK_TILE";
		string StaticObjectDefiner = "STATIC_OBJ";
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
	//Obj names
	/****************************************************/
	std::string tileNames[6]{
	"grass",
	"mud_grass",
	"mud_01",
	"mud_02",
	"water",
	"other"
	};
	
	/****************************************************/
	//Obj textures
	/****************************************************/
	//Tiles
	sf::Texture emptyTxt;
	sf::Texture grassTileSet;
	sf::Texture muddyGrassTileSet;
	sf::Texture moodTileSet;
	sf::Texture mood02TileSet;
	sf::Texture cobbleTileSet;
	sf::Texture water01TileSet;
	sf::Texture clif01Tiles;

	sf::Texture tilerDecorTxt;

	//Objects
	sf::Texture objectsTxt;
	sf::Texture chestsTxt;

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

	/****************************************************/
	// Global Variables
	/****************************************************/

	unsigned int seed;

	/****************************************************/
	// Functions
	/****************************************************/
	int RNG(int a_seed, int a_numbers[], unsigned int a_sizeofArr);

	DataMenager() {
		//Texture loaders
		/****************************************************/
		//Obj textures
		/****************************************************/
		//tiles
		if (!emptyTxt.loadFromFile("data/textures/empty.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: empty.png" << std::endl;
		if (!grassTileSet.loadFromFile("data/textures/grass01.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: grass.png" << std::endl;
		if (!moodTileSet.loadFromFile("data/textures/Mood01.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: mood.png" << std::endl;
		if (!mood02TileSet.loadFromFile("data/textures/Mood02.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: mood02.png" << std::endl;
		if (!cobbleTileSet.loadFromFile("data/textures/cobble.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: cobble.png" << std::endl;
		if (!muddyGrassTileSet.loadFromFile("data/textures/muddyGrass.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: muddyGrass.png" << std::endl;
		if (!water01TileSet.loadFromFile("data/textures/water01.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: water01.png" << std::endl;
		water01TileSet.setRepeated(true);
		if (!clif01Tiles.loadFromFile("data/textures/clif.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: clif.png" << std::endl;
		if (!tilerDecorTxt.loadFromFile("data/textures/decor.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: decor.png" << std::endl;

		//objects
		if (!objectsTxt.loadFromFile("data/textures/Dec_props2.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: Dec_props2.png" << std::endl;
		if (!chestsTxt.loadFromFile("data/textures/chest.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: chest.png" << std::endl;

		/****************************************************/
		//GUI textures
		/****************************************************/
		if(!windowsBackgroundTxt.loadFromFile("data/textures/paper background.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: paper background.png" << std::endl;
		windowsBackgroundTxt.setRepeated(true);

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
		Settings.hitboxes = true;

	/****************************************************/
	// Global Variables
	/****************************************************/
		srand(time(NULL));
		seed = rand();
		std::cout << seed << std::endl;
	}
	~DataMenager() {
		delete settings;
	}
};

