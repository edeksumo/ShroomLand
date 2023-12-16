#pragma once
#include "Object.h"
class InteractableObject :
    public Object
{
private:

protected:

public:
    InteractableObject() {

    }

    InteractableObject(sf::Texture* m_texture, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool m_isAnimated, DataMenager* m_dM) : Object(m_texture, m_area, m_solid, m_hitbox, m_dM) {
        isAnimated = m_isAnimated;
    }
    InteractableObject(const Object& p1) : Object(p1) {

    }
    void OnCollisionEnter();
    void OnCollision();
    void OnCollisionExit();
    void Update(sf::Vector2i* a_mousePos);
};

