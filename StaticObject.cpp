#include "StaticObject.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void StaticObject::OnCollisionEnter()
{
	std::cout << "Collision Enter StaObj\n";
}

void StaticObject::OnCollision()
{
	std::cout << "Collision StaObj\n";
}

void StaticObject::OnCollisionExit()
{
	std::cout << "Collision Exit StaObj\n";
}

void StaticObject::Update(sf::Vector2i* a_mousePos)
{
}
