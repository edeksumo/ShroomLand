#pragma once
#include <SFML/Graphics.hpp>
#include "DataMenager.h"

class Sprite
{
private:

protected:
	DataMenager* p_dM;
public:
	unsigned int ID;
	sf::Sprite sprite;
	Sprite() {
		p_dM = nullptr;
		static unsigned int ID_COUNTER;
		ID = ID_COUNTER++;
		std::cout << "sprite constructor " << ID << endl;
	};

	Sprite(const Sprite& p1) {
		ID = p1.ID;
		p_dM = p1.p_dM;
		std::cout << "sprite copy constructor " << ID << endl;
	};

	virtual void Update(sf::Vector2i* a_mousePos) = 0;
	void Render(sf::RenderTarget* a_target);
};

