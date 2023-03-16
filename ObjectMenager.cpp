#include "ObjectMenager.h"
/****************************************************/
//Private
/****************************************************/
void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[8][6])
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * 32, i * 32, 32, 32), p_dM);
			//std::cout << j * 32 << " " << i * 32 << std::endl;
			if (a_objArrPtr[j][i]->ID % MAX_IDIES_FOR_TILES == 47)
				a_objArrPtr[j][i]->sprite.setTextureRect(sf::IntRect(146, 19, 16, 16));
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
	}
}
void ObjectMenager::decorPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[6][2])
{
	auto s = TilePtrContainer.rbegin()->first;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * 32, i * 32, 32, 32), p_dM);
			DecorPtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID - s, a_objArrPtr[j][i]));
			//std::cout << DecorPtrContainer.rbegin()->first << std::endl;
		}
	}
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
