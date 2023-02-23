#pragma once
#include"Tile.h"
#include<deque>
#include "ObjectMenager.h"
class Stage
{
private:
	ObjectMenager* p_objMenager;
protected:

public:
	std::deque<Tile> TileDeque;

	//Tile TileArray[3800][3800];
	//std::map<std::pair<int, int>, Tile> TileGridMap; //for keeping only one tile at posistion amybe check vector2i

	Stage() {
		p_objMenager = nullptr;
	}

	Stage(ObjectMenager* m_objMenager) {
		p_objMenager = m_objMenager;
	}

	void addTile(Grid a_pos, unsigned int a_ID);		
	void removeTile(Grid a_pos);

	void Update(sf::Vector2i* a_mousePos);
	void Render(sf::RenderTarget* a_target);
};

