#include "Player.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void Player::OnCollisionEnter()
{
	std::cout << "Collision Enter PlaObj\n";
}

void Player::OnCollision()
{
	std::cout << "Collision PlaObj\n";
}

void Player::OnCollisionExit()
{
	std::cout << "Collision Exit PlaObj\n";
}

void Player::Update(sf::Vector2i* a_mousePos)
{
	stateDetector();
	detectFacing();
	resetLastPosition();
	animationControler();
}
