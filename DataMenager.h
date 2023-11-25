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
		string freeCam = "Free Camera:";
	};

	struct EngineNames {
		string volume = "volume";
		string settings = "settings";
		string volumeText = "volumeText";
		string volumeSlider = "volumeSlider";
		string hitboxSwitch = "hitboxSwitch";
		string freeCam = "freeCam";
	};

	struct Settings {
		int volume;
		bool hitboxes;
		bool freeCam;
	};

	struct SaveFormat {
		string SaveFileName = "Stages.dat";
		string StageDefiner = "STAGE";
		string ObjectDefiner = "OBJ";
		string TileDefiner = "TILE";
		string BackTileDefiner = "BACK_TILE";
		string StaticObjectDefiner = "STATIC_OBJ";
		string InteractableObjectDefiner = "INTERACTABLE_OBJ";
		string PlayerObjectDefiner = "PLAYER_OBJ";
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

	//Objects
	sf::Texture objectsTxt;
	sf::Texture chestsTxt;

	sf::Texture pinkTree01Anim;
	sf::Texture greenTree01Anim;
	sf::Texture waterAnim;

	sf::Texture playerTxt;

	/****************************************************/
	//GUI textures
	/****************************************************/
	sf::Texture windowsBackgroundTxt;

	sf::Texture windowsDecorUpLineTxt;
	sf::Texture windowsDecorLeftUpCornerTxt;
	sf::Texture windowsDecorLeftLineTxt;
	sf::Texture windowsDecorUpRightCornerTxt;
	sf::Texture windowsDecorRightLineTxt;
	sf::Texture windowsDecorDownRightCornerTxt;
	sf::Texture windowsDecorDownLineTxt;
	sf::Texture windowsDecorDownLeftCornerTxt;


	sf::Texture buttonBackgroundTxt;
	sf::Texture buttonDecorUpLineTxt;
	sf::Texture buttonDecorUpLeftCornerTxt;
	sf::Texture buttonDecorDownLineTxt;
	sf::Texture buttonDecorDownLeftCornerTxt;
	sf::Texture buttonDecorLeftLineTxt;
	sf::Texture buttonDecorUpRightCornerTxt;
	sf::Texture buttonDecorRightLineTxt;
	sf::Texture buttonDecorDownRightCornerTxt;

	sf::Texture switchBackgroundTxt;
	sf::Texture switchBackgroundTickTxt;

	sf::Texture sliderTxt;
	sf::Texture sliderBackgroundTxt;
	sf::Texture sliderLeftDecorTxt;
	sf::Texture sliderRightDecorTxt;

	//////Graphical buttons textures
	sf::Texture buttonTickTxt;
	sf::Texture buttonCrossTxt;
	sf::Texture buttonLeftTxt;
	sf::Texture buttonRightTxt;
	sf::Texture buttonUpTxt;
	sf::Texture buttonDownTxt;
	sf::Texture buttonPlusTxt;
	sf::Texture buttonMinusTxt;
	sf::Texture buttonNoneTxt;

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

		//objects
		if (!objectsTxt.loadFromFile("data/textures/Dec_props2.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: Dec_props2.png" << std::endl;
		if (!chestsTxt.loadFromFile("data/textures/chest.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: chest.png" << std::endl;

		//animations
		if (!pinkTree01Anim.loadFromFile("data/textures/tree1A.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: tree1A.png" << std::endl;
		if (!greenTree01Anim.loadFromFile("data/textures/tree2A.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: tree2A.png" << std::endl;
		if (!waterAnim.loadFromFile("data/textures/water_effB.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: water_effB.png" << std::endl;

		//player
		if (!playerTxt.loadFromFile("data/textures/BODY_male.png"))
			cout << "== DATAMENAGER ERROR == Texture not loaded: chest.png" << std::endl;

		/****************************************************/
		//GUI textures
		/****************************************************/
		if(!windowsBackgroundTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(5, 237, 130, 130)))
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		windowsBackgroundTxt.setRepeated(true);
		//////////////////////////////////////////////////////
		if (!windowsDecorUpLineTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(14, 224, 133, 12))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		windowsDecorUpLineTxt.setRepeated(true);

		if (!windowsDecorLeftUpCornerTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(0, 224, 13, 13))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}

		if (!windowsDecorRightLineTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(150, 238, 11, 133))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		windowsDecorRightLineTxt.setRepeated(true);

		if (!windowsDecorDownLeftCornerTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(0, 371, 13, 13))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}

		if (!windowsDecorDownLineTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(14, 379, 133, 5))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		windowsDecorDownLineTxt.setRepeated(true);

		if (!windowsDecorUpRightCornerTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(147, 224, 13, 13))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}

		if (!windowsDecorLeftLineTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(0, 238, 5, 133))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		windowsDecorLeftLineTxt.setRepeated(true);

		if (!windowsDecorDownRightCornerTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(147, 371, 13, 13))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		//////////////////////////////////////////////////////
		if (!buttonBackgroundTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(6, 8, 60, 3))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		buttonBackgroundTxt.setRepeated(true);

		if (!buttonDecorUpLineTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(86, 2, 68, 6))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		buttonDecorUpLineTxt.setRepeated(true);

		if (!buttonDecorUpLeftCornerTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(82, 2, 4, 4))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}

		if (!buttonDecorDownLineTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(86, 11, 68, 3))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		buttonDecorDownLineTxt.setRepeated(true);

		if (!buttonDecorDownLeftCornerTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(82, 10, 4, 4))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}

		if (!buttonDecorLeftLineTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(82, 4, 4, 6))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		buttonDecorLeftLineTxt.setRepeated(true);

		if (!buttonDecorUpRightCornerTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(154, 2, 4, 4))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}

		if (!buttonDecorRightLineTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(154, 4, 5, 7))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		buttonDecorRightLineTxt.setRepeated(true);

		if (!buttonDecorDownRightCornerTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(154, 10, 4, 4))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		/////////////////////////////////////////////////////////
		if (!switchBackgroundTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(0, 0, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!switchBackgroundTickTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(64, 160, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}

		if (!sliderTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(210, 227, 12, 26))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		if (!sliderBackgroundTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(93, 51, 53, 10))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		sliderBackgroundTxt.setRepeated(true);
		if (!sliderLeftDecorTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(82, 50, 11, 12))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}
		if (!sliderRightDecorTxt.loadFromFile("data/textures/UI_Steel_Flat.png", sf::IntRect(147, 50, 11, 12))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_Flat.png" << std::endl;
		}

		//////////////Graphical buttons textures
		if (!buttonTickTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(64, 160, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!buttonCrossTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(32, 160, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!buttonLeftTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(288, 256, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!buttonRightTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(160, 256, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!buttonUpTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(32, 256, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!buttonDownTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(544, 224, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!buttonPlusTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(448, 128, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!buttonMinusTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(383, 128, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}
		if (!buttonNoneTxt.loadFromFile("data/textures/UI_Steel_A_NoBorder.png", sf::IntRect(0, 0, 32, 32))) {
			cout << "== DATAMENAGER ERROR == Texture not loaded: UI_Steel_A_NoBorder.png" << std::endl;
		}

		//Settings
		settings = new mINI::INIFile("settings.ini");
		buttonFont.loadFromFile("assets/fonts/alagard.ttf");
		settings->read(settingsINI);
		std::string& volumeStr = settingsINI[EngineNames.settings][EngineNames.volume];
		Settings.volume = std::stoi(volumeStr);
		Settings.hitboxes = true;
		std::string& freeCamStr = settingsINI[EngineNames.settings][EngineNames.freeCam];
		Settings.freeCam = std::stoi(freeCamStr);
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

