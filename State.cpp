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
			PushWindow(999, sf::Vector2f(250, 40), sf::Vector2f(200, 100), sf::Color::Blue, p_dM->Lang.quitDial, sf::Vector2f(100, 30), sf::Color::Black);
			Windows.begin()->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(300, 100), sf::Color(50, 40, 30), p_dM->Lang.yes, sf::Color(23, 23, 23));
			Windows.begin()->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(360, 100), sf::Color(50, 40, 30), p_dM->Lang.no, sf::Color(23, 23, 23));
		}
	}
}
void State::defaultButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it)
{
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
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void State::PushWindow(unsigned int a_id, sf::Vector2f a_pos, sf::Vector2f a_size, sf::Color a_color, std::string a_text, sf::Vector2f a_textPos, sf::Color a_textColor)
{
	Windows.push_front(Window(a_id, a_pos, a_size, a_color, a_text, a_textColor, a_textPos, p_window, p_dM));
}


void State::RenderWindows(sf::RenderTarget* a_target)
{
	if (Windows.size() > 0) {
		std::list<Window>::iterator it_1;
		for (it_1 = Windows.begin(); it_1 != Windows.end(); ++it_1) {
			if ((it_1 == Windows.begin()) && (it_1->getUIState() == UI::UIState::inActive)) {
				//it_1->setColor(sf::Color(it_1->getColor().r, it_1->getColor().g - 10, it_1->getColor().b));
				it_1->setUIState(UI::UIState::active);
				std::multimap<std::string, Button>::iterator it = it_1->Buttons.begin();
				for (it = it_1->Buttons.begin(); it != it_1->Buttons.end(); ++it) {
					it->second.setUIState(UI::UIState::active);
				}
			}
			if (Windows.size() > 1) {
				if ((it_1 != Windows.begin()) && (it_1->getUIState() == UI::UIState::active)) {
					//it_1->setColor(sf::Color(it_1->getColor().r, it_1->getColor().g - 10, it_1->getColor().b));
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
}

void State::UpdateWindows(sf::Vector2i* a_mousePos)
{

	if (Windows.begin()->setToClose)
		Windows.pop_front();
	Keyboard();
	if (Windows.size()) {
		Windows.begin()->Update(a_mousePos);
		std::multimap<std::string, Button>::iterator it = Windows.begin()->Buttons.begin();
		for (it = Windows.begin()->Buttons.begin(); it != Windows.begin()->Buttons.end(); ++it) {
			defaultButtonFunctions(it);
		}
	}
	//std::cout << buttonCooldown << std::endl;
}
