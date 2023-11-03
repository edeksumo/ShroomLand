#pragma once
#include"Tile.h"
#include"StaticObject.h"
#include"InteractableObject.h"
#include"Player.h"
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

	std::vector<Object*> RenderObjPtrVec;							//stores all pointers to object for rendering in good order
	/// Need to be added for all types of Objects with corresponding add<objType> func;
	std::vector<StaticObject*> StaticObjStorageVec;					//stores all static objects
	std::vector<InteractableObject*> InteractableObjStorageVec;		//stores all interactable objects;
	std::vector<Player*> PlayerObjStorageVec;		//stores all player objects;

	Grid() {
		size_x = 100;
		size_y = 100;
		TileGridPtr.resize(size_x);
		/// <summary>
		/// prepering empty stage
		/// </summary>
		for (auto& i : TileGridPtr) {
			i.resize(size_y);
			std::fill(i.begin(), i.end(), nullptr);
		}
	}
	Grid(unsigned int m_sizex, unsigned int m_sizey) {
		size_x = m_sizex;
		size_y = m_sizey;
		TileGridPtr.resize(size_x);
		/// <summary>
		/// prepering empty stage
		/// </summary>
		for (auto& i : TileGridPtr) {
			i.resize(size_y);
			std::fill(i.begin(), i.end(), nullptr);
		}
	}
	void AddTile(GridCell a_pos, Tile* a_tile, unsigned int a_variant = 0);
	void RemoveTile(GridCell a_pos);
	Tile* GetTilePtr(GridCell a_pos);
	GridCell GetSize();
	bool isTileOccupied(GridCell a_pos);

	void AddObjectToRender(sf::Vector2f a_pos, Object* a_obj);

	void AddObject(sf::Vector2f a_pos, StaticObject* a_obj);
	void AddObject(sf::Vector2f a_pos, InteractableObject* a_obj);
	void AddObject(sf::Vector2f a_pos, Player* a_obj);
	void MoveOnPos(sf::Vector2f a_pos, Object* a_obj);	//used for already placed objects for seting position (updates render order)
	void MoveObject(sf::Vector2f a_pos, Object* a_obj);  //used for moving object pixel by pixel (updates render order)
	void RemoveObject(Object* a_obj);
	bool isTileObjOccupied(GridCell a_pos);
};

