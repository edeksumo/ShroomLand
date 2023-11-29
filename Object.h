#pragma once
#include "Sprite.h"
class Object :
    public Sprite
{
public:
    enum class ObjectState {
        idle,
        moving
    };
private:
    Animation::Direction facing;
    sf::Vector2f lastPos;
    Object::ObjectState state;

protected:
    bool solid;

public:
    Object() {
        solid = true;
        facing = Animation::Direction::up;
        state = Object::ObjectState::idle;
    }
    Object(sf::Texture* m_texture, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, DataMenager* m_dM) : Sprite (m_hitbox, m_dM) {
        //p_dM = m_dM;
        sprite.setTexture(*m_texture);
        sprite.setTextureRect(m_area);
        solid = m_solid;
        hasHitbox = true;
        facing = Animation::Direction::up;
        hitbox.setSize(sf::Vector2f(m_hitbox.width, m_hitbox.height));
        hitbox.setFillColor(sf::Color(0, 0, 0, 0));
        hitbox.setOutlineThickness(1.f);
        hitbox.setOutlineColor(sf::Color::White);
        state = Object::ObjectState::idle;
        lastPos = GetPosition();
        setObjectCenterOrigin();
    }
    Object(const Object& p1) : Sprite(p1) {
       // p_dM = p1.p_dM;
        facing = p1.facing;
        sprite = p1.sprite;
        solid = p1.solid;
        hasHitbox = p1.hasHitbox;
        hitbox = p1.hitbox;
        lastPos = p1.lastPos;
        state = p1.state;
        setObjectCenterOrigin();
    }
    bool operator <(const Object& p1) {
        return (sprite.getPosition().y < p1.sprite.getPosition().y);
    }
    bool isSolid();
    void SetFacing(Animation::Direction a_facing);
    Animation::Direction GetFacing();
    void setObjectCenterOrigin();
    void setObjectCenterOrigin(sf::Vector2f a_offset);  // moving origin around object by offset 
    void setState(Object::ObjectState a_state);
    Object::ObjectState getState();
    void detectFacing();
    void stateDetector();
    void animationControler();
    void resetLastPosition();       //used for detecting state and facing
    virtual void Update(sf::Vector2i* a_mousePos) = 0;
};

