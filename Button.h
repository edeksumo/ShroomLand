#pragma once
#include "UI.h"

class Button : public UI
{
public:
	enum class ButtonState {
		Free,
		Selected,
		Pressed,
		Hold
	};
	enum class SwitchState {
		off,
		on
	};
private:
	ButtonState lastButtonState;
	
	bool onEnter();
	bool onQuit();
protected:
	ButtonState buttonState;
	sf::FloatRect screenPositionRect;
	bool isSwitch;

	SwitchState state;	//only for switches
	bool pressed(sf::Vector2i* a_mousePos);
	void setTransparency();
	void drawSelector(sf::RenderTarget* a_target);
	bool mouseEnter(sf::Vector2i* a_mousePos);
	bool mouseQuit(sf::Vector2i* a_mousePos);
public:
	bool isPressed();
	
	Button() {
		isSwitch = false;
		buttonState = ButtonState::Free;
		lastButtonState = buttonState;
		selector.setFillColor(sf::Color(0, 0, 0, 50));
	};
	Button(sf::Vector2f m_size, sf::Vector2f m_pos, sf::Color m_color, std::string m_text, sf::Color m_textColor, DataMenager* m_dM) {
		hasText = true;
		hasSelector = true;
		hasBackground = true;
		isSwitch = false;
		screenPositionRect = sf::FloatRect(backgroundSprite.getLocalBounds().left + m_pos.x, backgroundSprite.getLocalBounds().top + m_pos.y, backgroundSprite.getLocalBounds().left + m_size.x + m_pos.x,
			backgroundSprite.getLocalBounds().top + m_size.y + m_pos.y);
		relativePosition = m_pos;
		color = m_color;
		textColor = m_textColor;
		size = m_size;
		p_dM = m_dM;
		textPosition = sf::Vector2f(m_size.x / 2, m_size.y / 2);
		v_UIState = UI::UIState::active;
		position = sf::Vector2f((relativePosition.x + (view.getCenter().x - (view.getSize().x / 2))), (relativePosition.y + (view.getCenter().y - (view.getSize().y / 2))));
		background.setFillColor(color);

		backgroundSprite.setTexture(p_dM->buttonBackgroundTxt);
		backgroundSprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		upperDecorLine.setTexture(p_dM->buttonDecorLineTxt);
		upperDecorLine.setTextureRect(sf::IntRect(0, 0, size.x - (p_dM->buttonDecorCornerTxt.getSize().x * 2), p_dM->buttonDecorLineTxt.getSize().y));
		lowerDecorLine.setTexture(p_dM->buttonDecorLineTxt);
		lowerDecorLine.setTextureRect(sf::IntRect(0, 0, size.x - (p_dM->buttonDecorCornerTxt.getSize().x * 2), p_dM->buttonDecorLineTxt.getSize().y));
		lowerDecorLine.rotate(180);
		leftDecorLine.setTexture(p_dM->buttonDecorLineTxt);
		leftDecorLine.setTextureRect(sf::IntRect(0, 0, size.y - (p_dM->buttonDecorCornerTxt.getSize().x * 2), p_dM->buttonDecorLineTxt.getSize().y));
		leftDecorLine.rotate(270);
		rightDecorLine.setTexture(p_dM->buttonDecorLineTxt);
		rightDecorLine.setTextureRect(sf::IntRect(0, 0, size.y - (p_dM->buttonDecorCornerTxt.getSize().x * 2), p_dM->buttonDecorLineTxt.getSize().y));
		rightDecorLine.rotate(90);
		upperDecorLeftCorn.setTexture(p_dM->buttonDecorCornerTxt);
		lowerDecorLeftCorn.setTexture(p_dM->buttonDecorCornerTxt);
		lowerDecorLeftCorn.setRotation(270);
		upperDecorRightCorn.setTexture(p_dM->buttonDecorCornerTxt);
		upperDecorRightCorn.setRotation(90);
		lowerDecorRightCorn.setTexture(p_dM->buttonDecorCornerTxt);
		lowerDecorRightCorn.setRotation(180);

		state = SwitchState::off;	

		text.setFillColor(textColor);
		buttonState = ButtonState::Free;
		lastButtonState = buttonState;
		initBackground();
		initText(m_text);
		selector.setFillColor(sf::Color(0, 0, 0, 50));
		onEnter();
	};
	~Button() {
		onQuit();
	};
	
	void Update(sf::Vector2i* a_mousePos);
	void Render(sf::RenderTarget* a_target);
};

