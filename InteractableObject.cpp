#include "InteractableObject.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void InteractableObject::OnCollisionEnter()
{
	std::cout << "Collision Enter IntObj\n";
}

void InteractableObject::OnCollision()
{
	std::cout << "Collision IntObj\n";
}

void InteractableObject::OnCollisionExit()
{
	std::cout << "Collision Exit IntObj\n";
}

void InteractableObject::Update(sf::Vector2i* a_mousePos)
{
}
