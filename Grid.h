#pragma once
#include"Tile.h"
#include<deque>
#include<map>
class Grid
{
private:

protected:

public:
	std::vector<std::vector<Tile*>> TileGridPtr;
	std::deque<Tile> TileDeque;
	Grid() {
		TileGridPtr.resize(100);
		for (auto& i : TileGridPtr) {
			i.resize(100);
			std::fill(i.begin(), i.end(), nullptr);
			//std::cout << "a";
		}
	}
	void AddTile(GridCell a_pos, Tile* a_tile);
	void RemoveTile(GridCell a_pos);
	void RemoveTile(GridCell a_pos, unsigned int a_it);
	Tile* GetTilePtr(GridCell a_pos);
	bool isTileOccupied(GridCell a_pos);
};

