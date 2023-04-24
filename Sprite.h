#pragma once
#include <SFML/Graphics.hpp>
#include "DataMenager.h"
#include "GridCell.h"

const int MAX_IDIES_FOR_TILES = 55; //taken from ObjectMenager.h size of arr
const int TILE_SIZE = 32;			//in pixels
const bool DEFAULT_MASK_FOR_BACKGROUND[MAX_IDIES_FOR_TILES] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
																1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
																1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
																1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
																1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 };		//premade bitmask for all tilesets

class Sprite
{
private:
protected:
	DataMenager* p_dM;
public:
	unsigned int ID;
	sf::Sprite sprite;
	GridCell posOnGrid;
	int animFrame;
	void animation();
	
		
	Sprite() {
		p_dM = nullptr;
		static unsigned int ID_COUNTER;
		ID = ID_COUNTER++;
		posOnGrid = GridCell(0, 0);
		animFrame = 0;
		//std::cout << "sprite constructor " << ID << endl;
	};

	Sprite(const Sprite& p1) {
		ID = p1.ID;
		p_dM = p1.p_dM;
		animFrame = p1.animFrame;
		posOnGrid = p1.posOnGrid;
		//std::cout << "sprite copy constructor " << ID << endl;
	};

	void SetPosition(GridCell a_pos);	//sets position on grid and multiplias it by 32 for in game pos
	void flipSprite();
	GridCell GetGridPosition();
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
	void Render(sf::RenderTarget* a_target);
};

