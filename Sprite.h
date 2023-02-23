#pragma once
#include <SFML/Graphics.hpp>
#include "DataMenager.h"
#include "Grid.h"

class Sprite
{
private:
protected:
	DataMenager* p_dM;
public:
	unsigned int ID;
	sf::Sprite sprite;
	Grid posOnGrid;
	Sprite() {
		p_dM = nullptr;
		static unsigned int ID_COUNTER;
		ID = ID_COUNTER++;
		posOnGrid = Grid(0, 0);
		std::cout << "sprite constructor " << ID << endl;
	};

	Sprite(const Sprite& p1) {
		ID = p1.ID;
		p_dM = p1.p_dM;
		posOnGrid = p1.posOnGrid;
		std::cout << "sprite copy constructor " << ID << endl;
	};

	void SetPosition(Grid a_pos);	//sets position on grid and multiplias it by 32 for in game pos;
	Grid GetGridPosition();
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
	void Render(sf::RenderTarget* a_target);
};

