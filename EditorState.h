#pragma once
#include "State.h"
class EditorState :
    public State
{
private:
    enum class EditorFunction {
        placeTile,
        changeVariant,
        placeObject,
        specialObjects
    };

    sf::RectangleShape cursorShape;
    sf::Sprite activeSprite;
    EditorFunction currentFunction;
    int currentTyleType;
    int currentTileID;
    Tile* selectedTile;
    Object* selectedObject;
    std::map<int, std::map<int, GridCell>> tileUpdateMap;
    bool singleTileMode;
    bool v_createClearDial;
    bool v_closeClearDial;
    bool v_addStageDial;
    bool v_closeAddStageDial;
    bool v_delStageDial;
    bool v_closeDelStageDial;
    bool v_addSpecialObjectDial;
    bool v_closeSpecialObjectDial;
    sf::Vector2f mousePosVec;
    sf::Vector2f mousePosPressed;
    sf::Vector2f mousePosPressed_SpcObj;
    sf::Vector2f tempObjPos;
    unsigned int objectIdOffset;
    sf::Sprite emptySprite;
    unsigned int stageOffset;
    //for adding new stage
    std::string inputString;
    sf::String input;
    unsigned int v_inputTimer;

    unsigned int spcObjWheelOffset;

    std::string editorFuncNames[4]{
        "Tiles",
        "Variants",
        "Objects",
        "Spc Objects"
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
    void clearStage();
    void closeDialWindow();
    void createClearDial();
    void createAddStageDial();
    void closeAddStageDial();
    void inputWindowMenager();
    void closeDelStageDial();
    void createDelStageDial();
    void createAddSpecialObjDial();
    void closeAddSpecialObjDial();
    void changeStage(bool a_next);
    void addStage();
    void deleteStage();
    void inputTimer();

protected:

public:  
    GridCell MousePosOnGrid;

    EditorState(StageMenager* m_stgM, sf::Window* m_window, Camera* m_mainCamera, DataMenager* m_dM, ObjectMenager* m_oM, std::stack<State*>* m_state, sf::Event* m_event) {
        MousePosOnGrid = GridCell(0, 0);
        p_state = m_state;
        p_window = m_window;
        p_mainCamera = m_mainCamera;
        p_dM = m_dM;
        p_oM = m_oM;
        p_event = m_event;
        currentTyleType = 0;
        p_stgM = m_stgM;
        cursorShape.setOutlineColor(sf::Color::White);
        cursorShape.setOutlineThickness(1.f);
        cursorShape.setFillColor(sf::Color(0, 0, 0, 0));
        currentStage = &p_stgM->StageContainer.begin()->second;
        selectedTile = nullptr;
        selectedObject = nullptr;
        currentFunction = EditorState::EditorFunction::placeTile;
        currentTileID = DEFAULT_BASE_TILE;
        singleTileMode = false;
        v_createClearDial = false;
        v_closeClearDial = false;
        v_addStageDial = false;
        v_closeAddStageDial = false;
        v_delStageDial = false;
        v_closeDelStageDial = false;
        v_addSpecialObjectDial = false;
        v_closeSpecialObjectDial = false;
        mousePosPressed = sf::Vector2f(0, 0);
        mousePosPressed_SpcObj = sf::Vector2f(0, 0);
        tempObjPos = sf::Vector2f(0, 0);
        objectIdOffset = 0;
        stageOffset = 1;

        cameraMovement = true;

        inputString = "";
        v_inputTimer = 0;

        spcObjWheelOffset = 0;

        PushWindow(1, sf::Vector2f(0, 0), sf::Vector2f(135, p_window->getSize().y), "", sf::Vector2f(0, 0), sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.save, sf::Vector2f(105, 40), sf::Vector2f(15, 15), m_dM->Lang.save, sf::Color::White);
        OpenedWindow->AddSlider("Cursor_Size", sf::Vector2f(38, 70), 60, 2);
        OpenedWindow->AddButton("Editor_Func", sf::Vector2f(105, 40), sf::Vector2f(15, 110), editorFuncNames[0], sf::Color::Black);
        OpenedWindow->AddText("Current_Obj_Name", sf::Vector2f(60, 165), sf::Color::Black, "Grass");
        OpenedWindow->AddImage("Tile_Image", sf::Vector2f(50, 175), &p_dM->emptyTxt);
        OpenedWindow->AddImage("Obj_Image", sf::Vector2f(50, 340), &p_dM->emptyTxt);
        OpenedWindow->AddText("Current_Stage_Name", sf::Vector2f(65, p_window->getSize().y - 225), sf::Color::Black, p_stgM->StageContainer.begin()->first);
        OpenedWindow->AddButton("Next_Stage", Button::GraphicalButton::right, sf::Vector2f(90, p_window->getSize().y - 205));
        OpenedWindow->AddButton("Back_Stage", Button::GraphicalButton::left, sf::Vector2f(15, p_window->getSize().y - 205));
        OpenedWindow->AddButton("Add_Stage", sf::Vector2f(105, 40), sf::Vector2f(15, p_window->getSize().y - 155), "Add Stg", sf::Color::White);
        OpenedWindow->AddButton("Clear_Stage", sf::Vector2f(105, 40), sf::Vector2f(15, p_window->getSize().y - 105), "Clear Stg", sf::Color::White);
        OpenedWindow->AddButton("Delete_Stage", sf::Vector2f(105, 40), sf::Vector2f(15, p_window->getSize().y - 55), "Delete Stg", sf::Color::Red);
        OpenedWindow->SetElementValue("Cursor_Size", 1);
        updateText();

        StateType = Stage::EState::editorState;
        setStateForStages();

        Keyboard::resetButtons();
        MainDimmer = new Dimmer(p_window, p_dM);
    };

    void Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords);
    void Render(sf::RenderTarget* a_target);
};

