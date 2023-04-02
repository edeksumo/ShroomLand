#include "Tile.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/


/****************************************************/
//Public
/****************************************************/
void Tile::SetTileType(groundTileType a_type)
{
}


Tile::groundTileType Tile::GetTileType()
{
	return tileType;
}

void Tile::Update(sf::Vector2i* a_mousePos)
{
	//if (GetTileType() == Tile::groundTileType::water) {
	//	animation();
	//}
	//std::cout << a_mousePos->x << " " << a_mousePos->y;
	//system("cls");
}
