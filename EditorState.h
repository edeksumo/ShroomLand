#pragma once
#include "State.h"
class EditorState :
    public State
{
private:
    Stage* currentStage;

    void mousePosUpdate(sf::Vector2f* a_mousePosOnCoords);
    void saveStages();
    void buttonFunctions(const std::multimap<std::string, Button>::iterator& a_it);
    void mouseFunctions();
protected:

public:  
    Grid MousePosOnGrid;

    EditorState(std::multimap<std::string, Stage>* m_stageContainer, sf::Window* m_window, DataMenager* m_dM, ObjectMenager* m_oM, std::stack<State*>* m_state) {
        MousePosOnGrid = Grid(0, 0);
        p_state = m_state;
        p_window = m_window;
        p_dM = m_dM;
        p_oM = m_oM;
        p_stageContainer = m_stageContainer;
        currentStage = &p_stageContainer->begin()->second;
        PushWindow(1, sf::Vector2f(0, 0), sf::Vector2f(100, 300), "", sf::Vector2f(0, 0), sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.save, sf::Vector2f(70, 40), sf::Vector2f(15, 15), m_dM->Lang.save, sf::Color::Black);
    };

    void Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords);
    void Render(sf::RenderTarget* a_target);
};

