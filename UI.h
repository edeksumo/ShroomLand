#pragma once

#include <iostream>
#include <map>
#include <stack>
#include <SFML/Graphics.hpp>
#include "DataMenager.h"
#include "Keyboard.h"

class UI
{
public:
	enum class UIState {
		active,
		inActive
	};
private:
protected:
	UIState v_UIState;
	DataMenager* p_dM;
	sf::RectangleShape background;
	sf::RectangleShape shadow;
	sf::RectangleShape selector;
	sf::RectangleShape sliderShape;
	sf::Text text;
	sf::Vector2f size;
	sf::View view;
	sf::Vector2f relativePosition;
	sf::Vector2f position;
	sf::Vector2f textPosition;
	sf::Color textColor;
	sf::Color color;
	sf::Color secondColor;
	bool hasSelector;
	bool hasText;
	bool hasSlider;
	bool hasBackground;
	float sliderOffset;

	void keepOnPosition();
	void initText(std::string a_text);
	void initBackground();
	void renderShadow(sf::RenderTarget* a_target);
public:
	UI() {
		p_dM = nullptr;
		v_UIState = UI::UIState::active;
		hasSelector = false;
		hasText = false;
		hasSlider = false;
		hasBackground = false;
		sliderOffset = 0;
	}
	
	void setUIState(UI::UIState a_state);
	UI::UIState getUIState();
	void setColor(sf::Color a_color);
	sf::Color getColor();
	virtual void Render(sf::RenderTarget* a_target) = 0;
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
};

