#include "Grid.h"

void Grid::AddTile(GridCell a_pos, Tile* a_tile, unsigned int a_variant)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;

	Tile* p = new Tile(*a_tile);
	p->SetPosition(a_pos);
	
	if(a_variant != 0)
		p->setVariant(a_variant);
	
	TileGridPtr[a_pos.x][a_pos.y] = p;
}

void Grid::RemoveTile(GridCell a_pos)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	if (TileGridPtr[a_pos.x][a_pos.y] == nullptr)
		return;
	delete TileGridPtr[a_pos.x][a_pos.y];
	TileGridPtr[a_pos.x][a_pos.y] = nullptr;
	
}

Tile* Grid::GetTilePtr(GridCell a_pos)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return nullptr;
	return TileGridPtr[a_pos.x][a_pos.y];
}

GridCell Grid::GetSize()
{
	return GridCell(size_x, size_y);
}

bool Grid::isTileOccupied(GridCell a_pos)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return false;
	if (TileGridPtr[a_pos.x][a_pos.y] == nullptr)
		return false;
	return true;
}
