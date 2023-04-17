#pragma once
#include "State.h"
class EditorState :
    public State
{
private:
    enum class EditorFunction {
        placeTile,
        changeVariant,
        placeObject
    };

    Stage* currentStage;
    sf::RectangleShape cursorShape;
    sf::Sprite activeSprite;
    EditorFunction currentFunction;
    int currentTyleType;
    Tile* selectedTile;
    std::map<int, std::map<int, GridCell>> tileUpdateMap;
    std::string editorFuncNames[3]{
        "Tiles",
        "Variants",
        "Objects"
    };


    void mousePosUpdate(sf::Vector2f* a_mousePosOnCoords);
    void saveStages();
    void buttonFunctions(const std::multimap<std::string, Button>::iterator& a_it);
    void placeTiles();
    void addTilesToUpdate(int a_x, int a_y);
    void changeVariants();
    void placeObjects();
    void wheelFunctions();
    void updateText();
    void cursorUpdateAndRender(sf::RenderTarget* a_target);
    void mouseFunctions();
    void updateTiles();
    void setBackgroundTiles();
    void editorFunction(const std::multimap<std::string, Button>::iterator& a_it);
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
        selectedTile = nullptr;
        currentFunction = EditorState::EditorFunction::placeTile;

        PushWindow(1, sf::Vector2f(0, 0), sf::Vector2f(135, p_window->getSize().y), "", sf::Vector2f(0, 0), sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.save, sf::Vector2f(70, 40), sf::Vector2f(15, 15), m_dM->Lang.save, sf::Color::Black);
        OpenedWindow->AddSlider("Cursor_Size", sf::Vector2f(38, 70), 60, 2);
        OpenedWindow->AddButton("Editor_Func", sf::Vector2f(105, 40), sf::Vector2f(15, 110), editorFuncNames[0], sf::Color::Black);
        OpenedWindow->AddText("Current_Obj_Name", sf::Vector2f(60, 165), sf::Color::Black, "Grass");
        OpenedWindow->AddImage("Obj_Image", sf::Vector2f(50, 175), &p_dM->emptyTxt);
        OpenedWindow->SetElementValue("Cursor_Size", 1);
        //OpenedWindow->AddButton("Update_Tiles", sf::Vector2f(105, 40), sf::Vector2f(15, 160), "Update Tl", sf::Color::Black);
        updateText();
    };

    void Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords);
    void Render(sf::RenderTarget* a_target);
};

