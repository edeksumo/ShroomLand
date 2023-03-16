#pragma once
#include "State.h"
class EditorState :
    public State
{
private:
    Stage* currentStage;
    sf::RectangleShape cursorShape;

    void mousePosUpdate(sf::Vector2f* a_mousePosOnCoords);
    void saveStages();
    void buttonFunctions(const std::multimap<std::string, Button>::iterator& a_it);
    void cursorUpdateAndRender(sf::RenderTarget* a_target);
    void mouseFunctions();
    void updateTiles();
    void setBackgroundTiles();
    int currentTyleType;
protected:

public:  
    GridCell MousePosOnGrid;

    EditorState(std::multimap<std::string, Stage>* m_stageContainer, sf::Window* m_window, DataMenager* m_dM, ObjectMenager* m_oM, std::stack<State*>* m_state) {
        MousePosOnGrid = GridCell(0, 0);
        p_state = m_state;
        p_window = m_window;
        p_dM = m_dM;
        p_oM = m_oM;
        currentTyleType = 0;
        p_stageContainer = m_stageContainer;
        cursorShape.setOutlineColor(sf::Color::White);
        cursorShape.setOutlineThickness(1.f);
        cursorShape.setFillColor(sf::Color(0, 0, 0, 0));
        currentStage = &p_stageContainer->begin()->second;
        PushWindow(1, sf::Vector2f(0, 0), sf::Vector2f(135, 300), "", sf::Vector2f(0, 0), sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.save, sf::Vector2f(70, 40), sf::Vector2f(15, 15), m_dM->Lang.save, sf::Color::Black);
        OpenedWindow->AddSlider("Cursor_Size", sf::Vector2f(38, 70), 60, 2);
        OpenedWindow->AddButton("Tile_Type", sf::Vector2f(105, 40), sf::Vector2f(15, 110), "Grass", sf::Color::Black);
        //OpenedWindow->AddButton("Update_Tiles", sf::Vector2f(105, 40), sf::Vector2f(15, 160), "Update Tl", sf::Color::Black);

    };

    void Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords);
    void Render(sf::RenderTarget* a_target);
};

