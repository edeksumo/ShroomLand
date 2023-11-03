#pragma once
#include "Sprite.h"
class Object :
    public Sprite
{
private:

protected:
    bool solid;

public:
    Object() {
        solid = true;
    }
    Object(sf::Texture* m_texture, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, DataMenager* m_dM) : Sprite (m_hitbox) {
        p_dM = m_dM;
        sprite.setTexture(*m_texture);
        sprite.setTextureRect(m_area);
        solid = m_solid;
        hasHitbox = true;
        hitbox.setSize(sf::Vector2f(m_hitbox.width, m_hitbox.height));
        hitbox.setFillColor(sf::Color(0, 0, 0, 0));
        hitbox.setOutlineThickness(1.f);
        hitbox.setOutlineColor(sf::Color::White);
        setObjectCenterOrigin();
    }
    Object(const Object& p1) : Sprite(p1) {
        p_dM = p1.p_dM;
        sprite = p1.sprite;
        solid = p1.solid;
        hasHitbox = p1.hasHitbox;
        hitbox = p1.hitbox;
        setObjectCenterOrigin();
    }
    bool operator <(const Object& p1) {
        return (sprite.getPosition().y < p1.sprite.getPosition().y);
    }
    bool isSolid();
    void setObjectCenterOrigin();
    void setObjectCenterOrigin(sf::Vector2f a_offset);  // moving origin around object by ofsfet 
    virtual void Update(sf::Vector2i* a_mousePos) = 0;
};

