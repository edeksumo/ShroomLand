#include "Dimmer.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/


/****************************************************/
//Public
/****************************************************/
void Dimmer::FadeIn(unsigned int a_speed)
{
	currentTransparency+= a_speed;
	if (currentTransparency >= MAX_TRANSPARENCY) {
		currentTransparency = MAX_TRANSPARENCY;
		Mode = EMode::none;
	}

}

void Dimmer::FadeOut(unsigned int a_speed)
{
	currentTransparency -= a_speed;
	if (currentTransparency <= MIN_TRANSPARENCY) {
		currentTransparency = MIN_TRANSPARENCY;
		Mode = EMode::none;
	}
}

void Dimmer::setTransparency(unsigned int a_transparency)
{
	currentTransparency = a_transparency;
	if (a_transparency > MAX_TRANSPARENCY)
		currentTransparency = MAX_TRANSPARENCY;
}

void Dimmer::setMode(Dimmer::EMode a_mode)
{
	Mode = a_mode;
}

Dimmer::EMode Dimmer::getMode()
{
	return Mode;
}

void Dimmer::Update(sf::Vector2i* a_mousePos)
{
	switch (Mode)
	{
	case Dimmer::EMode::none:
		break;
	case Dimmer::EMode::dim:
		FadeIn(4);
		break;
	case Dimmer::EMode::brighten:
		FadeOut(4);
		break;
	}
	shadow.setFillColor(sf::Color(0, 0, 0, currentTransparency));
	if (currentTransparency == MAX_TRANSPARENCY)
		isBlacked = true;
	else
		isBlacked = false;
}

void Dimmer::Render(sf::RenderTarget* a_target)
{
	view = a_target->getView();
	p_rTarget = a_target;
	keepOnPosition();
	a_target->draw(shadow);
	//std::cout << "== IMAGE == Render Func" << std::endl;
}

bool Dimmer::IsBlacked()
{
	return isBlacked;
}
