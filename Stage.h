#pragma once
#include"Tile.h"
#include<deque>
#include<map>
#include "ObjectMenager.h"
class Stage
{
private:
	ObjectMenager* p_objMenager;
	sf::RenderTarget* p_renderTarget;
	DataMenager* p_dM;
	unsigned int setDecor(unsigned int a_type);
protected:

public:
	std::deque<Tile> TileDeque;
	std::deque<Tile> BackGroundTiles;
	std::deque<Tile> DecorTiles;
	//std::vector<std::vector<Tile>> TileVector;
	//std::map<int, std::map<int, Tile>> TileMap; //for keeping only one tile at posistion amybe check vector2i

	Stage() {
		p_objMenager = nullptr;
		p_renderTarget = nullptr;
		p_dM = nullptr;
	}

	Stage(ObjectMenager* m_objMenager, DataMenager* m_dM) {
		p_objMenager = m_objMenager;
		p_dM = m_dM;
		p_renderTarget = nullptr;
	}

	bool isVisible(const Sprite& a_sprite, sf::RenderTarget* a_target);
	void addTile(Grid a_pos, unsigned int a_ID);	
	void fillDeque(Grid a_pos, unsigned int a_ID);
	void addBackgroundTile(Grid a_pos, unsigned int a_ID, int a_shifted = 0);
	void addDecoration(Grid a_pos, unsigned int a_ID);
	Tile getTileByGrid(Grid a_pos);
	void removeTile(Grid a_pos);

	void Update(sf::Vector2i* a_mousePos);
	void Render(sf::RenderTarget* a_target);
};

