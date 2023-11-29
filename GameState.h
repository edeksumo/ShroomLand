#pragma once
#include "State.h"
#include <stack>

class GameState :
    public State
{
public:
    enum class Directions {
        up,
        down,
        left,
        right,
        upLeft,
        upRight,
        downLeft,
        downRight,
        none
    };
private:
    void ButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it);
    void createQuitDial();
    bool v_createQuitDial;
    void switchCameraMode();
    void cameraMovementSetup();
    Camera* p_freeCam;
    bool freeCamEnable;
    void cameraFollowObject(Object* a_obj);
    void cameraFollowObject(Object* a_obj, sf::FloatRect a_limits);
    bool canEnterTile(Object* a_obj, Directions a_dir);
    bool checkCollision(sf::Vector2f a_pointLeft, sf::Vector2f a_pointRight); // it takes two points and make line out of it and checks is it colides with solidObject vector;
protected:

public:
    GameState(std::multimap<std::string, Stage>* m_stageContainer, sf::RenderWindow* m_renderWindow, sf::Window* m_window, Camera* m_mainCamera, DataMenager* m_dM, ObjectMenager* m_oM, std::stack<State*>* m_state) {
        p_state = m_state;
        p_window = m_window;
        p_mainCamera = m_mainCamera;
        p_dM = m_dM;
        p_oM = m_oM;
        p_stageContainer = m_stageContainer;
        p_renderWindow = m_renderWindow;
        freeCamEnable = false;
        cameraMovement = true;
        ActivePlayer = nullptr;
        PushWindow(1, sf::Vector2f(0, 0), sf::Vector2f(p_window->getSize().x, 30), "", sf::Vector2f(0, 0), sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.quit, sf::Vector2f(50, 20), sf::Vector2f(p_window->getSize().x - 55, 5), m_dM->Lang.quit, sf::Color::Black, 12);
        p_freeCam = new Camera(m_renderWindow, sf::Vector2f(800, 600));
        v_createQuitDial = false;
        //currentStage = &p_stageContainer->begin()->second;
        setActiveStage("cave");
        setActivePlayer(nullptr);

        StateType == Stage::EState::gameState;
        setStateForStages();
    };
    ~GameState() {
        delete p_freeCam;
    }
    
    Player* ActivePlayer;
    void setActivePlayer(Player* a_player);
    void playerControl();

    void Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords);
    void Render(sf::RenderTarget* a_target);
};

