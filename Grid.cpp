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

void Grid::AddObjectToRender(sf::Vector2f a_pos, Object* a_obj)
{
	int a = 0;
	for (auto i : RenderObjPtrVec) {
		if (a_pos.y > i->sprite.getPosition().y)
			a++;
	}
	RenderObjPtrVec.insert(RenderObjPtrVec.begin() + a, a_obj);
	/////////////////////////////////////////////
	//////	IT WILL Be usefull while moving 
	////////////////////////////////////////////
	//RenderObjPtrVec.push_back(StaticObjStorageVec.back());
	//std::sort(RenderObjPtrVec.begin(), RenderObjPtrVec.end(), sortingFunc);
}

void Grid::AddSpecialObjectToRender(sf::Vector2f a_pos, Object* a_obj)
{
	int a = 0;
	for (auto i : RenderEditorObjPtrVec) {
		if (a_pos.y > i->sprite.getPosition().y)
			a++;
	}
	RenderEditorObjPtrVec.insert(RenderEditorObjPtrVec.begin(), a_obj);
}

void Grid::AddSolidObjToVec(Object* a_obj)
{
	if (!a_obj->isSolid())
		return;
	SolidObjects.push_back(a_obj);
}

void Grid::AddObject(sf::Vector2f a_pos, StaticObject* a_obj)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;

	auto* p = new StaticObject(*a_obj);
	p->SetPosition(a_pos);
	StaticObjStorageVec.push_back(p);
	AddSolidObjToVec(StaticObjStorageVec.back());
	AddObjectToRender(a_pos, StaticObjStorageVec.back());
}

void Grid::AddObject(sf::Vector2f a_pos, InteractableObject* a_obj)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;

	auto p = new InteractableObject(*a_obj);
	p->SetPosition(a_pos);
	InteractableObjStorageVec.push_back(p);
	AddSolidObjToVec(InteractableObjStorageVec.back());
	AddObjectToRender(a_pos, InteractableObjStorageVec.back());
}

void Grid::AddObject(sf::Vector2f a_pos, SpecialObject* a_obj)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;

	auto p = new SpecialObject(*a_obj);
	p->SetPosition(a_pos);
	SpecialObjStorageVec.push_back(p);
	AddSolidObjToVec(SpecialObjStorageVec.back());
	//AddObjectToRender(a_pos, SpecialObjStorageVec.back());
	AddSpecialObjectToRender(a_pos, SpecialObjStorageVec.back());
}

void Grid::AddObject(sf::Vector2f a_pos, Player* a_obj)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;

	auto p = new Player(*a_obj);
	p->SetPosition(a_pos);
	PlayerObjStorageVec.push_back(p);
	//AddSolidObjToVec(PlayerObjStorageVec.back());
	AddObjectToRender(a_pos, PlayerObjStorageVec.back());
}

void Grid::MoveOnPos(sf::Vector2f a_pos, Object* a_obj)
{
	a_obj->SetPosition(a_pos);
	std::sort(RenderObjPtrVec.begin(), RenderObjPtrVec.end(), sortingFunc);
}

void Grid::MoveObject(sf::Vector2f a_pos, Object* a_obj)
{
	a_obj->MoveSprite(a_pos);
	std::sort(RenderObjPtrVec.begin(), RenderObjPtrVec.end(), sortingFunc);
}
/// //////////////////////////////////////
/// each object class must be added here
/// /////////////////////////////////////
void Grid::RemoveObject(Object* a_obj)
{
	int a = 0, b = 0, c = 0, d = 0, r = 0, s = 0;
	bool _static = false, _interactable = false, _player = false, _special = false;
	for (int i = 0; i < StaticObjStorageVec.size(); i++) {
		if (StaticObjStorageVec[i] == a_obj) {
			_static = true;
			break;
		}
		a++;
	}
	for (int i = 0; i < InteractableObjStorageVec.size(); i++) {

		if (InteractableObjStorageVec[i] == a_obj) {
			_interactable = true;
			break;
		}
		b++;
	}
	for (int i = 0; i < PlayerObjStorageVec.size(); i++) {

		if (PlayerObjStorageVec[i] == a_obj) {
			_player = true;
			break;
		}
		c++;
	}
	for (int i = 0; i < SpecialObjStorageVec.size(); i++) {

		if (SpecialObjStorageVec[i] == a_obj) {
			_special = true;
			break;
		}
		d++;
	}
	/// 
	/// removing adress from rendering vector 
	/// 
	for (int i = 0; i < RenderObjPtrVec.size(); i++) {
		if (RenderObjPtrVec[i] == a_obj) {
			break;
		}
		r++;
	}
	if (_static)
		StaticObjStorageVec.erase(StaticObjStorageVec.begin() + a);
	if (_interactable)
		InteractableObjStorageVec.erase(InteractableObjStorageVec.begin() + b);
	if (_player)
		PlayerObjStorageVec.erase(PlayerObjStorageVec.begin() + c);
	if (!_special) {
		RenderObjPtrVec.erase(RenderObjPtrVec.begin() + r);
		return;
	}
	for (int i = 0; i < RenderEditorObjPtrVec.size(); i++) {
		if (RenderEditorObjPtrVec[i] == a_obj) {
			break;
		}
		s++;
	}
	if (_special) {
		SpecialObjStorageVec.erase(SpecialObjStorageVec.begin() + d);
		RenderEditorObjPtrVec.erase(RenderEditorObjPtrVec.begin() + s);
	}
}

bool Grid::isTileObjOccupied(GridCell a_pos)
{
	//if (a_pos.x < 0 || a_pos.y < 0)
	//	return false;
	//if (ObjGridPtr[a_pos.x][a_pos.y] == nullptr)
	//	return false;
	return true;
}