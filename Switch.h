#pragma once
#include "Button.h"
class Switch :
    public Button
{
private:
    void setTexture();
protected:

public:
    Switch(sf::Vector2f m_pos, sf::Color m_color, DataMenager* m_dM) {
        hasSelector = true;
        hasBackground = true;
        isSwitch = true;
        relativePosition = m_pos;
        color = m_color;
        size = sf::Vector2f(20, 20);
        screenPositionRect = sf::FloatRect(background.getLocalBounds().left + m_pos.x, background.getLocalBounds().top + m_pos.y, background.getLocalBounds().left + size.x + m_pos.x,
            background.getLocalBounds().top + size.y + m_pos.y);
        //background.setOutlineThickness(1.f);
        //background.setOutlineColor(sf::Color::Black);
        p_dM = m_dM;
        state = SwitchState::off;
        backgroundSprite.setTexture(p_dM->switchBackgroundTxt);
        position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
        v_UIState = UI::UIState::active;
        initBackground();
    };

    void setState(Button::ButtonState a_state);
    Button::ButtonState getState();
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};

