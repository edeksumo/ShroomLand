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
	//shadow.setPosition(backgroundSprite.getPosition());
	shadow.setPosition(p_rTarget->mapPixelToCoords(sf::Vector2i(0, 0)));
	if (hasBackground) {
		backgroundSprite.setPosition(position);
		upperDecorLine.setPosition(position.x - 2 + upperDecorLeftCorn.getTextureRect().width, position.y - 2);
		lowerDecorLine.setPosition(position.x + upperDecorLeftCorn.getTextureRect().width - 2, position.y + backgroundSprite.getTextureRect().height - lowerDecorLine.getTextureRect().height + 2);
		leftDecorLine.setPosition(position.x - 2, position.y + upperDecorLeftCorn.getTextureRect().height - 2);
		rightDecorLine.setPosition(position.x + backgroundSprite.getTextureRect().width - rightDecorLine.getTextureRect().width + 3, position.y + upperDecorLeftCorn.getTextureRect().height - 2);
		
		upperDecorLeftCorn.setPosition(position.x - 2, position.y - 2);
		lowerDecorLeftCorn.setPosition(position.x - 2, position.y + backgroundSprite.getTextureRect().height - lowerDecorLeftCorn.getTextureRect().height + 2);
		upperDecorRightCorn.setPosition(position.x + (backgroundSprite.getTextureRect().width) - upperDecorRightCorn.getTextureRect().width + 2, position.y - 2);
		lowerDecorRightCorn.setPosition(position.x + (backgroundSprite.getTextureRect().width) - lowerDecorRightCorn.getTextureRect().width + 2, position.y + backgroundSprite.getTextureRect().height - lowerDecorRightCorn.getTextureRect().height + 2);
	}
	if (hasText)
		text.setPosition(textPosition + position);
	if(hasSelector)
		selector.setPosition(backgroundSprite.getPosition());
	if (hasSlider) {

		sliderShapeSprite.setPosition(sf::Vector2f(backgroundSprite.getPosition().x + sliderOffset, backgroundSprite.getPosition().y + 5));
		sliderDecorLeft.setPosition(position.x - sliderDecorLeft.getTextureRect().width, position.y + ((sliderShapeSprite.getTextureRect().height - backgroundSprite.getTextureRect().height) / 1.3f) - 1);
		sliderDecorRight.setPosition(position.x + backgroundSprite.getTextureRect().width, position.y + ((sliderShapeSprite.getTextureRect().height - backgroundSprite.getTextureRect().height) / 1.3f) - 1);
		shadow.setPosition(sliderShapeSprite.getPosition());
		backgroundSprite.setPosition(position.x, position.y + ((sliderShapeSprite.getTextureRect().height - backgroundSprite.getTextureRect().height) / 1.3f));
	}
	if (hasImage) {
		imageSprite.setPosition(position);
	}
}

void UI::initText(std::string a_text, int a_size)
{
	text.setFont(p_dM->buttonFont);
	text.setString(a_text);
	text.setCharacterSize(a_size);
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
	if (v_UIState == UI::UIState::inActive) {
		shadow.setSize(sf::Vector2f(a_target->getSize().x, a_target->getSize().y));
		a_target->draw(shadow);
	}
}
/****************************************************/
//Public
/****************************************************/
void UI::moveUIElement(sf::Vector2f a_pos)
{
	relativePosition = sf::Vector2f(relativePosition.x + a_pos.x, relativePosition.y + a_pos.y);
}

void UI::setUIState(UI::UIState a_state)
{
	v_UIState = a_state;
}

UI::UIState UI::getUIState()
{
	return v_UIState;
}