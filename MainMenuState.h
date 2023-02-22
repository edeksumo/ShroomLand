#pragma once
#include "State.h"
#include "GameState.h"
#include "EditorState.h"
class MainMenuState :
    public State
{
private:
    bool v_createQuitDial;
    bool v_closeSettings;
    bool openSettings;

    void ButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it);
    void closeSettings();
    void createQuitDial();
    void createSettingsWindow();
    void settingWindowUpdate();
protected:
    
public:
    GameState * p_game;
    EditorState* p_editor;

    MainMenuState(std::multimap<std::string, Stage>* m_stageContainer, sf::Window* m_window, DataMenager* m_dM, ObjectMenager* m_oM, std::stack<State*>* m_state) {
        p_state = m_state;
        p_window = m_window;
        p_dM = m_dM;
        p_oM = m_oM;
        p_stageContainer = m_stageContainer;

        PushWindow(1, sf::Vector2f(10, 10), sf::Vector2f(200, 400), p_dM->Lang.gameName, sf::Vector2f(100, 30), sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.newGame, sf::Vector2f(100, 50), sf::Vector2f(30, 60), m_dM->Lang.newGame, sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.settings, sf::Vector2f(100, 50), sf::Vector2f(30, 130), m_dM->Lang.settings, sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.editor, sf::Vector2f(100, 50), sf::Vector2f(30, 200), m_dM->Lang.editor, sf::Color::Black);
        OpenedWindow->AddButton(m_dM->Lang.quit, sf::Vector2f(100, 50), sf::Vector2f(30, 340), m_dM->Lang.quit, sf::Color::Black);

        p_game = nullptr;
        p_editor = nullptr;
        v_createQuitDial = false;
        v_closeSettings = false;
        openSettings = false;
    };
    ~MainMenuState() {
        delete p_game;
    }

    void Update(sf::Vector2i * mousePos, sf::Vector2f* a_mousePosOnCoords);
    void Render(sf::RenderTarget * target);
};

