#pragma once
#include"Tile.h"

class ObjectMenager
{
private:
	DataMenager* p_dM;
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[8][6]);
protected:

public:
	Tile* grass[8][6];		//full tileset for grass in one array
	Tile* dirt[8][6];
	Tile* sand[8][6];
	Tile* gravel[8][6];
	Tile* forrest[8][6];
	Tile* water[8][6];

	std::multimap<int, Tile*> TilePtrContainer;					//stores all Tiles pointer in the game 
	ObjectMenager() {

	}

	ObjectMenager(DataMenager* m_dM) {
		p_dM = m_dM;
		tilesetPrefabCreater(&p_dM->grassTileSet, grass);
		tilesetPrefabCreater(&p_dM->dirtTileSet, dirt);
		tilesetPrefabCreater(&p_dM->sandTileSet, sand);
		tilesetPrefabCreater(&p_dM->gravelTileSet, gravel);
		tilesetPrefabCreater(&p_dM->forrestTileSet, water);
		tilesetPrefabCreater(&p_dM->waterTileSet, water);
	};
	~ObjectMenager() {
		//delete grass;
	}
};

