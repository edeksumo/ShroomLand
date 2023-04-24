#pragma once
#include"Tile.h"
#include<deque>
#include<map>
class Grid
{
private:
	unsigned int size_x;
	unsigned int size_y;
protected:

public:
	std::vector<std::vector<Tile*>> TileGridPtr;
	//std::deque<Tile> TileDeque;
	Grid() {
		size_x = 100;
		size_y = 100;
		TileGridPtr.resize(size_x);
		for (auto& i : TileGridPtr) {
			i.resize(size_y);
			std::fill(i.begin(), i.end(), nullptr);
			//std::cout << "a";
		}
	}
	Grid(unsigned int m_sizex, unsigned int m_sizey) {
		size_x = m_sizex;
		size_y = m_sizey;
		TileGridPtr.resize(size_x);
		for (auto& i : TileGridPtr) {
			i.resize(size_y);
			std::fill(i.begin(), i.end(), nullptr);
			//std::cout << "a";
		}
	}
	void AddTile(GridCell a_pos, Tile* a_tile, unsigned int a_variant = 0);
	void RemoveTile(GridCell a_pos);
	Tile* GetTilePtr(GridCell a_pos);
	GridCell GetSize();
	bool isTileOccupied(GridCell a_pos);
};

