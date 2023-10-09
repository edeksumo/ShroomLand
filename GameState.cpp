#include "GameState.h"

/****************************************************/
//Private
/****************************************************/
void GameState::ButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it)
{
	if (Window::CheckButton(a_it, p_dM->Lang.quit)) {
		v_createQuitDial = true;
	}
}

void GameState::createQuitDial()
{
	if (!v_createQuitDial)
		return;
	v_createQuitDial = false;
	PushWindow(999, sf::Vector2f(250, 40), sf::Vector2f(200, 100), p_dM->Lang.quitDial, sf::Vector2f(100, 30), sf::Color::Black);
	OpenedWindow->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(300, 90), p_dM->Lang.yes, sf::Color(23, 23, 23));
	OpenedWindow->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(360, 90), p_dM->Lang.no, sf::Color(23, 23, 23));
}

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/


void GameState::Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords)
{
	updateOpenedWindowIt();

	std::multimap<std::string, Button>::iterator it = Windows.begin()->Buttons.begin();
	for (it = Windows.begin()->Buttons.begin(); it != Windows.begin()->Buttons.end(); ++it) {
		ButtonFunctions(it);
	}

	createQuitDial();
	//std::cout << "== GAMESTATE == Update Func" << std::endl;
}

void GameState::Render(sf::RenderTarget* a_target)
{
	currentStage->Render(a_target);
	//std::cout << "== GAMESTATE == Render Func" << std::endl;
}
