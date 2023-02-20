#pragma once
#include "Sprite.h"
class Tile :
    public Sprite
{
private:

protected:

public:
    Tile() {

    };

    Tile(sf::Texture* m_texture, sf::IntRect m_area, DataMenager* m_dM) {
        p_dM = m_dM;
        sprite.setTexture(*m_texture);
        sprite.setTextureRect(m_area);
        std::cout << "constructor" << std::endl;
    };

    Tile(const Tile& p1) : Sprite(p1) {         //it make sure that the copy constructor of parent class is run
        p_dM = p1.p_dM;
        sprite.setTexture(*p1.sprite.getTexture());
        sprite.setTextureRect(p1.sprite.getTextureRect());
        std::cout << "copy constructor" << std::endl;
    };
    void Update(sf::Vector2i* a_mousePos);
};
