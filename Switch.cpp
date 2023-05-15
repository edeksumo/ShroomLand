#include "Switch.h"
/****************************************************/
//Private
/****************************************************/

void Switch::setTexture()
{
	if (state == Button::SwitchState::off) {
		backgroundSprite.setTexture(p_dM->switchBackgroundTxt);
	}
	else if (state == Button::SwitchState::on) {
		backgroundSprite.setTexture(p_dM->switchBackgroundTickTxt);
	}
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void Switch::setState(Button::SwitchState a_state)
{
	//buttonState = a_state;
	state = a_state;
}

Button::SwitchState Switch::getState()
{
	return state;
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
	p_rTarget = a_target;
	keepOnPosition();
	//a_target->draw(background);
	setTexture();
	a_target->draw(backgroundSprite);
	setTransparency();
	drawSelector(a_target);

	//std::cout << "== SWITCH == Render Func" << std::endl;
}