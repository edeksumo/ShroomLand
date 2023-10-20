#include "Notification.h"
/****************************************************/
//Private
/****************************************************/

void Notification::timer()
{
	if (relativePosition != sf::Vector2f(p_Window->getSize().x - notificationBoxSize.x, relativePosition.y))
		return;
	if (lastingTicks >= 0)
		lastingTicks--;		//must be devidable by 255
}

void Notification::killNotification()
{
	if (lastingTicks == 0)
		setToClose = true;
}

void Notification::enterScreen()
{
	if(relativePosition != sf::Vector2f(p_Window->getSize().x - notificationBoxSize.x, relativePosition.y))
		moveUIElement(sf::Vector2f(-6, 0));
}

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void Notification::UpdateNotification()
{
	enterScreen();
	timer();
	setAlpha(lastingTicks);
	killNotification();
}
