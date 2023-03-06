#pragma once
#include <SFML/Graphics.hpp>
#include "DataMenager.h"
#include "Grid.h"

const int MAX_IDIES_FOR_TILES = 48; //taken from ObjectMenager.h size of arr

class Sprite
{
public:
	enum class shifted {
		none = -1,
		lUp = 0,
		up,
		rUp,
		Right,
		rDown,
		down,
		lDown,
		left
	};
private:
protected:
	DataMenager* p_dM;
public:
	unsigned int ID;
	sf::Sprite sprite;
	Grid posOnGrid;
	shifted shift;
	int animFrame;
	void animation();
	
		
	Sprite() {
		p_dM = nullptr;
		static unsigned int ID_COUNTER;
		ID = ID_COUNTER++;
		posOnGrid = Grid(0, 0);
		animFrame = 0;
		shift == shifted::none;
		std::cout << "sprite constructor " << ID << endl;
	};

	Sprite(const Sprite& p1) {
		ID = p1.ID;
		p_dM = p1.p_dM;
		animFrame = p1.animFrame;
		posOnGrid = p1.posOnGrid;
		shift = p1.shift;
		std::cout << "sprite copy constructor " << ID << endl;
	};

	void SetPosition(Grid a_pos, int a_shifted = -1);	//sets position on grid and multiplias it by 32 for in game pos; shifted -2, -1, 0, 1, 2 up left none right down
	void setShift(Sprite::shifted a_shift);
	Sprite::shifted getShift();
	Grid GetGridPosition();
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
	void Render(sf::RenderTarget* a_target);
};

