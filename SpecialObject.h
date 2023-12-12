#pragma once
#include "Object.h"
class SpecialObject :
    public Object
{
private:

protected:

public:
    SpecialObject() {

    }

    SpecialObject(sf::Texture* m_texture, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool m_isAnimated, DataMenager* m_dM) : Object(m_texture, m_area, m_solid, m_hitbox, m_dM) {
        isAnimated = m_isAnimated;
    }
    SpecialObject(const Object& p1) : Object(p1) {
    }
    void Update(sf::Vector2i* a_mousePos);
};

