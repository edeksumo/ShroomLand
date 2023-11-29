#include "Sprite.h"
unsigned int Sprite::ID_COUNTER = 0;
unsigned int Sprite::LAST_ID = 0;
/****************************************************/
//Private
/****************************************************/
void Sprite::setSpriteForAnimations()
{
	map<string, Animation>::iterator it;

	for (it = AnimMenager->AnimationMap.begin(); it != AnimMenager->AnimationMap.end(); it++)
	{
		it->second.setSpritePointer(&sprite);
	}
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

sf::Vector2f Sprite::GetPosition()
{
	return sprite.getPosition();
}

void Sprite::SetPosition(GridCell a_pos)
{
	posOnGrid = a_pos;
	sprite.setPosition(sf::Vector2f(a_pos.x * TILE_SIZE, a_pos.y * TILE_SIZE));
	if (hasHitbox) {
		hitbox.setPosition(sprite.getPosition().x + hitboxPos.x, sprite.getPosition().y + hitboxPos.y);
	}
}

void Sprite::SetPosition(sf::Vector2f a_pos)
{
	sprite.setPosition(sf::Vector2f(a_pos.x, a_pos.y));
	if (hasHitbox) {
		hitbox.setPosition(sprite.getPosition().x + hitboxPos.x, sprite.getPosition().y + hitboxPos.y);
	}
}

void Sprite::MoveSprite(sf::Vector2f a_pos)
{
	sprite.move(sf::Vector2f(a_pos.x, a_pos.y));
	if (hasHitbox) {
		hitbox.setPosition(sprite.getPosition().x + hitboxPos.x, sprite.getPosition().y + hitboxPos.y);
	}
}

void Sprite::flipSprite()
{
	auto r = sprite.getTextureRect();
	sprite.setTextureRect(sf::IntRect(r.left + r.width, r.top, -r.width, r.height));
}

GridCell Sprite::GetGridPosition()
{
	return posOnGrid;
}

GridCell Sprite::GetObjectGridPosition()
{
	return GridCell(sprite.getPosition().x / TILE_SIZE, sprite.getPosition().y / TILE_SIZE);
}

AnimationMenager* Sprite::GetAnimationMenager()
{
	return AnimMenager;
}

sf::FloatRect Sprite::getHitboxWorldRect()
{
	return hitbox.getGlobalBounds();
}

sf::FloatRect Sprite::getSpriteBoundariesPos(bool a_intoGrid)
{
	sf::Vector2f pos = sprite.getPosition();
	sf::IntRect box = sprite.getTextureRect();
	sf::FloatRect boxPos = sf::FloatRect(pos.x - box.width / 2, pos.y - box.height / 2, pos.x + box.width / 2, pos.y + box.height / 2);
	if (!a_intoGrid)
		return boxPos;
	else
		return sf::FloatRect(boxPos.left / TILE_SIZE, boxPos.top / TILE_SIZE, boxPos.width / TILE_SIZE, boxPos.height / TILE_SIZE);
}

Sprite::Verticles Sprite::getHitboxVerticles()
{
	Verticles vert;
	vert.topLeft = sf::Vector2f(getHitboxWorldRect().left, getHitboxWorldRect().top);
	//std::cout << vert.topLeft.y << " " << vert.topLeft.y << endl;
	vert.topRight = sf::Vector2f(getHitboxWorldRect().left + getHitboxWorldRect().width, getHitboxWorldRect().top);
	//std::cout << vert.topRight.y << " " << vert.topRight.y << endl;
	vert.downLeft = sf::Vector2f(getHitboxWorldRect().left, getHitboxWorldRect().top + getHitboxWorldRect().height);
	//std::cout << vert.downLeft.y << " " << vert.downLeft.y << endl;
	vert.downRight = sf::Vector2f(getHitboxWorldRect().left + getHitboxWorldRect().width, getHitboxWorldRect().top + getHitboxWorldRect().height);
	//std::cout << vert.downRight.y << " " << vert.downRight.y << endl;
	return vert;
}

void Sprite::Render(sf::RenderTarget* a_target)
{
	a_target->draw(sprite);
}

void Sprite::RenderAnimation(sf::RenderTarget* a_target)
{
	if (isAnimated) {
		AnimMenager->UpdateAnimation();
	}
}

void Sprite::RenderHitboxes(sf::RenderTarget* a_target)
{
	if (hasHitbox)
		if (p_dM->Settings.hitboxes)
			a_target->draw(hitbox);
}
