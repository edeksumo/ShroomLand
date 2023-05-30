#include "Grid.h"
bool sortingFunc(Object* a_o1, Object* a_o2)
{
	//std::cout << "sorting";
	return (*a_o1 < *a_o2);
}
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

void Grid::AddObject(sf::Vector2f a_pos, StaticObject* a_obj)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;

	StaticObject* p = new StaticObject(*a_obj);
	p->SetPosition(a_pos);
	StaticObjStorageVec.push_back(p);
	int a = 0;
	for (auto i : RenderObjPtrVec) {
		if (a_pos.y > i->sprite.getPosition().y)
			a++;
	}
	RenderObjPtrVec.insert(RenderObjPtrVec.begin() + a, StaticObjStorageVec.back());
	/////////////////////////////////////////////
	//////	IT WILL Be usefull while moving 
	////////////////////////////////////////////
	//RenderObjPtrVec.push_back(StaticObjStorageVec.back());
	//std::sort(RenderObjPtrVec.begin(), RenderObjPtrVec.end(), sortingFunc);
}

void Grid::MoveOnPos(sf::Vector2f a_pos, Object* a_obj)
{
	a_obj->SetPosition(a_pos);
	std::sort(RenderObjPtrVec.begin(), RenderObjPtrVec.end(), sortingFunc);
}

void Grid::RemoveObject(Object* a_obj)
{
	int a = 0;
	for (int i = 0; i < StaticObjStorageVec.size(); i++) {
		if (StaticObjStorageVec[i] == a_obj) {
			break;
		}
		a++;
	}

	/// 
	/// removing adress from rendering vector 
	/// 

	int b = 0;
	for (int i = 0; i < RenderObjPtrVec.size(); i++) {
		if (RenderObjPtrVec[i] == a_obj) {
			break;
		}
		b++;
	}
	StaticObjStorageVec.erase(StaticObjStorageVec.begin() + a);
	RenderObjPtrVec.erase(RenderObjPtrVec.begin() + b);
}

bool Grid::isTileObjOccupied(GridCell a_pos)
{
	//if (a_pos.x < 0 || a_pos.y < 0)
	//	return false;
	//if (ObjGridPtr[a_pos.x][a_pos.y] == nullptr)
	//	return false;
	return true;
}