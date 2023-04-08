#include "UI.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/
void UI::keepOnPosition()
{
	position = p_rTarget->mapPixelToCoords(sf::Vector2i(relativePosition));
	shadow.setPosition(backgroundSprite.getPosition());
	if (hasBackground) {
		backgroundSprite.setPosition(position);
		upperDecorLine.setPosition(position.x + upperDecorLeftCorn.getTextureRect().width /*p_dM->windowsDecorCornerTxt.getSize().x*/, position.y);
		lowerDecorLine.setPosition(position.x + lowerDecorLine.getTextureRect().width + upperDecorLeftCorn.getTextureRect().width/*p_dM->windowsDecorCornerTxt.getSize().x*/, position.y + backgroundSprite.getTextureRect().height);
		leftDecorLine.setPosition(position.x, position.y + leftDecorLine.getTextureRect().width + upperDecorLeftCorn.getTextureRect().height);
		rightDecorLine.setPosition(position.x + (backgroundSprite.getTextureRect().width), position.y + upperDecorLeftCorn.getTextureRect().height);
		upperDecorLeftCorn.setPosition(position);
		lowerDecorLeftCorn.setPosition(position.x, position.y + backgroundSprite.getTextureRect().height);
		upperDecorRightCorn.setPosition(position.x + (backgroundSprite.getTextureRect().width), position.y);
		lowerDecorRightCorn.setPosition(position.x + (backgroundSprite.getTextureRect().width), position.y + backgroundSprite.getTextureRect().height);
	}
	if (hasText)
		text.setPosition(textPosition + position);
	if(hasSelector)
		selector.setPosition(backgroundSprite.getPosition());
	if (hasSlider) {
		sliderShapeSprite.setPosition(sf::Vector2f(backgroundSprite.getPosition().x + sliderOffset, backgroundSprite.getPosition().y + 5));
		sliderDecorLeft.setPosition(position.x - (sliderDecorLeft.getTextureRect().width), position.y + 5);
		SliderDecorRight.setPosition(position.x + backgroundSprite.getTextureRect().width + SliderDecorRight.getTextureRect().width, position.y + SliderDecorRight.getTextureRect().width + 8);
		shadow.setPosition(sliderShapeSprite.getPosition());
	}
	if (hasImage) {
		imageSprite.setPosition(position);
	}
}

void UI::initText(std::string a_text)
{
	text.setFont(p_dM->buttonFont);
	text.setString(a_text);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	auto textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height);
	text.setPosition(position.x + textPosition.x, position.y + textPosition.y);
	text.setFillColor(textColor);
}

void UI::initBackground()
{
	shadow.setFillColor(sf::Color(0, 0, 0, 150));
	shadow.setSize(size);
	shadow.setPosition(position);
	if (hasBackground){

	}
	if (hasSelector) {
		selector.setSize(size);
		selector.setPosition(position);
	}
	if (hasSlider) {
		sliderShapeSprite.setPosition(sf::Vector2f(position.x + 5, position.y + 5));
	}
}

void UI::renderShadow(sf::RenderTarget* a_target)
{
	if (v_UIState == UI::UIState::inActive)
		a_target->draw(shadow);
}
/****************************************************/
//Public
/****************************************************/
void UI::setUIState(UI::UIState a_state)
{
	v_UIState = a_state;
}

UI::UIState UI::getUIState()
{
	return v_UIState;
}