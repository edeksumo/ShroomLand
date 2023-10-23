#pragma once
#include "Object.h"
class Player :
    public Object
{
private:

protected:

public:
    Player() {

    }

    Player(sf::Texture* m_texture, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, DataMenager* m_dM) : Object(m_texture, m_area, m_solid, m_hitbox, m_dM) {

    }
    Player(const Object& p1) : Object(p1) {

    }
    void Update(sf::Vector2i* a_mousePos);
};

