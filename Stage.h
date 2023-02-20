#pragma once
#include"Tile.h"
#include<deque>

class Stage
{
private:

protected:

public:
	std::deque<Tile> TileDeque;

	void addTile(sf::Vector2f a_pos, Tile* a_tileptr);

	void Update(sf::Vector2i* a_mousePos);
	void Render(sf::RenderTarget* a_target);
};

