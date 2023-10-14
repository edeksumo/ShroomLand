#include "Camera.h"

/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/


/****************************************************/
//Public
/****************************************************/
sf::View* Camera::GetView()
{
    return &view;
}

void Camera::ActiveCamera()
{
    p_window->setView(view);
}

void Camera::rotate(int a_angle, bool a_setActive)
{
    view.rotate(a_angle);
    if(a_setActive)
        ActiveCamera();
}

void Camera::move(sf::Vector2f a_dir, bool a_setActive)
{
    view.move(a_dir);
    if (a_setActive)
        ActiveCamera();
}

void Camera::updateCamera()
{
}
