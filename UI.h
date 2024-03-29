#pragma once

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
	sf::RenderTarget* p_rTarget;
	sf::Window* p_Window;

	sf::Sprite backgroundSprite;
	sf::Sprite upperDecorLine;
	sf::Sprite lowerDecorLine;
	sf::Sprite leftDecorLine;
	sf::Sprite rightDecorLine;
	sf::Sprite upperDecorLeftCorn;	//and for button left edge
	sf::Sprite lowerDecorLeftCorn;
	sf::Sprite upperDecorRightCorn;	//and for button right edge
	sf::Sprite lowerDecorRightCorn;

	sf::Sprite buttonDecorLines;
	sf::Sprite buttonDecorLeft;
	sf::Sprite buttonDecorRight;

	sf::Sprite sliderShapeSprite;
	sf::Sprite sliderDecorLeft;
	sf::Sprite sliderDecorRight;

	sf::Sprite imageSprite;

	sf::RectangleShape shadow;
	
	sf::RectangleShape selector;
	sf::Text text;
	sf::Vector2f size;
	sf::View view;
	sf::Vector2f relativePosition;
	sf::Vector2f position;
	sf::Vector2f textPosition;
	sf::Color textColor;

	bool hasSelector;
	bool hasText;
	bool hasSlider;
	bool hasBackground;
	bool hasImage;
	float sliderOffset;

	void keepOnPosition();
	void initText(std::string a_text,int a_size = 20);
	void initBackground();
	void renderShadow(sf::RenderTarget* a_target);
public:
	UI() {
		p_dM = nullptr;
		p_rTarget = nullptr;
		p_Window = nullptr;
		v_UIState = UI::UIState::active;
		hasSelector = false;
		hasText = false;
		hasSlider = false;
		hasBackground = false;
		hasImage = false;
		sliderOffset = 0;
	}
	
	void moveUIElement(sf::Vector2f a_pos);
	void setUIState(UI::UIState a_state);
	UI::UIState getUIState();
	virtual void Render(sf::RenderTarget* a_target) = 0;
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
};

