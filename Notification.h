#pragma once
#include "Window.h"
const sf::Vector2f notificationBoxSize = sf::Vector2f(150, 60);
class Notification :
    public Window
{
private:
    void timer();
    void killNotification();
    void enterScreen();

    unsigned int lastingTicks;
protected:

public:
    Notification(string m_text, sf::Color m_textColor, sf::Window* m_window, DataMenager* m_dM) : Window(-1, sf::Vector2f(m_window->getSize().x, m_window->getSize().y -notificationBoxSize.y), 
    notificationBoxSize, m_text, m_textColor, sf::Vector2f(notificationBoxSize.x / 2 + 13, notificationBoxSize.y / 2), m_window, m_dM) {
        lastingTicks = 255;
        text.setCharacterSize(15);
    }
    void UpdateNotification();
};

