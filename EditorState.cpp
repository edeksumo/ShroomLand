#include "EditorState.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void EditorState::Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords)
{
	updateOpenedWindowIt();
	sf::Mouse::getPosition();
	MousePosOnGrid = Grid(a_mousePosOnCoords->x / 32, a_mousePosOnCoords->y / 32);
	currentStage->Update(a_mousePos);
	//std::cout << a_mousePos->x << " " << a_mousePos->y << std::endl;
	std::cout << MousePosOnGrid.x << " " << MousePosOnGrid.y << std::endl;
	//std::cout << "== GAMESTATE == Update Func" << std::endl;
}

void EditorState::Render(sf::RenderTarget* a_target)
{
	currentStage->Render(a_target);
	//std::cout << "== GAMESTATE == Render Func" << std::endl;
}
