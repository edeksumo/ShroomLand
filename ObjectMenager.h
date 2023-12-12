#pragma once
#include"Tile.h"
#include"StaticObject.h"
#include"InteractableObject.h"
#include"SpecialObject.h"
#include"Player.h";
#include <map>

class ObjectMenager
{
private:
	DataMenager* p_dM;

	Sprite* GetLastIDSpritePtr();

	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5]);		//default isTilable = true, needBackgroundTile = true
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5], bool a_isTilable, bool a_isWalkable, bool a_needBackgroundTile, unsigned int a_nbOfVariants);		//customazible isTilable and needBackground, zero is first variant
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[5][7], bool a_isTilable, bool a_isWalkable, bool a_needBackgroundTile, unsigned int a_nbOfVariants);		//customazible isTilable and needBackground, zero is first variant
	
	void addPrefab(int a_ID, Object* a_obj);
	void createStaticObjPrefab(sf::Texture* a_texture, StaticObject* a_staticObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool a_isAnimated);
	void createInteractableObjPrefab(sf::Texture* a_texture, InteractableObject* a_intractableObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool a_isAnimated);
	void createPlayerObjPrefab(sf::Texture* a_texture, Player* a_playerObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool a_isAnimated);
	void createSpecialObjPrefab(sf::Texture* a_texture, SpecialObject* a_specialObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool a_isAnimated);

	void addAnimationToLastPrefab(string a_name, sf::Texture* a_texture, sf::Vector2f a_textureOffset, size_t a_nbOfFrames, float a_speed, sf::Vector2i a_sizeOfFrame/*size in pixels*/, sf::Vector2i a_spriteSheetSize /*size in frames*/,
		Animation::repeatMode a_mode, sf::Sprite* a_sprite, sf::Texture a_defTexture /*texture of original sprite*/, bool m_fliped, bool m_upsideDown);
	void createAnimation4DToLastPrefab(string a_name, string a_upFacingAnim, string a_downFacingAni, string a_leftFacingAnim, string a_rightFacingAnim);
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
	StaticObject* waterEff01;
	StaticObject* grass_01;
	StaticObject* grass_02;
	StaticObject* grass_03;
	StaticObject* grass_04;
	StaticObject* waterBamboo_01;
	StaticObject* waterBamboo_02;
	StaticObject* waterBamboo_03;

	InteractableObject* chest_01;

	Player* character;

	SpecialObject* changeZone;

	std::multimap<int, StaticObject*> StaticObjectPtrContainer;					//stores all StaticObject pointer in the game
	std::multimap<int, InteractableObject*> InteractableObjectPtrContainer;		//stores all InteractableObject pointer in the game
	std::multimap<int, Player*> PlayerObjectPtrContainer;		//stores all PlayerObject pointer in the game
	std::multimap<int, SpecialObject*> SpecialObjectPtrContainer;		//stores all SpecialObject pointer in the game
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
		tilesetPrefabCreater(&p_dM->water01TileSet, water01, true, false, true, 4);
		tilesetPrefabCreater(&p_dM->clif01Tiles, clif01, false, false, true, 0);

		createStaticObjPrefab(&p_dM->objectsTxt, tree, sf::IntRect(0, 0, 160, 224), true, sf::IntRect(20, -30, 35, 50), true);
		addAnimationToLastPrefab("Idle", &m_dM->greenTree01Anim, sf::Vector2f(0.f, 0.f), 10, 0.05f, sf::Vector2i(160, 224), sf::Vector2i(2, 5), Animation::repeatMode::circle, nullptr, m_dM->objectsTxt, true, false);
		createStaticObjPrefab(&p_dM->objectsTxt, tree2, sf::IntRect(160, 0, 160, 224), true, sf::IntRect(20, -30, 35, 50), true);
		addAnimationToLastPrefab("Idle", &m_dM->pinkTree01Anim, sf::Vector2f(0.f, 0.f), 10, 0.05f, sf::Vector2i(160, 224), sf::Vector2i(2, 5), Animation::repeatMode::circle, nullptr, m_dM->objectsTxt, true, false);
		createStaticObjPrefab(&p_dM->objectsTxt, bush_01, sf::IntRect(0, 224, 64, 96), true, sf::IntRect(0, -20, 20, 30), false);
		createStaticObjPrefab(&p_dM->objectsTxt, bush_02, sf::IntRect(64, 224, 64, 96), true, sf::IntRect(0, -20, 20, 30), false);
		createStaticObjPrefab(&p_dM->objectsTxt, stemp_01, sf::IntRect(128, 224, 96, 128), true, sf::IntRect(0, -20, 30, 30), false);

		createInteractableObjPrefab(&p_dM->chestsTxt, chest_01, sf::IntRect(0, 0, 64, 64), true, sf::IntRect(0, 0, 64, 64), false);

		createPlayerObjPrefab(&p_dM->playerTxt, character, sf::IntRect(0, 128, 64, 64), true, sf::IntRect(1, 0, 20, 22), true);
		addAnimationToLastPrefab("IdleUp", &m_dM->playerTxt, sf::Vector2f(0.f, 0.f), 1, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 1), Animation::repeatMode::circle, nullptr, m_dM->playerTxt, false, false);
		addAnimationToLastPrefab("IdleLeft", &m_dM->playerTxt, sf::Vector2f(0.f, 64.f), 1, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 1), Animation::repeatMode::circle, nullptr, m_dM->playerTxt, false, false);
		addAnimationToLastPrefab("IdleDown", &m_dM->playerTxt, sf::Vector2f(0.f, 128.f), 1, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 1), Animation::repeatMode::circle, nullptr, m_dM->playerTxt, false, false);
		addAnimationToLastPrefab("IdleRight", &m_dM->playerTxt, sf::Vector2f(0.f, 192.f), 1, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 1), Animation::repeatMode::circle, nullptr, m_dM->playerTxt, false, false);
		createAnimation4DToLastPrefab("Idle", "IdleUp", "IdleDown", "IdleLeft", "IdleRight");


		addAnimationToLastPrefab("WalkDownStart", &m_dM->playerTxt, sf::Vector2f(0.f, 128.f), 2, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 2), Animation::repeatMode::once, nullptr, m_dM->playerTxt, false, false);
		
		addAnimationToLastPrefab("WalkUp", &m_dM->playerTxt, sf::Vector2f(128.f, 0.f), 7, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 7), Animation::repeatMode::circle, nullptr, m_dM->playerTxt, false, false);
		addAnimationToLastPrefab("WalkLeft", &m_dM->playerTxt, sf::Vector2f(128.f, 64.f), 7, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 7), Animation::repeatMode::circle, nullptr, m_dM->playerTxt, false, false);
		addAnimationToLastPrefab("WalkDown", &m_dM->playerTxt, sf::Vector2f(128.f, 128.f), 7, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 7), Animation::repeatMode::circle, nullptr, m_dM->playerTxt, false, false);
		addAnimationToLastPrefab("WalkRight", &m_dM->playerTxt, sf::Vector2f(128.f, 192.f), 7, 0.05f, sf::Vector2i(64, 64), sf::Vector2i(1, 7), Animation::repeatMode::circle, nullptr, m_dM->playerTxt, false, false);
		createAnimation4DToLastPrefab("Walk", "WalkUp", "WalkDown", "WalkLeft", "WalkRight");

		createStaticObjPrefab(&p_dM->waterAnim, waterEff01, sf::IntRect(0, 0, 32, 32), false, sf::IntRect(0, 0, 20, 20), true);
		addAnimationToLastPrefab("Idle", &m_dM->waterAnim, sf::Vector2f(0.f, 0.f), 10, 0.05f, sf::Vector2i(32, 32), sf::Vector2i(1, 10), Animation::repeatMode::circle, nullptr, m_dM->waterAnim, false, false);

		createStaticObjPrefab(&p_dM->objectsTxt, grass_01, sf::IntRect(1152, 640, 32, 32), false, sf::IntRect(0, 0, 20, 20), false);
		createStaticObjPrefab(&p_dM->objectsTxt, grass_02, sf::IntRect(1184, 640, 32, 32), false, sf::IntRect(0, 0, 20, 20), false);
		createStaticObjPrefab(&p_dM->objectsTxt, grass_03, sf::IntRect(1216, 640, 32, 32), false, sf::IntRect(0, 0, 20, 20), false);
		createStaticObjPrefab(&p_dM->objectsTxt, grass_04, sf::IntRect(1248, 640, 32, 32), false, sf::IntRect(0, 0, 20, 20), false);
		createStaticObjPrefab(&p_dM->objectsTxt, waterBamboo_01, sf::IntRect(0, 928, 32, 64), false, sf::IntRect(0, -20, 10, 20), false);
		createStaticObjPrefab(&p_dM->objectsTxt, waterBamboo_02, sf::IntRect(32, 928, 32, 64), false, sf::IntRect(0, -32, 10, 20), false);
		createStaticObjPrefab(&p_dM->objectsTxt, waterBamboo_03, sf::IntRect(64, 928, 32, 64), false, sf::IntRect(0, -20, 10, 20), false);

		createSpecialObjPrefab(&p_dM->specialObjectsTxt, changeZone, sf::IntRect(0, 0, 16, 16), false, sf::IntRect(0, -0, 32, 32), false);
	};
	~ObjectMenager() {
		//delete grass[1][1];
	}
};

