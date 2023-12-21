#pragma once
#include "Object.h"
class SpecialObject :
    public Object
{
private:
    string properties;
protected:

public:
    bool changeState;
    enum class SpecialType {
        none = -1,
        zoneChanger,
        sound,
        trigger
    };

    SpecialType subType;
    
    SpecialObject() {
        changeState = false;
        properties = "";
        subType = SpecialType::none;
    }

    SpecialObject(sf::Texture* m_texture, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool m_isAnimated, SpecialType m_subType, DataMenager* m_dM) : Object(m_texture, m_area, m_solid, m_hitbox, m_dM) {
        changeState = false;
        properties = "";
        isAnimated = m_isAnimated;
        subType = m_subType;
    }
    SpecialObject(const SpecialObject& p1) : Object(p1) {
        changeState = false;
        properties = p1.properties;
        isAnimated = p1.isAnimated;
        subType = p1.subType;
    }

    void setProperties(string a_properties);
    string getProperties();
    void OnCollisionEnter();
    void OnCollision();
    void OnCollisionExit();
    void Update(sf::Vector2i* a_mousePos);
};

