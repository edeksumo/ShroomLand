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

	std::multimap<int, Tile*> TilePtrContainer;					//stores all Tiles pointer in the game 
	ObjectMenager() {

	}

	ObjectMenager(DataMenager* m_dM) {
		p_dM = m_dM;
		tilesetPrefabCreater(&p_dM->grassTileSet, grass);
	};
	~ObjectMenager() {
		//delete grass;
	}
};

