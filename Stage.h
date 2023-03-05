#pragma once
#include"Tile.h"
#include<deque>
#include<map>
#include "ObjectMenager.h"
class Stage
{
private:
	ObjectMenager* p_objMenager;
protected:

public:
	std::deque<Tile> TileDeque;
	std::deque<Tile> BackGroundTiles;
	//std::vector<std::vector<Tile>> TileVector;
	//std::map<int, std::map<int, Tile>> TileMap; //for keeping only one tile at posistion amybe check vector2i

	Stage() {
		p_objMenager = nullptr;
	}

	Stage(ObjectMenager* m_objMenager) {
		p_objMenager = m_objMenager;
	}

	void addTile(Grid a_pos, unsigned int a_ID);	
	void addBackgroundTile(Grid a_pos, unsigned int a_ID, int a_shifted = 0);
	Tile getTileByGrid(Grid a_pos);
	void removeTile(Grid a_pos);

	void Update(sf::Vector2i* a_mousePos);
	void Render(sf::RenderTarget* a_target);
};

