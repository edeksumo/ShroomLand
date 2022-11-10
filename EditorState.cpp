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

void EditorState::Update(sf::Vector2i* a_mousePos)
{
	updateOpenedWindowIt();
	//std::cout << "== GAMESTATE == Update Func" << std::endl;
}

void EditorState::Render(sf::RenderTarget* a_target)
{
	//std::cout << "== GAMESTATE == Render Func" << std::endl;
}
