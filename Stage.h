#pragma once
#include"Grid.h"
#include "ObjectMenager.h"
class Stage
{
private:
	ObjectMenager* p_objMenager;
	sf::RenderTarget* p_renderTarget;
	DataMenager* p_dM;
protected:

public:
	std::deque<Tile> BackGroundTiles;
	std::deque<Tile> DecorTiles;

	Grid TileGrid;

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
	void addTile(GridCell a_pos, unsigned int a_ID);	
	void addObject(sf::Vector2f a_pos, unsigned int a_ID);
	void fillDeque(GridCell a_pos, unsigned int a_ID, unsigned int a_vatiant);
	void addBackgroundTile(GridCell a_pos, unsigned int a_ID);
	Tile* getPrefTilePtr(int a_ID);

	void Update(sf::Vector2i* a_mousePos);
	void Render(sf::RenderTarget* a_target);
};

