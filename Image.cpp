#include "Image.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

void Image::setTexture(sf::Texture* a_texture)
{
	imageSprite.setTexture(*a_texture);
}

void Image::setSprite(sf::Sprite* a_sprite)
{
	imageSprite = *a_sprite;
}

/****************************************************/
//Public
/****************************************************/
void Image::Update(sf::Vector2i* a_mousePos)
{
	//std::cout << "== IMAGE == Update Func" << std::endl;
}

void Image::Render(sf::RenderTarget* a_target)
{
	view = a_target->getView();
	p_rTarget = a_target;
	keepOnPosition();
	a_target->draw(imageSprite);
	//std::cout << "== IMAGE == Render Func" << std::endl;
}