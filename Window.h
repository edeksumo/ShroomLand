#pragma once

#include "UI.h"
#include "Switch.h"
#include "Slider.h"
#include "Text.h"
#include "Image.h"

class Window : public UI
{
private:
    unsigned int ID;
    sf::FloatRect screenPositionRect;
    bool isBlockingMouse;
    void checkMousePos(sf::Vector2i* a_mousePos);
protected:

public:
    bool setToClose;
    std::multimap<std::string, Button> Buttons;
    std::multimap<std::string, Switch> Switches;
    std::multimap<std::string, Slider> Sliders;
    std::multimap<std::string, Text> Texts;
    std::multimap<std::string, Image> Images;

    static bool CheckButton(const std::multimap<std::string, Button>::iterator& a_it, std::string a_name);

    Window(unsigned int m_id, sf::Vector2f m_pos, sf::Vector2f m_size, std::string m_text, sf::Color m_textColor, sf::Vector2f m_textPos, sf::Window * m_window, DataMenager* m_dM){
        hasText = true;
        hasBackground = true;
        isBlockingMouse = false;
        relativePosition = m_pos;
        textColor = m_textColor;
        size = m_size;
        p_dM = m_dM;
        ID = m_id;
        textPosition = m_textPos;
        position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
        v_UIState = UI::UIState::active;
        screenPositionRect = sf::FloatRect(backgroundSprite.getLocalBounds().left + m_pos.x, backgroundSprite.getLocalBounds().top + m_pos.y, backgroundSprite.getLocalBounds().left + m_size.x + m_pos.x,
            backgroundSprite.getLocalBounds().top + m_size.y + m_pos.y);

        backgroundSprite.setTexture(p_dM->windowsBackgroundTxt);
        backgroundSprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
       
        upperDecorLine.setTexture(p_dM->windowsDecorUpLineTxt);
        upperDecorLine.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x) - (p_dM->windowsDecorDownLeftCornerTxt.getSize().x *2) + 4, p_dM->windowsDecorUpLineTxt.getSize().y));
        
        lowerDecorLine.setTexture(p_dM->windowsDecorDownLineTxt);
        lowerDecorLine.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x) - (p_dM->windowsDecorDownLeftCornerTxt.getSize().x * 2) + 4, p_dM->windowsDecorDownLineTxt.getSize().y));

        leftDecorLine.setTexture(p_dM->windowsDecorLeftLineTxt);
        leftDecorLine.setTextureRect(sf::IntRect(0, 0, p_dM->windowsDecorLeftLineTxt.getSize().x, static_cast<int>(size.y) - (p_dM->windowsDecorDownLeftCornerTxt.getSize().y * 2) + 4));

        rightDecorLine.setTexture(p_dM->windowsDecorRightLineTxt);
        rightDecorLine.setTextureRect(sf::IntRect(0, 0, p_dM->windowsDecorRightLineTxt.getSize().x, static_cast<int>(size.y) - (p_dM->windowsDecorDownLeftCornerTxt.getSize().y * 2) + 4));

        
        upperDecorLeftCorn.setTexture(p_dM->windowsDecorLeftUpCornerTxt);
        lowerDecorLeftCorn.setTexture(p_dM->windowsDecorDownLeftCornerTxt);
        //lowerDecorLeftCorn.setRotation(270);
        upperDecorRightCorn.setTexture(p_dM->windowsDecorUpRightCornerTxt);
        //upperDecorRightCorn.setRotation(90);
        lowerDecorRightCorn.setTexture(p_dM->windowsDecorDownRightCornerTxt);
        //lowerDecorRightCorn.setRotation(180);
        
        initBackground();
        initText(m_text);
        setToClose = false;
    }
    ~Window() {
        setToClose = true;
    }

    unsigned int getID();
    void AddButton(std::string a_name, sf::Vector2f a_size, sf::Vector2f a_pos, std::string a_text, sf::Color a_textColor);
    void AddSwitch(std::string a_name, sf::Vector2f a_pos);
    void AddSlider(std::string a_name, sf::Vector2f a_pos, float a_lenght, unsigned int a_maxValue);
    void AddText(std::string a_name, sf::Vector2f a_pos, sf::Color a_color, std::string a_text);
    void AddImage(std::string a_name, sf::Vector2f a_pos, sf::Texture* a_texture);
    void SetElementValue(std::string a_eleName, int a_val);
    void SetElementValue(std::string a_eleName, std::string a_val);
    void SetElementValue(std::string a_eleName, sf::Sprite* a_val);
    int GetSliderValue(std::string a_eleName);
    Button::SwitchState GetSwitchValue(std::string a_eleName);
    bool IsSwitchOn(std::string a_eleName);
    bool isWindowBlockingMouse();
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};

