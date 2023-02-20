#pragma once
#include "Stage.h"
class ObjectMenager
{
private:
	DataMenager* p_dM;
	std::multimap<int, Tile*>* p_TilePtrCointainer;
	void tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[8][6]);
protected:

public:
	Tile* grass[8][6];		//full tileset for grass in one array
	ObjectMenager() {

	}

	ObjectMenager(DataMenager* m_dM, std::multimap<int, Tile*>* m_TilePtrCointainer) {
		p_dM = m_dM;
		p_TilePtrCointainer = m_TilePtrCointainer;
		tilesetPrefabCreater(&p_dM->grassTileSet, grass);
		//grass[0] = new Tile(&p_dM->grassTileSet, sf::IntRect(160, 0, 32, 32), p_dM);
		//grass[1] = new Tile(&p_dM->grassTileSet, sf::IntRect(160, 0, 32, 32), p_dM);
		//Tile t1 = *grass[0];
		//Tile t2 = *grass[1];
	};
	~ObjectMenager() {
		//delete grass;
	}
};

