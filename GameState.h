#pragma once
#include "State.h"
#include <stack>

class GameState :
    public State
{
private:
    void ButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it);
    void createQuitDial();
    bool v_createQuitDial;
protected:

public:
    GameState(std::multimap<std::string, Stage>* m_stageContainer, sf::Window* m_window, DataMenager* m_dM, ObjectMenager* m_oM, std::stack<State*>* m_state) {
        p_state = m_state;
        p_window = m_window;
        p_dM = m_dM;
        p_oM = m_oM;
        p_stageContainer = m_stageContainer;
        PushWindow(1, sf::Vector2f(0, 0), sf::Vector2f(p_window->getSize().x, 30), "", sf::Vector2f(0, 0), sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.quit, sf::Vector2f(50, 20), sf::Vector2f(p_window->getSize().x - 55, 5), m_dM->Lang.quit, sf::Color::Black, 12);

        v_createQuitDial = false;
        currentStage = &p_stageContainer->begin()->second;
    };
    
    void Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords);
    void Render(sf::RenderTarget* a_target);
};

