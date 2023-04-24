#include "ObjectMenager.h"
/****************************************************/
//Private
/****************************************************/
void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5])
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			auto b = DEFAULT_MASK_FOR_BACKGROUND[Tile::g_lastID] + 1;
			//std::cout << Tile::g_lastID << " " << b << std::endl;
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), true, b, 0, p_dM);
			//std::cout << Tile::g_lastID  << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
	}
}

void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5], bool a_isTilable, bool a_needBackgroundTile, unsigned int a_nbOfVariants)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), a_isTilable, a_needBackgroundTile, a_nbOfVariants, p_dM);
			//std::cout << j * 32 << " " << i * 32 << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
	}
}

void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[5][7], bool a_isTilable, bool a_needBackgroundTile, unsigned int a_nbOfVariants)
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 5; j++) {
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), a_isTilable, a_needBackgroundTile, a_nbOfVariants, p_dM);
			//std::cout << j * 32 << " " << i * 32 << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
		
	}
}

Tile* ObjectMenager::getTilePtrById(int a_ID)
{
	std::cout << "2";
	//std::multimap<int, Tile*>::iterator it = TilePtrContainer.find(a_ID);
	//std::cout << "2";
	return TilePtrContainer.find(a_ID)->second;
}

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
