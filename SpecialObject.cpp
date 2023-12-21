#include "SpecialObject.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void SpecialObject::setProperties(string a_properties)
{
	properties = a_properties;
}

string SpecialObject::getProperties()
{
	return properties;
}

void SpecialObject::OnCollisionEnter()
{
	switch (subType)
	{
	case SpecialObject::SpecialType::none:
		break;
	case SpecialObject::SpecialType::zoneChanger:
		changeState = true;
		break;
	case SpecialObject::SpecialType::sound:
		break;
	case SpecialObject::SpecialType::trigger:
		break;
	default:
		break;
	}
	std::cout << "Collision Enter SpcObj\n";
}

void SpecialObject::OnCollision()
{
	std::cout << "Collision SpcObj\n";
}

void SpecialObject::OnCollisionExit()
{
	std::cout << "Collision Exit SpcObj\n";
}

void SpecialObject::Update(sf::Vector2i* a_mousePos)
{
}
