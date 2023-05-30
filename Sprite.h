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
	sf::Vector2f hitboxPos;
protected:
	sf::RectangleShape hitbox;
	DataMenager* p_dM;
	bool hasHitbox;
public:
	
	unsigned int ID;
	sf::Sprite sprite;
	GridCell posOnGrid;
	static unsigned int ID_COUNTER;
	static unsigned int LAST_ID;
		
	Sprite() {
		p_dM = nullptr;
		//static unsigned int ID_COUNTER;
		ID = ID_COUNTER++;
		LAST_ID = ID;
		posOnGrid = GridCell(0, 0);
		hasHitbox = false;
		//std::cout << "sprite constructor " << ID << endl;
	};

	Sprite(sf::IntRect m_hitboxPos) {
		p_dM = nullptr;
		//static unsigned int ID_COUNTER;
		ID = ID_COUNTER++;
		LAST_ID = ID;
		posOnGrid = GridCell(0, 0);
		hasHitbox = true;
		hitboxPos = sf::Vector2f(m_hitboxPos.left, m_hitboxPos.top);
		//std::cout << "sprite constructor " << ID << endl;
	};

	Sprite(const Sprite& p1) {
		ID = p1.ID;
		p_dM = p1.p_dM;
		posOnGrid = p1.posOnGrid;
		hasHitbox = p1.hasHitbox;
		hitboxPos = p1.hitboxPos;
		//std::cout << "sprite copy constructor " << ID << endl;
	};

	void SetPosition(GridCell a_pos);	//sets position on grid and multiplias it by 32 for in game pos
	void SetPosition(sf::Vector2f a_pos);	//sets position in pixels
	void flipSprite();
	GridCell GetGridPosition();
	sf::FloatRect getHitboxWorldRect();
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
	void Render(sf::RenderTarget* a_target);
};

