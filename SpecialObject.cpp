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
	switch (subType)
	{
	case SpecialObject::SpecialType::none:
		break;
	case SpecialObject::SpecialType::zoneChanger:
		std::cout << "Properties set zoneChanger: " << a_properties << endl;
		break;
	case SpecialObject::SpecialType::sound:
		std::cout << "Properties set sound: " << a_properties << endl;
		break;
	case SpecialObject::SpecialType::trigger:
		std::cout << "Properties set trigger: " << a_properties << endl;
		break;
	default:
		break;
	}

}

void SpecialObject::OnCollisionEnter()
{
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
