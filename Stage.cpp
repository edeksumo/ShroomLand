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
void Stage::addTile(Grid a_pos, unsigned int a_ID)
{
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	/// Keeps track of all tiles and deleting those ones that exist in one spot on the grid
	int i = 0;
	bool b = false;
	for (auto &it : TileDeque) {
		if (it.GetGridPosition() == a_pos) {
			std::cout << "== STAGE == addTile func: Two Tiles on one spot on the grid; old one will be eresed" << std::endl;
			b = true;
			break;
		}
		i++;
	}
	if (b)
		TileDeque.erase(TileDeque.begin() + i);
	/// ////////////////////////////////////////////////////////
	TileDeque.push_back(*it->second);
	TileDeque.back().SetPosition(a_pos);

}

void Stage::removeTile(Grid a_pos)
{
	int i = 0;
	bool b = false;
	for (auto& it : TileDeque) {
		if (it.GetGridPosition() == a_pos) {
			b = true;
			break;
		}
		i++;
	}
	if (b)
		TileDeque.erase(TileDeque.begin() + i);
}

void Stage::Update(sf::Vector2i* a_mousePos)
{
	for (Tile& i : TileDeque) {
		i.Update(a_mousePos);
	}
}

void Stage::Render(sf::RenderTarget* a_target)
{
	for (Tile& i : TileDeque) {
		i.Render(a_target);
		//std::cout << i.sprite.getPosition().x << " " << i.sprite.getPosition().y << std::endl;
	}
}
