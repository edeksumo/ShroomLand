#pragma once
#include "State.h"
#include <stack>

class GameState :
    public State
{
private:

protected:

public:
    GameState(std::multimap<std::string, Stage>* m_stageContainer, sf::Window* m_window, DataMenager* m_dM, ObjectMenager* m_oM, std::stack<State*>* m_state) {
        p_state = m_state;
        p_window = m_window;
        p_dM = m_dM;
        p_oM = m_oM;
        p_stageContainer = m_stageContainer;
        PushWindow(1, sf::Vector2f(10, 10), sf::Vector2f(10, 10), "", sf::Vector2f(0, 0), sf::Color::Black);
    };
    
    void Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords);
    void Render(sf::RenderTarget* a_target);
};

