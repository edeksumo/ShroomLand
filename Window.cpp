#include "Window.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
bool Window::CheckButton(const std::multimap<std::string, Button>::iterator& a_it, std::string a_name)
{
	if (a_it->first == a_name)
		if (a_it->second.isPressed())
			return true;
	return false;
}

unsigned int Window::getID()
{
	return ID;
}

void Window::AddButton(std::string a_name, sf::Vector2f a_size, sf::Vector2f a_pos, sf::Color a_color, std::string a_text, sf::Color a_textColor){

	Buttons.emplace(a_name, Button(a_size, a_pos, a_color, a_text, a_textColor, p_dM));
}

void Window::AddSwitch(std::string a_name, sf::Vector2f a_pos, sf::Color a_color)
{
	Switches.emplace(a_name, Switch(a_pos, a_color, p_dM));
}

void Window::AddSlider(std::string a_name, sf::Vector2f a_pos, sf::Color a_color, float a_lenght, unsigned int a_maxValue)
{
	Sliders.emplace(a_name, Slider(a_pos, a_color, a_lenght, a_maxValue, p_dM));
}

void Window::AddText(std::string a_name, sf::Vector2f a_pos, sf::Color a_color, std::string a_text)
{
	Texts.emplace(a_name, Text(a_pos, a_text, a_color, p_dM));
}

void Window::SetElementValue(std::string a_eleName, int a_val)
{
	std::multimap<std::string, Switch>::iterator it_1 = Switches.begin();
	for (it_1 = Switches.begin(); it_1 != Switches.end(); ++it_1) {
		if (it_1->first == a_eleName) {
			if (a_val == 1) {
				it_1->second.setState(Button::ButtonState::Pressed);
				return;
			}
			else if (a_val == 0) {
				it_1->second.setState(Button::ButtonState::Free);
				return;
			}
			else {
				std::cout << "== WINDOW == SetElementValue Func: Wrong Val" << std::endl;
				return;
			}
		}
	}
	std::multimap<std::string, Slider>::iterator it_2 = Sliders.begin();
	for (it_2 = Sliders.begin(); it_2 != Sliders.end(); ++it_2) {
		if (it_2->first == a_eleName) {
			if (a_val <= it_2->second.getMaxValue()) {
				it_2->second.setValue(a_val);
				return;
			}
			else {
				std::cout << "== WINDOW == SetElementValue Func: Wrong Val" << std::endl;
				return;
			}
		}
	}
}
void Window::SetElementValue(std::string a_eleName, std::string a_val) {
	std::multimap<std::string, Text>::iterator it = Texts.begin();
	for (it = Texts.begin(); it != Texts.end(); ++it) {
		if (it->first == a_eleName) {
			it->second.setText(a_val);
		}
	}
}

int Window::GetSliderValue(std::string a_eleName)
{
	std::multimap<std::string, Slider>::iterator it = Sliders.begin();
	for (it = Sliders.begin(); it != Sliders.end(); ++it) {
		if (it->first == a_eleName) {
			return it->second.getValue();
		}
	}
}

bool Window::IsSwitchOn(std::string a_eleName)
{
	std::multimap<std::string, Switch>::iterator it = Switches.begin();
	for (it = Switches.begin(); it != Switches.end(); ++it) {
		if (it->first == a_eleName) {
			return it->second.isPressed();
		}
	}
}

void Window::Update(sf::Vector2i* a_mousePos) {
	std::multimap<std::string, Button>::iterator it = Buttons.begin();
	for (it = Buttons.begin(); it != Buttons.end(); ++it) {
		it->second.Update(a_mousePos);
	}
	std::multimap<std::string, Switch>::iterator it_1 = Switches.begin();
	for (it_1 = Switches.begin(); it_1 != Switches.end(); ++it_1) {
		it_1->second.Update(a_mousePos);
	}
	std::multimap<std::string, Slider>::iterator it_2 = Sliders.begin();
	for (it_2 = Sliders.begin(); it_2 != Sliders.end(); ++it_2) {
		it_2->second.Update(a_mousePos);
	}
	std::multimap<std::string, Text>::iterator it_3 = Texts.begin();
	for (it_3 = Texts.begin(); it_3 != Texts.end(); ++it_3) {
		it_3->second.Update(a_mousePos);
	}
	//std::cout << "== WINDOW == Update Func"  << std::endl;
}

void Window::Render(sf::RenderTarget* a_target) {
	view = a_target->getView();
	keepOnPosition();
	a_target->draw(background);
	a_target->draw(text);
	renderShadow(a_target);
	std::multimap<std::string, Button>::iterator it = Buttons.begin();
	for (it = Buttons.begin(); it != Buttons.end(); ++it) {
		it->second.Render(a_target);
	}
	std::multimap<std::string, Switch>::iterator it_1 = Switches.begin();
	for (it_1 = Switches.begin(); it_1 != Switches.end(); ++it_1) {
		it_1->second.Render(a_target);
	}
	std::multimap<std::string, Slider>::iterator it_2 = Sliders.begin();
	for (it_2 = Sliders.begin(); it_2 != Sliders.end(); ++it_2) {
		it_2->second.Render(a_target);
	}
	std::multimap<std::string, Text>::iterator it_3 = Texts.begin();
	for (it_3 = Texts.begin(); it_3 != Texts.end(); ++it_3) {
		it_3->second.Render(a_target);
	}
	//std::cout << "== WINDOW == Render Func" << std::endl;
}