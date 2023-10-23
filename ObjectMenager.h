#pragma once
#include"Tile.h"
#include"StaticObject.h"
#include"InteractableObject.h"
#include"Player.h";
#include <map>

class ObjectMenager
{
private:
	DataMenager* p_dM;
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5]);		//default isTilable = true, needBackgroundTile = true
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5], bool a_isTilable, bool a_needBackgroundTile, unsigned int a_nbOfVariants);		//customazible isTilable and needBackground, zero is first variant
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[5][7], bool a_isTilable, bool a_needBackgroundTile, unsigned int a_nbOfVariants);		//customazible isTilable and needBackground, zero is first variant
	
	void addPrefab(int a_ID, Object* a_obj);
	void createStaticObjPrefab(sf::Texture* a_texture, StaticObject* a_staticObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox);
	void createInteractableObjPrefab(sf::Texture* a_texture, InteractableObject* a_intractableObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox);
	void createPlayerObjPrefab(sf::Texture* a_texture, Player* a_playerObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox);

protected:

public:
	////////////////////////////////////////////////
	/// Tiles
	////////////////////////////////////////////////
	
	Tile* grass[11][5];		//full tileset for grass in one array
	Tile* muddyGrass[11][5];
	Tile* mood01[11][5];
	Tile* mood02[11][5];
	Tile* water01[11][5];

	Tile* clif01[5][7];	// [5][7]
	std::multimap<int, Tile*> TilePtrContainer;					//stores all Tiles pointer in the game 

	Tile* getTilePtrById(int a_ID);

	////////////////////////////////////////////////
	/// Objects
	////////////////////////////////////////////////
	
	StaticObject* tree;
	StaticObject* tree2;
	StaticObject* bush_01;
	StaticObject* bush_02;
	StaticObject* stemp_01;

	InteractableObject* chest_01;

	Player* character;

	std::multimap<int, StaticObject*> StaticObjectPtrContainer;					//stores all StaticObject pointer in the game
	std::multimap<int, InteractableObject*> InteractableObjectPtrContainer;		//stores all InteractableObject pointer in the game
	std::multimap<int, Player*> PlayerObjectPtrContainer;		//stores all InteractableObject pointer in the game
	std::multimap<int, Object*> ObjectsPrefabs;									//Stores all object pointers to prefabs
	
	Object* getObjectPtrById(int a_ID);

	ObjectMenager() {

	}

	ObjectMenager(DataMenager* m_dM) {
		p_dM = m_dM;
		tilesetPrefabCreater(&p_dM->grassTileSet, grass);
		tilesetPrefabCreater(&p_dM->muddyGrassTileSet, muddyGrass);
		tilesetPrefabCreater(&p_dM->moodTileSet, mood01);
		tilesetPrefabCreater(&p_dM->mood02TileSet, mood02);
		tilesetPrefabCreater(&p_dM->water01TileSet, water01, true, true, 4);
		tilesetPrefabCreater(&p_dM->clif01Tiles, clif01, false, true, 0);

		createStaticObjPrefab(&p_dM->objectsTxt, tree, sf::IntRect(0, 0, 160, 224), true, sf::IntRect(20, -30, 50, 120));
		createStaticObjPrefab(&p_dM->objectsTxt, tree2, sf::IntRect(160, 0, 160, 224), true, sf::IntRect(20, -30, 50, 120));
		createStaticObjPrefab(&p_dM->objectsTxt, bush_01, sf::IntRect(0, 224, 64, 96), true, sf::IntRect(0, -20, 40, 55));
		createStaticObjPrefab(&p_dM->objectsTxt, bush_02, sf::IntRect(64, 224, 64, 96), true, sf::IntRect(0, -20, 40, 55));
		createStaticObjPrefab(&p_dM->objectsTxt, stemp_01, sf::IntRect(128, 224, 96, 128), true, sf::IntRect(0, -20, 40, 55));

		createInteractableObjPrefab(&p_dM->chestsTxt, chest_01, sf::IntRect(0, 0, 64, 64), true, sf::IntRect(0, 0, 64, 64));

		createPlayerObjPrefab(&p_dM->playerTxt, character, sf::IntRect(0, 128, 64, 64), true, sf::IntRect(0, 0, 30, 46));
	};
	~ObjectMenager() {
		//delete grass[1][1];
	}
};

