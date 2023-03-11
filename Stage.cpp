#include "Stage.h"
/****************************************************/
//Private
/****************************************************/

unsigned int Stage::setDecor(unsigned int a_type)
{
	auto s = p_dM->seed;
	s = s - reinterpret_cast<int>(&TileDeque.back()) % 133;
	s = s % 12 + 1;
	if (a_type == static_cast<int>(Tile::groundTileType::grass)) {
		if (s <= 6)
			return s;
		else
			return s / 2;
	}

	if (a_type == static_cast<int>(Tile::groundTileType::forrest)) {
		if (s >= 4) {
			if (s <= 9) {
				return s;
			}
			return 12;
		}
		else
			return 9;
	}

	if (a_type == static_cast<int>(Tile::groundTileType::dirt)) {
		if (s >= 8)
			return s;
		else if (s == 7)
			return 6;
		else if (s >= 3)
			return s * 2;
	}

	if (a_type == static_cast<int>(Tile::groundTileType::gravel)) {
		if (s <= 6)
			return 10;
		else if (s >= 7)
			return 11;
	}

	if (a_type == static_cast<int>(Tile::groundTileType::sand)) {
		if (s <= 4)
			return 10;
		else if (s <= 8)
			return 11;
	}
	return 12;
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
bool Stage::isVisible(const Sprite& a_sprite, sf::RenderTarget* a_target)
{
	if ((a_target->getView().getCenter().x - (a_target->getView().getSize().x / 2) < a_sprite.sprite.getPosition().x + 40) &&
		(a_target->getView().getCenter().x + (a_target->getView().getSize().x / 2) > a_sprite.sprite.getPosition().x)) {
		if ((a_target->getView().getCenter().y - (a_target->getView().getSize().y / 2) < a_sprite.sprite.getPosition().y + 40) &&
			(a_target->getView().getCenter().y + (a_target->getView().getSize().y / 2) > a_sprite.sprite.getPosition().y)) {
			return true;
		}
		return false;
	}
	return false;
}

void Stage::addTile(Grid a_pos, unsigned int a_ID)
{
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	/// Keeps track of all tiles and deleting those ones that exist in one spot on the grid
	int i = 0;
	bool b = false;
	for (auto& it : TileDeque) {
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

void Stage::fillDeque(Grid a_pos, unsigned int a_ID)
{
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	TileDeque.push_back(*it->second);
	TileDeque.back().SetPosition(a_pos);
}

void Stage::addBackgroundTile(Grid a_pos, unsigned int a_ID, int a_shifted)
{
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	BackGroundTiles.push_back(*it->second);
	BackGroundTiles.back().SetPosition(a_pos, a_shifted);
	BackGroundTiles.back().setShift(static_cast<Tile::shifted>(a_shifted));
}

void Stage::addDecoration(Grid a_pos, unsigned int a_ID)
{
	auto p = reinterpret_cast<int>(&TileDeque.back()) % 11;

	auto z = p % 8;
	int a = a_ID / MAX_IDIES_FOR_TILES;
	if (a == static_cast<int>(Tile::groundTileType::water))
		return;
	std::cout << a << std::endl;
	std::multimap<int, Tile*>::iterator it_2 = p_objMenager->DecorPtrContainer.find(setDecor(a));
	if (p == 1) {
		a = a * MAX_IDIES_FOR_TILES;
		if (a_ID - 14  - a == 0) {
			DecorTiles.push_back(*it_2->second);
			DecorTiles.back().SetPosition(a_pos, z);
		}
	}

}

Tile Stage::getTileByGrid(Grid a_pos)
{
	for (auto &it : TileDeque) {
		if (it.GetGridPosition() == a_pos) {
			return it;
		}
	}
	//return Tile();
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
		if (isVisible(i, p_renderTarget))
			i.Update(a_mousePos);
	}
}

void Stage::Render(sf::RenderTarget* a_target)
{
	p_renderTarget = a_target;
	for (Tile& i : BackGroundTiles) {
		if(isVisible(i, a_target))
			i.Render(a_target);	
	}
	for (Tile& i : TileDeque) {
		if (isVisible(i, a_target))
			i.Render(a_target);
		//std::cout << i.sprite.getPosition().x << " " << i.sprite.getPosition().y << std::endl;
	}
	for (Tile& i : DecorTiles) {
		if (isVisible(i, a_target))
			i.Render(a_target);
	}
}
