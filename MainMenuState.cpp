#include "MainMenuState.h"

/****************************************************/
//Private
/****************************************************/
void MainMenuState::ButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it)
{
	if (Window::CheckButton(a_it, p_dM->Lang.quit)) {
		v_createQuitDial = true;
	}
	if (Window::CheckButton(a_it, p_dM->Lang.newGame)) {
		p_game = new GameState(p_window, p_dM, p_state);
		p_state->push(p_game);
	}
	if (Window::CheckButton(a_it, p_dM->Lang.editor)) {
		p_editor = new EditorState(p_window, p_dM, p_state);
		p_state->push(p_editor);
	}
	if (Window::CheckButton(a_it, p_dM->Lang.settings)) {
		openSettings = true;
	}
	if (Windows.begin()->getID() == 100) {
		if (Window::CheckButton(a_it, p_dM->Lang.save)) {
			p_dM->settingsINI["settings"]["volume"] = std::to_string(Windows.begin()->Sliders.begin()->second.getValue());
			p_dM->settings->write(p_dM->settingsINI);
			v_closeSettings = true;
		}
	}
}
void MainMenuState::closeSettings()
{
	if (!v_closeSettings)
		return;
	v_closeSettings = false;
	Windows.pop_front();
}
void MainMenuState::createQuitDial()
{
	if (!v_createQuitDial)
		return;
	v_createQuitDial = false;
	PushWindow(999, sf::Vector2f(250, 40), sf::Vector2f(200, 100), sf::Color::Blue, p_dM->Lang.quitDial, sf::Vector2f(100, 30), sf::Color::Black);
	Windows.begin()->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(300, 100), sf::Color(50, 40, 30), p_dM->Lang.yes, sf::Color(23, 23, 23));
	Windows.begin()->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(360, 100), sf::Color(50, 40, 30), p_dM->Lang.no, sf::Color(23, 23, 23));
}
void MainMenuState::createSettingsWindow()
{
	if (!openSettings)
		return;
	openSettings = false;
	PushWindow(100, sf::Vector2f(150, 40), sf::Vector2f(400, 450), sf::Color::Red, p_dM->Lang.settings, sf::Vector2f(200, 30), sf::Color::Black);
	Windows.begin()->AddSwitch("Switch", sf::Vector2f(470, 100), sf::Color::Magenta);
	Windows.begin()->AddSlider("Slider", sf::Vector2f(270, 200), sf::Color::Blue, 230, 100);
	Windows.begin()->AddText("test3", sf::Vector2f(220, 220), sf::Color::Black, p_dM->Lang.volume);
	Windows.begin()->AddText("Text", sf::Vector2f(520, 220), sf::Color::Black, "2");
	Windows.begin()->AddButton(p_dM->Lang.save, sf::Vector2f(100, 50), sf::Vector2f(300, 400), sf::Color(50, 40, 30), p_dM->Lang.save, sf::Color::Black);
	Windows.begin()->SetElementValue("Slider", p_dM->Settings.volume);
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void MainMenuState::Update(sf::Vector2i* mousePos) {
	//std::cout << "== MAINMENU == Update Func" << std::endl;
	//loop for mainmenu window buttons functions
	
	if (Keyboard::checkKeyState(sf::Keyboard::A) == Keyboard::KeyState::pressed) {

		if (Windows.begin()->getID() == 100) {
			std::cout << "pressed";
			Windows.begin()->SetElementValue("Slider", Windows.begin()->Sliders.begin()->second.getValue() +1);
		}
	}
	if (Windows.begin()->getID() == 100) {
		Windows.begin()->SetElementValue("Text", Windows.begin()->Sliders.begin()->second.getValue());
		Windows.begin()->SetElementValue("Text", std::to_string(Windows.begin()->Sliders.begin()->second.getValue()));
		p_dM->Settings.volume = Windows.begin()->Sliders.begin()->second.getValue();
	}
	std::multimap<std::string, Button>::iterator it = Windows.begin()->Buttons.begin();
	for (it = Windows.begin()->Buttons.begin(); it != Windows.begin()->Buttons.end(); ++it) {
		ButtonFunctions(it);
	}
	createQuitDial();
	createSettingsWindow();
	closeSettings();
}
void MainMenuState::Render(sf::RenderTarget *target) {
	//std::cout << "== MAINMENU == Render Func" << std::endl;
}