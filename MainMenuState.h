#pragma once
#include "State.h"
#include "GameState.h"
#include "EditorState.h"
class MainMenuState :
    public State
{
private:

    void ButtonFunctions(const std::multimap<std::string, Button>::iterator &a_it);
    bool v_createQuitDial;
    bool v_closeSettings;
    bool openSettings;
    void closeSettings();
    void createQuitDial();
    void createSettingsWindow();
protected:
    
public:
    GameState * p_game;
    EditorState* p_editor;
    MainMenuState(sf::Window* m_window, DataMenager* m_dM, std::stack<State*>* m_state) {
        p_state = m_state;
        p_window = m_window;
        p_dM = m_dM;
        PushWindow(1, sf::Vector2f(10, 10), sf::Vector2f(200, 400), sf::Color::Green, p_dM->Lang.gameName, sf::Vector2f(90, 20), sf::Color::Black);
        Windows.begin()->AddButton(m_dM->Lang.newGame, sf::Vector2f(100, 50), sf::Vector2f(30, 60), sf::Color(50, 40, 30), m_dM->Lang.newGame, sf::Color::Black);
        Windows.begin()->AddButton(m_dM->Lang.settings, sf::Vector2f(100, 50), sf::Vector2f(30, 130), sf::Color(50, 40, 30), m_dM->Lang.settings, sf::Color::Black);
        Windows.begin()->AddButton(m_dM->Lang.editor, sf::Vector2f(100, 50), sf::Vector2f(30, 200), sf::Color(50, 40, 30), m_dM->Lang.editor, sf::Color::Black);
        Windows.begin()->AddButton(m_dM->Lang.quit, sf::Vector2f(100, 50), sf::Vector2f(30, 350), sf::Color(50, 40, 30), m_dM->Lang.quit, sf::Color::Black);

        //std::cout << p_dM;
        p_game = nullptr;
        p_editor = nullptr;
        v_createQuitDial = false;
        v_closeSettings = false;
        openSettings = false;
    };
    ~MainMenuState() {
        delete p_game;
    }
    void Update(sf::Vector2i * mousePos);
    void Render(sf::RenderTarget * target);

};

