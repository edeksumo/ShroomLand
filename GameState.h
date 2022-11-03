#pragma once
#include "State.h"
#include <stack>

class GameState :
    public State
{
private:

protected:

public:
    GameState(sf::Window* m_window, DataMenager* m_dM, std::stack<State*>* m_state) {
        p_state = m_state;
        p_window = m_window;
        p_dM = m_dM;
        PushWindow(1, sf::Vector2f(10, 10), sf::Vector2f(10, 10), sf::Color::Green, "", sf::Vector2f(0, 0), sf::Color::Black);
    };
    
    void Update(sf::Vector2i* a_mousePos);
    void Render(sf::RenderTarget* a_target);
};

