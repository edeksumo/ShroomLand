#pragma once
#include "Object.h"
class StaticObject :
    public Object
{
private:

protected:

public:
    StaticObject() {

    }

    StaticObject(sf::Texture* m_texture, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool m_isAnimated, DataMenager* m_dM) : Object(m_texture, m_area, m_solid, m_hitbox, m_dM) {
        isAnimated = m_isAnimated;
    }
    StaticObject(const StaticObject& p1) : Object(p1) {
        if(isAnimated)
           AnimMenager->PlayAnimation("Idle");
    
    }
    void OnCollisionEnter();
    void OnCollision();
    void OnCollisionExit();
    void Update(sf::Vector2i* a_mousePos);
};

