#include "State.h"

/****************************************************/
//Private
/****************************************************/
void State::Keyboard()
{
	if (Keyboard::checkKeyState(sf::Keyboard::Escape) == Keyboard::KeyState::pressed)
	{
		if (Windows.size() > 1) {
			Windows.begin()->setToClose = true;
			return;
		}
		else {
			PushWindow(999, sf::Vector2f(250, 40), sf::Vector2f(200, 100), p_dM->Lang.quitDial, sf::Vector2f(100, 30), sf::Color::Black);
			Windows.begin()->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(300, 90), p_dM->Lang.yes, sf::Color(23, 23, 23));
			Windows.begin()->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(360, 90), p_dM->Lang.no, sf::Color(23, 23, 23));
		}
	}
}

void State::defaultButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it)
{
	if (Windows.begin()->getID() == 999) {
		if (Window::CheckButton(a_it, p_dM->Lang.yes)) {
			if (p_state->size()) {
				stateQuit = true;
				return;
			}
		}
		if (Window::CheckButton(a_it, p_dM->Lang.no)) {
			if (Windows.size()) {
				Windows.begin()->setToClose = true;
				return;
			}
		}
	}
}

void State::DimmerUpdate(sf::Vector2i* a_mousePos)
{
	if (MainDimmer == nullptr)
		return;
	MainDimmer->Update(a_mousePos);
}

void State::DimmerRender(sf::RenderTarget* a_target)
{
	if (MainDimmer == nullptr)
		return;
	MainDimmer->Render(a_target);
}

/****************************************************/
//Protected
/****************************************************/
void State::setStateForStages()
{
	for (auto it = p_stageContainer->begin(); it != p_stageContainer->end(); ++it) {
		it->second.setCurrentState(StateType);
	}
}
void State::updateOpenedWindowIt()
{
	if (nbOfOpenedWindows != Windows.size()) {
		nbOfOpenedWindows = Windows.size();
		OpenedWindow = Windows.begin();
	}
}
/****************************************************/
//Public
/****************************************************/
void State::setActiveStage(string a_name)
{
	if (p_stageContainer == nullptr) {
		return;	//future throw
	}
	if (p_stageContainer->find(a_name) == p_stageContainer->end()) {
		std::cout << "There is not stage with name: " << a_name;
	}
	auto stg = p_stageContainer->find(a_name);
	currentStage = &stg->second;
}

void State::moveCamera(Camera* a_cam, float a_speed)
{
	if (!cameraMovement)
		return;
	if (Keyboard::checkKeyState(sf::Keyboard::Up) == Keyboard::KeyState::hold) {
		a_cam->move(sf::Vector2f(0.f, -a_speed));
	}
	else if (Keyboard::checkKeyState(sf::Keyboard::Down) == Keyboard::KeyState::hold) {
		a_cam->move(sf::Vector2f(0.f, a_speed));
	}
	if (Keyboard::checkKeyState(sf::Keyboard::Left) == Keyboard::KeyState::hold) {
		a_cam->move(sf::Vector2f(-a_speed, 0.f));
	}
	else if (Keyboard::checkKeyState(sf::Keyboard::Right) == Keyboard::KeyState::hold) {
		a_cam->move(sf::Vector2f(a_speed, 0.f));
	}
}
void State::PushWindow(unsigned int a_id, sf::Vector2f a_pos, sf::Vector2f a_size, std::string a_text, sf::Vector2f a_textPos, sf::Color a_textColor)
{
	Windows.push_front(Window(a_id, a_pos, a_size, a_text, a_textColor, a_textPos, p_window, p_dM));
	OpenedWindow = Windows.begin();
}

void State::RenderWindows(sf::RenderTarget* a_target)
{
	if (Windows.size() > 0) {
		std::list<Window>::iterator it_1;
		for (it_1 = Windows.begin(); it_1 != Windows.end(); ++it_1) {
			if ((it_1 == Windows.begin()) && (it_1->getUIState() == UI::UIState::inActive)) {
				it_1->setUIState(UI::UIState::active);
				std::multimap<std::string, Button>::iterator it = it_1->Buttons.begin();
				for (it = it_1->Buttons.begin(); it != it_1->Buttons.end(); ++it) {
					it->second.setUIState(UI::UIState::active);
				}
			}
			if (Windows.size() > 1) {
				if ((it_1 != Windows.begin()) && (it_1->getUIState() == UI::UIState::active)) {
					it_1->setUIState(UI::UIState::inActive);
					std::multimap<std::string, Button>::iterator it = it_1->Buttons.begin();
					for (it = it_1->Buttons.begin(); it != it_1->Buttons.end(); ++it) {
						it->second.setUIState(UI::UIState::inActive);
					}
				}
			}
		}
		std::list<Window>::reverse_iterator it;
		for (it = Windows.rbegin(); it != Windows.rend(); ++it) {
			it->Render(a_target);
		}
	}
	DimmerRender(a_target);
	RenderNotifications(a_target);
}

void State::UpdateWindows(sf::Vector2i* a_mousePos)
{
	DimmerUpdate(a_mousePos);
	UpdateNotifications(a_mousePos);
	if (MainDimmer->getMode() != Dimmer::EMode::none)
		return;
	Keyboard();
	if (Windows.front().setToClose)
		Windows.pop_front();
	if (Windows.size()) {
		Windows.begin()->Update(a_mousePos);
		std::multimap<std::string, Button>::iterator it = Windows.begin()->Buttons.begin();
		for (it = Windows.begin()->Buttons.begin(); it != Windows.begin()->Buttons.end(); ++it) {
			defaultButtonFunctions(it);
		}
	}
}

void State::PushNotification(std::string a_text, sf::Color a_textColor)
{
	Notifications.push_front(Notification(a_text, a_textColor, p_window, p_dM));
}

void State::RenderNotifications(sf::RenderTarget* a_target)
{
	if (Notifications.size() > 0) {
		std::list<Notification>::reverse_iterator it;
		for (it = Notifications.rbegin(); it != Notifications.rend(); ++it) {
			it->Render(a_target);
		}
	}
}

void State::UpdateNotifications(sf::Vector2i* a_mousePos)
{
	if (Notifications.size() > 0) {
		Notifications.front().UpdateNotification();
		if (Notifications.front().setToClose)
			Notifications.pop_front();
	}
}
