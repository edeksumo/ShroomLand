#include "Switch.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void Switch::setState(Button::ButtonState a_state)
{
	buttonState = a_state;
}

Button::ButtonState Switch::getState()
{
	return buttonState;
}

void Switch::Update(sf::Vector2i* a_mousePos)
{
	pressed(a_mousePos);
	mouseEnter(a_mousePos);
	mouseQuit(a_mousePos);
	//std::cout << "== SWITCH == Update Func" << std::endl;
}

void Switch::Render(sf::RenderTarget* a_target)
{
	view = a_target->getView();
	keepOnPosition();
	a_target->draw(background);
	setTransparency();
	drawSelector(a_target);
	renderShadow(a_target);

	//std::cout << "== SWITCH == Render Func" << std::endl;
}
