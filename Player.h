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
        setObjectCenterOrigin(sf::Vector2f(0.f, 16.f));
    }
    Player(const Player& p1) : Object(p1) {
        setObjectCenterOrigin(sf::Vector2f(0.f, 16.f));
    }
    void Update(sf::Vector2i* a_mousePos);
};

