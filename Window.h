#pragma once

#include "UI.h"
#include "Switch.h"
#include "Slider.h"
#include "Text.h"

class Window : public UI
{

private:
    unsigned int ID;
protected:

public:
    bool setToClose;
    std::multimap<std::string, Button> Buttons;
    std::multimap<std::string, Switch> Switches;
    std::multimap<std::string, Slider> Sliders;
    std::multimap<std::string, Text> Texts;

    static bool CheckButton(const std::multimap<std::string, Button>::iterator& a_it, std::string a_name);

    Window(unsigned int m_id, sf::Vector2f m_pos, sf::Vector2f m_size, sf::Color m_color, std::string m_text, sf::Color m_textColor, sf::Vector2f m_textPos, sf::Window * m_window, DataMenager* m_dM){
        hasText = true;
        hasBackground = true;
        relativePosition = m_pos;
        color = m_color;
        textColor = m_textColor;
        size = m_size;
        p_dM = m_dM;
        ID = m_id;
        textPosition = m_textPos;
        position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
        v_UIState = UI::UIState::active;
        
        backgroundSprite.setTexture(p_dM->windowsBackgroundTxt);
        backgroundSprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
        upperDecorLine.setTexture(p_dM->windowsDecorLineTxt);
        upperDecorLine.setTextureRect(sf::IntRect(0, 0, size.x - (p_dM->windowsDecorCornerTxt.getSize().x *2), p_dM->windowsDecorLineTxt.getSize().y));
        lowerDecorLine.setTexture(p_dM->windowsDecorLineTxt);
        lowerDecorLine.setTextureRect(sf::IntRect(0, 0, size.x - (p_dM->windowsDecorCornerTxt.getSize().x * 2), p_dM->windowsDecorLineTxt.getSize().y));
        lowerDecorLine.rotate(180);
        leftDecorLine.setTexture(p_dM->windowsDecorLineTxt);
        leftDecorLine.setTextureRect(sf::IntRect(0, 0, size.y - (p_dM->windowsDecorCornerTxt.getSize().x * 2), p_dM->windowsDecorLineTxt.getSize().y));
        leftDecorLine.rotate(270);
        rightDecorLine.setTexture(p_dM->windowsDecorLineTxt);
        rightDecorLine.setTextureRect(sf::IntRect(0, 0, size.y - (p_dM->windowsDecorCornerTxt.getSize().x * 2), p_dM->windowsDecorLineTxt.getSize().y));
        rightDecorLine.rotate(90);
        upperDecorLeftCorn.setTexture(p_dM->windowsDecorCornerTxt);
        lowerDecorLeftCorn.setTexture(p_dM->windowsDecorCornerTxt);
        lowerDecorLeftCorn.setRotation(270);
        upperDecorRightCorn.setTexture(p_dM->windowsDecorCornerTxt);
        upperDecorRightCorn.setRotation(90);
        lowerDecorRightCorn.setTexture(p_dM->windowsDecorCornerTxt);
        lowerDecorRightCorn.setRotation(180);
        
        initBackground();
        initText(m_text);
        setToClose = false;
    }
    ~Window() {
        setToClose = true;
    }

    unsigned int getID();
    void AddButton(std::string a_name, sf::Vector2f a_size, sf::Vector2f a_pos, sf::Color a_color, std::string a_text, sf::Color a_textColor);
    void AddSwitch(std::string a_name, sf::Vector2f a_pos, sf::Color a_color);
    void AddSlider(std::string a_name, sf::Vector2f a_pos, sf::Color a_color, float a_lenght, unsigned int a_maxValue);
    void AddText(std::string a_name, sf::Vector2f a_pos, sf::Color a_color, std::string a_text);
    void SetElementValue(std::string a_eleName, int a_val);
    void SetElementValue(std::string a_eleName, std::string a_val);
    int GetSliderValue(std::string a_eleName);
    bool IsSwitchOn(std::string a_eleName);
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};

