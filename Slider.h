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
    bool drawSelector;
    sf::FloatRect screenPositionRect;
    std::vector<float> sliderPosVec;
    
    void calculateEachPos();
    bool isSliderSelected(sf::Vector2i* a_mousePos);
    void slider(sf::Vector2i* a_mousePos);
    void setOffset();

protected:
public:
    Slider(sf::Vector2f m_pos, float m_lenght, unsigned int m_maxValue, DataMenager* m_dM) {
        mouseX = 0;
        tempOffset = 0;
        isHold = false;
        hasSlider = true;
        hasBackground = true;
        hasSelector = true;
        
        drawSelector = false;

        sliderShapeSprite.setTexture(m_dM->sliderTxt);
        backgroundSprite.setTexture(m_dM->sliderBackgroundTxt);
        backgroundSprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_lenght), m_dM->sliderBackgroundTxt.getSize().y));
        sliderDecorLeft.setTexture(m_dM->sliderDecorTxt);
        SliderDecorRight.setTexture(m_dM->sliderDecorTxt);
        SliderDecorRight.setRotation(-180);

        screenPositionRect = sf::FloatRect(sliderShapeSprite.getLocalBounds().left + m_pos.x , sliderShapeSprite.getLocalBounds().top + m_pos.y + 5, sliderShapeSprite.getLocalBounds().left + 
            sliderShapeSprite.getLocalBounds().width + m_pos.x, sliderShapeSprite.getLocalBounds().top + sliderShapeSprite.getLocalBounds().height + m_pos.y + 5);

        relativePosition = m_pos;
        size = sf::Vector2f(m_lenght, 40);
        p_dM = m_dM;
        maxValue = m_maxValue;
        value = 0;
        position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
        v_UIState = UI::UIState::active;
        initBackground();
        pxPerVal = (m_lenght - sliderShapeSprite.getLocalBounds().width) / maxValue;
        shadow.setSize(sf::Vector2f(sliderShapeSprite.getTextureRect().width, sliderShapeSprite.getTextureRect().height));
        shadow.setFillColor(sf::Color(0, 0, 0, 60));
        calculateEachPos();
    };

    void setValue(int a_val);
    int getValue();
    int getMaxValue();
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};

