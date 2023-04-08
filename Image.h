#pragma once
#include "UI.h"
class Image :
    public UI
{
private:

protected:

public:
    Image(sf::Vector2f m_pos, sf::Texture* m_texture, DataMenager* m_dM) {
        relativePosition = m_pos;
        p_dM = m_dM;
        hasImage = true;
        imageSprite.setTexture(*m_texture);
        position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
        v_UIState = UI::UIState::active;
        initBackground();
    }
    void setTexture(sf::Texture* a_texture);
    void setSprite(sf::Sprite* a_sprite);
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};
