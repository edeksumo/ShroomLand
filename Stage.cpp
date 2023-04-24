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

void Stage::addTile(GridCell a_pos, unsigned int a_ID)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
		
	if (TileGrid.isTileOccupied(a_pos)) {
		TileGrid.RemoveTile(a_pos);
		//std::cout << "== STAGE == addTile func: Two Tiles on one spot on the grid; old one will be eresed" << std::endl;
	}
	/// ////////////////////////////////////////////////////////
	TileGrid.AddTile(a_pos, it->second);
}

void Stage::fillDeque(GridCell a_pos, unsigned int a_ID, unsigned int a_vatiant)
{
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	TileGrid.AddTile(a_pos, it->second, a_vatiant);
}

void Stage::addBackgroundTile(GridCell a_pos, unsigned int a_ID)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	BackGroundTiles.push_back(*it->second);
	BackGroundTiles.back().SetPosition(a_pos);	//HACKED NEED FIX
}

Tile* Stage::getPrefTilePtr(int a_ID)
{
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	return it->second;
}

void Stage::Update(sf::Vector2i* a_mousePos)
{

	for (int i = 0; i < TileGrid.GetSize().x; i++) {
		for (int j = 0; j < TileGrid.GetSize().y; j++) {
			if (TileGrid.TileGridPtr[i][j] != nullptr) {
				//if (isVisible(i, p_renderTarget))
				TileGrid.TileGridPtr[i][j]->Update(a_mousePos);
			}
		}
	}
}

void Stage::Render(sf::RenderTarget* a_target)
{
	p_renderTarget = a_target;
	for (Tile& i : BackGroundTiles) {
		if(isVisible(i, a_target))
			i.Render(a_target);	
	}
	for (int i = 0; i < TileGrid.GetSize().x; i++) {
		for (int j = 0; j < TileGrid.GetSize().y; j++) {
			if (TileGrid.TileGridPtr[i][j] != nullptr) {
				//if(isVisible(*TileGrid.TileGridPtr[i][j], a_target))
				TileGrid.TileGridPtr[i][j]->Render(a_target);
			}
		}
	}
}
