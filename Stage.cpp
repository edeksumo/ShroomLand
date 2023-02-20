#include "Stage.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void Stage::addTile(sf::Vector2f a_pos, Tile* a_tileptr)
{
	TileDeque.push_back(*a_tileptr);
	auto v = sf::Vector2f(a_pos.x * 32, a_pos.y * 32);
	TileDeque.back().sprite.setPosition(v);
}

void Stage::Update(sf::Vector2i* a_mousePos)
{
	for (Tile& i : TileDeque) {
		i.Update(a_mousePos);
	}
}

void Stage::Render(sf::RenderTarget* a_target)
{
	for (Tile & i : TileDeque) {
		i.Render(a_target);
		
		//std::cout << i.sprite.getPosition().x << " " << i.sprite.getPosition().y << std::endl;
	}
}
