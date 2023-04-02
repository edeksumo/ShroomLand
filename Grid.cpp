#include "Grid.h"

void Grid::AddTile(GridCell a_pos, Tile* a_tile)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	TileDeque.push_back(*a_tile);
	TileDeque.back().SetPosition(a_pos);
	Tile* p = &TileDeque.back();
	TileGridPtr[a_pos.x][a_pos.y] = &TileDeque.back();
}

void Grid::RemoveTile(GridCell a_pos)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	int i = 0;
	bool b = false;
	for (auto& it : TileDeque) {
		if (it.GetGridPosition() == a_pos) {
			b = true;
			break;
		}
		i++;
	}
	if (b) {
		TileGridPtr[a_pos.x][a_pos.y] = nullptr;
		TileDeque.erase(TileDeque.begin() + i);
	}
}

void Grid::RemoveTile(GridCell a_pos, unsigned int a_it)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	TileGridPtr[a_pos.x][a_pos.y] = nullptr;
	TileDeque.erase(TileDeque.begin() + a_it);
}

Tile* Grid::GetTilePtr(GridCell a_pos)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return nullptr;
	return TileGridPtr[a_pos.x][a_pos.y];
}

bool Grid::isTileOccupied(GridCell a_pos)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return false;
	if (TileGridPtr[a_pos.x][a_pos.y] == nullptr)
		return false;
	return true;
}
