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


Tile::groundTileType Tile::GetTileType()
{
	return tileType;
}

void Tile::changeVariant(bool a_up)
{
	if (a_up == true) {
		currentVariant++;
		if (currentVariant > nbOfVariants)
			currentVariant = 0;
	}
	else {
		currentVariant--;
		if (currentVariant == UINT_MAX)
			currentVariant = nbOfVariants;
	}
	std::cout << currentVariant << std::endl;
	sprite.setTextureRect(sf::IntRect(basicRect.left + (BASE_TEXTURE_SIZE_X * currentVariant), basicRect.top, basicRect.width, basicRect.height));
}

void Tile::Update(sf::Vector2i* a_mousePos)
{
	//if (GetTileType() == Tile::groundTileType::water) {
	//	animation();
	//}
	//std::cout << a_mousePos->x << " " << a_mousePos->y;
	//system("cls");
}
