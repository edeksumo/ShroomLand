#pragma once
#include "Object.h"
class Stage;
class SpecialObject :
    public Object
{
private:

protected:

public:
    enum class SpecialType {
        none = -1,
        zoneChanger,
        sound,
        trigger
    };

    SpecialType subType;
    Stage* ZoneChangerStagePtr;
    
    SpecialObject() {
        subType = SpecialType::none;
        ZoneChangerStagePtr = nullptr;
    }

    SpecialObject(sf::Texture* m_texture, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool m_isAnimated, SpecialType m_subType, DataMenager* m_dM) : Object(m_texture, m_area, m_solid, m_hitbox, m_dM) {
        isAnimated = m_isAnimated;
        subType = m_subType;
        ZoneChangerStagePtr = nullptr;
    }
    SpecialObject(const SpecialObject& p1) : Object(p1) {
        isAnimated = p1.isAnimated;
        subType = p1.subType;
        ZoneChangerStagePtr = p1.ZoneChangerStagePtr;
    }

    void setProperties(string a_properties);
    void OnCollisionEnter();
    void OnCollision();
    void OnCollisionExit();
    void Update(sf::Vector2i* a_mousePos);
};

