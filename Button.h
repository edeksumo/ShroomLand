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
	enum class GraphicalButton {
		tick,
		cross,
		left,
		right,
		up,
		down,
		plus,
		minus,
		none
	};
private:
	ButtonState lastButtonState;
	
	bool hasBorders;

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
	void setText(std::string a_text);
	void setButtonState(Button::ButtonState a_state);
	Button() {
		isSwitch = false;
		buttonState = Button::ButtonState::Free;
		lastButtonState = buttonState;
		selector.setFillColor(sf::Color(0, 0, 0, 50));
	};
	Button(sf::Vector2f m_size, sf::Vector2f m_pos, std::string m_text, sf::Color m_textColor, DataMenager* m_dM, int m_textSize = 20) {
		hasText = true;
		hasSelector = true;
		hasBackground = true;
		isSwitch = false;
		hasBorders = true;
		screenPositionRect = sf::FloatRect(backgroundSprite.getLocalBounds().left + m_pos.x, backgroundSprite.getLocalBounds().top + m_pos.y, backgroundSprite.getLocalBounds().left + m_size.x + m_pos.x,
			backgroundSprite.getLocalBounds().top + m_size.y + m_pos.y);
		relativePosition = m_pos;
		textColor = m_textColor;
		size = m_size;
		p_dM = m_dM;
		textPosition = sf::Vector2f(m_size.x / 2, m_size.y / 2);
		v_UIState = UI::UIState::active;

		backgroundSprite.setTexture(p_dM->buttonBackgroundTxt);
		//backgroundSprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		//upperDecorLine.setTexture(p_dM->buttonDecorLineTxt);
		//upperDecorLine.setTextureRect(sf::IntRect(0, 0, size.x - (p_dM->buttonDecorCornerTxt.getSize().x * 2), p_dM->buttonDecorLineTxt.getSize().y));
		//lowerDecorLine.setTexture(p_dM->buttonDecorLineTxt);
		//lowerDecorLine.setTextureRect(sf::IntRect(0, 0, size.x - (p_dM->buttonDecorCornerTxt.getSize().x * 2), p_dM->buttonDecorLineTxt.getSize().y));
		//lowerDecorLine.rotate(180);
		//leftDecorLine.setTexture(p_dM->buttonDecorLineTxt);
		//leftDecorLine.setTextureRect(sf::IntRect(0, 0, size.y - (p_dM->buttonDecorCornerTxt.getSize().x * 2), p_dM->buttonDecorLineTxt.getSize().y));
		//leftDecorLine.rotate(270);
		//rightDecorLine.setTexture(p_dM->buttonDecorLineTxt);
		//rightDecorLine.setTextureRect(sf::IntRect(0, 0, size.y - (p_dM->buttonDecorCornerTxt.getSize().x * 2), p_dM->buttonDecorLineTxt.getSize().y));
		//rightDecorLine.rotate(90);
		upperDecorLeftCorn.setTexture(p_dM->buttonDecorUpLeftCornerTxt);
		lowerDecorLeftCorn.setTexture(p_dM->buttonDecorDownLeftCornerTxt);
		//lowerDecorLeftCorn.setRotation(270);
		upperDecorRightCorn.setTexture(p_dM->buttonDecorUpRightCornerTxt);
		//upperDecorRightCorn.setRotation(90);
		lowerDecorRightCorn.setTexture(p_dM->buttonDecorDownRightCornerTxt);
		//lowerDecorRightCorn.setRotation(180);

		backgroundSprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));

		upperDecorLine.setTexture(p_dM->buttonDecorUpLineTxt);
		upperDecorLine.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x) - (p_dM->buttonDecorDownLeftCornerTxt.getSize().x * 2) + 4, p_dM->buttonDecorUpLineTxt.getSize().y));

		lowerDecorLine.setTexture(p_dM->buttonDecorDownLineTxt);
		lowerDecorLine.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x) - (p_dM->buttonDecorDownLeftCornerTxt.getSize().x * 2) + 4, p_dM->buttonDecorDownLineTxt.getSize().y));
		//lowerDecorLine.rotate(180);
		leftDecorLine.setTexture(p_dM->buttonDecorLeftLineTxt);
		leftDecorLine.setTextureRect(sf::IntRect(0, 0, p_dM->buttonDecorLeftLineTxt.getSize().x, static_cast<int>(size.y) - (p_dM->buttonDecorDownLeftCornerTxt.getSize().y * 2) + 4));
		//leftDecorLine.rotate(270);
		rightDecorLine.setTexture(p_dM->buttonDecorRightLineTxt);
		rightDecorLine.setTextureRect(sf::IntRect(0, 0, p_dM->buttonDecorRightLineTxt.getSize().x, static_cast<int>(size.y) - (p_dM->buttonDecorDownLeftCornerTxt.getSize().y * 2) + 4));
		//rightDecorLine.rotate(90);

		state = SwitchState::off;	

		text.setFillColor(textColor);
		buttonState = ButtonState::Free;
		lastButtonState = buttonState;
		initBackground();
		initText(m_text, m_textSize);
		selector.setFillColor(sf::Color(0, 0, 0, 50));
		onEnter();
	};
	Button(GraphicalButton m_visual ,sf::Vector2f m_pos, DataMenager* m_dM) : Button(sf::Vector2f(32, 32), m_pos, "", sf::Color::Black, m_dM) {
		hasBorders = false;
		if (m_visual == Button::GraphicalButton::tick)
			backgroundSprite.setTexture(m_dM->buttonTickTxt);
		if (m_visual == Button::GraphicalButton::cross)
			backgroundSprite.setTexture(m_dM->buttonCrossTxt);
		if (m_visual == Button::GraphicalButton::down)
			backgroundSprite.setTexture(m_dM->buttonDownTxt);
		if (m_visual == Button::GraphicalButton::up)
			backgroundSprite.setTexture(m_dM->buttonUpTxt);
		if (m_visual == Button::GraphicalButton::left)
			backgroundSprite.setTexture(m_dM->buttonLeftTxt);
		if (m_visual == Button::GraphicalButton::right)
			backgroundSprite.setTexture(m_dM->buttonRightTxt);
		if (m_visual == Button::GraphicalButton::plus)
			backgroundSprite.setTexture(m_dM->buttonPlusTxt);
		if (m_visual == Button::GraphicalButton::minus)
			backgroundSprite.setTexture(m_dM->buttonMinusTxt);
		if (m_visual == Button::GraphicalButton::none)
			backgroundSprite.setTexture(m_dM->buttonNoneTxt);
	};

	~Button() {
		onQuit();
	};
	
	void Update(sf::Vector2i* a_mousePos);
	void Render(sf::RenderTarget* a_target);
};

