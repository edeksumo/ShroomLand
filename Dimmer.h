#pragma once
#include "UI.h"
const int MIN_TRANSPARENCY = 0;
const int MAX_TRANSPARENCY = 255;
const int MAX_TIMER = 2;
class Dimmer :
    public UI
{
public:
    enum class EMode {
        none,
        dim,
        brighten
    };
private:
    EMode Mode;
    int currentTransparency;
protected:

public:
    Dimmer(sf::Window* m_Window, DataMenager* m_dM) {
        relativePosition = sf::Vector2f(0.f, 0.f);
        p_dM = m_dM;
        p_Window = m_Window;
        position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
        v_UIState = UI::UIState::active;
        initBackground();
        Mode = EMode::none;
        shadow.setSize(sf::Vector2f(p_Window->getSize().x, p_Window->getSize().y));
        currentTransparency = 0;
        setTransparency(currentTransparency);
    }
    void FadeIn(unsigned int a_speed);
    void FadeOut(unsigned int a_speed);
    void setTransparency(unsigned int a_transparency);
    void setMode(Dimmer::EMode a_mode);
    Dimmer::EMode getMode();
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};

