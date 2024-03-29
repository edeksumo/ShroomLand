#include "Tile.h"

int Tile::g_lastID = 0;
int Tile::g_lastTileID = 0;
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

void Tile::setVariant(unsigned int a_variant)
{
	if (a_variant > nbOfVariants)
		return;
	currentVariant = a_variant;
	sprite.setTextureRect(sf::IntRect(basicRect.left + (BASE_TEXTURE_SIZE_X * currentVariant), basicRect.top, basicRect.width, basicRect.height));
}

bool Tile::isTileWalkable()
{
	return isWalkable;
}


void Tile::Update(sf::Vector2i* a_mousePos)
{

}