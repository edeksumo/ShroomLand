#pragma once
#include"Tile.h"
#include <map>

class ObjectMenager
{
private:
	DataMenager* p_dM;
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5]);		//default isTilable = true, needBackgroundTile = true
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5], bool a_isTilable, bool a_needBackgroundTile, unsigned int a_nbOfVariants);		//customazible isTilable and needBackground, zero is first variant
protected:

public:
	Tile* grass[11][5];		//full tileset for grass in one array
	Tile* mood01[11][5];
	Tile* mood02[11][5];
	Tile* water01[11][5];

	std::multimap<int, Tile*> TilePtrContainer;					//stores all Tiles pointer in the game 

	Tile* getTilePtrById(int a_ID);

	ObjectMenager() {

	}

	ObjectMenager(DataMenager* m_dM) {
		p_dM = m_dM;
		tilesetPrefabCreater(&p_dM->grassTileSet, grass);
		tilesetPrefabCreater(&p_dM->moodTileSet, mood01);
		tilesetPrefabCreater(&p_dM->mood02TileSet, mood02);
		tilesetPrefabCreater(&p_dM->water01TileSet, water01, true, true, 4);
	};
	~ObjectMenager() {
		//delete grass[1][1];
	}
};

