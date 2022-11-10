#pragma once
#include "UI.h"
class Slider :
    public UI
{
private:
    int value;
    int maxValue;
    float tempOffset;
    float mouseX;
    float pxPerVal;
    bool isHold;
    sf::FloatRect screenPositionRect;
    std::vector<float> sliderPosVec;
    
    void calculateEachPos();
    bool isSliderSelected(sf::Vector2i* a_mousePos);
    void slider(sf::Vector2i* a_mousePos);
    void setOffset();

protected:
public:
    Slider(sf::Vector2f m_pos, sf::Color m_color, float m_lenght, unsigned int m_maxValue, DataMenager* m_dM) {
        mouseX = 0;
        tempOffset = 0;
        isHold = false;
        hasSlider = true;
        hasBackground = true;
        sliderShape.setSize(sf::Vector2f(20, 30));
        screenPositionRect = sf::FloatRect(sliderShape.getLocalBounds().left + m_pos.x + 5 , sliderShape.getLocalBounds().top + m_pos.y + 5, sliderShape.getLocalBounds().left + sliderShape.getSize().x + m_pos.x + 5,
            sliderShape.getLocalBounds().top + sliderShape.getSize().y + m_pos.y + 5);
        sliderShape.setFillColor(sf::Color::Black);
        relativePosition = m_pos;
        color = m_color;
        size = sf::Vector2f(m_lenght, 40);
        p_dM = m_dM;
        maxValue = m_maxValue;
        value = 0;
        position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
        v_UIState = UI::UIState::active;
        initBackground();
        pxPerVal = ((background.getLocalBounds().left + background.getSize().x - 10) - sliderShape.getSize().x) / (maxValue );
        calculateEachPos();
    };

    void setValue(int a_val);
    int getValue();
    int getMaxValue();
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};

