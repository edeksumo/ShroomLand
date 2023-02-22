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
		p_game = new GameState(p_stageContainer, p_window, p_dM, p_oM, p_state);
		p_state->push(p_game);
	}
	if (Window::CheckButton(a_it, p_dM->Lang.editor)) {
		p_editor = new EditorState(p_stageContainer, p_window, p_dM, p_oM, p_state);
		p_state->push(p_editor);
	}
	if (Window::CheckButton(a_it, p_dM->Lang.settings)) {
		openSettings = true;
	}
	if (Windows.begin()->getID() == 100) {
		if (Window::CheckButton(a_it, p_dM->Lang.save)) {
			p_dM->Settings.volume = OpenedWindow->GetSliderValue(p_dM->EngineNames.volumeSlider);
			p_dM->settingsINI[p_dM->EngineNames.settings][p_dM->EngineNames.volume] = std::to_string(OpenedWindow->GetSliderValue(p_dM->EngineNames.volumeSlider));
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
	PushWindow(999, sf::Vector2f(250, 40), sf::Vector2f(200, 100), p_dM->Lang.quitDial, sf::Vector2f(100, 30), sf::Color::Black);
	OpenedWindow->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(300, 90), p_dM->Lang.yes, sf::Color(23, 23, 23));
	OpenedWindow->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(360, 90), p_dM->Lang.no, sf::Color(23, 23, 23));
}

void MainMenuState::createSettingsWindow()
{
	if (!openSettings)
		return;
	openSettings = false;
	PushWindow(100, sf::Vector2f(150, 40), sf::Vector2f(420, 450), p_dM->Lang.settings, sf::Vector2f(200, 30), sf::Color::Black);
	OpenedWindow->AddSwitch(p_dM->EngineNames.settingsSwitch, sf::Vector2f(470, 100));
	OpenedWindow->AddSlider(p_dM->EngineNames.volumeSlider, sf::Vector2f(270, 200), 200, 100);
	OpenedWindow->AddText(p_dM->Lang.volume, sf::Vector2f(210, 218), sf::Color::Black, p_dM->Lang.volume);
	OpenedWindow->AddText(p_dM->EngineNames.volumeText, sf::Vector2f(535, 218), sf::Color::Black, to_string(p_dM->Settings.volume));
	OpenedWindow->AddButton(p_dM->Lang.save, sf::Vector2f(100, 50), sf::Vector2f(300, 400), p_dM->Lang.save, sf::Color::Black);
	OpenedWindow->SetElementValue(p_dM->EngineNames.volumeSlider, p_dM->Settings.volume);
}

void MainMenuState::settingWindowUpdate()
{
	if (OpenedWindow->getID() == 100) {
		OpenedWindow->SetElementValue(p_dM->EngineNames.volumeText, std::to_string(OpenedWindow->GetSliderValue(p_dM->EngineNames.volumeSlider)));
	}
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void MainMenuState::Update(sf::Vector2i* mousePos, sf::Vector2f* a_mousePosOnCoords) {
	updateOpenedWindowIt();

	std::multimap<std::string, Button>::iterator it = Windows.begin()->Buttons.begin();
	for (it = Windows.begin()->Buttons.begin(); it != Windows.begin()->Buttons.end(); ++it) {
		ButtonFunctions(it);
	}

	settingWindowUpdate();
	createQuitDial();
	createSettingsWindow();
	closeSettings();
	//std::cout << "== MAINMENU == Update Func" << std::endl;
}

void MainMenuState::Render(sf::RenderTarget *target) {
	//std::cout << "== MAINMENU == Render Func" << std::endl;
}