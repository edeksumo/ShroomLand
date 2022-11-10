#pragma once
#include "UI.h"
class Text :
    public UI
{
private:
    std::string v_text;
protected:

public:
    Text(sf::Vector2f m_pos, std::string m_text, sf::Color m_textColor, DataMenager* m_dM) {
        hasText = true;
        v_text = m_text;
        relativePosition = m_pos;
        textColor = m_textColor;
        p_dM = m_dM;
        position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
        v_UIState = UI::UIState::active;
        initBackground();
        initText(m_text);
    }

    void setText(string a_text);
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};

