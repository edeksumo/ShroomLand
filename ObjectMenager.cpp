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
			p_TilePtrCointainer->insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
	}
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
