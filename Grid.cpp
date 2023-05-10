#include "Grid.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/


/****************************************************/
//Public
/****************************************************/
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

void Grid::AddObject(GridCell a_pos, StaticObject* a_obj)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;

	StaticObject* p = new StaticObject(*a_obj);
	p->SetPosition(a_pos);

	ObjGridPtr[a_pos.x][a_pos.y] = p;
}

void Grid::RemoveObject(GridCell a_pos)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	if (ObjGridPtr[a_pos.x][a_pos.y] == nullptr)
		return;
	delete ObjGridPtr[a_pos.x][a_pos.y];
	ObjGridPtr[a_pos.x][a_pos.y] = nullptr;
}

bool Grid::isTileObjOccupied(GridCell a_pos)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return false;
	if (ObjGridPtr[a_pos.x][a_pos.y] == nullptr)
		return false;
	return true;
}