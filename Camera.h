#pragma once
#include <SFML/Graphics.hpp>
#include "Keyboard.h"
class Camera
{
private:
	sf::View view;
	sf::RenderWindow* p_window;
protected:
	
public:
	Camera() {
		p_window = nullptr;
	}
	Camera(sf::RenderWindow* m_window, sf::Vector2f m_size) {
		p_window = m_window;
		view.setSize(m_size.x, m_size.y);
	}
	sf::View* GetView();
	void ActiveCamera();
	void rotate(int a_angle, bool a_setActive = true);
	void move(sf::Vector2f a_dir, bool a_setActive = true);
	void setCenter(sf::Vector2f a_pos, bool a_setActive = true);
	sf::Vector2f getCenter();
	void updateCamera();
};

