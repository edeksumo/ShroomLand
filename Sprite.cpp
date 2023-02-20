#include "Sprite.h"

void Sprite::Render(sf::RenderTarget* a_target)
{
	a_target->draw(sprite);
}
