#include "Text.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void Text::setText(string a_text)
{
	text.setString(a_text);
}

void Text::Update(sf::Vector2i* a_mousePos)
{
	//std::cout << "== TEXT == Update Func" << std::endl;
}

void Text::Render(sf::RenderTarget* a_target)
{
	view = a_target->getView();
	keepOnPosition();
	a_target->draw(text);

	//std::cout << "== TEXT == Render Func" << std::endl;
}