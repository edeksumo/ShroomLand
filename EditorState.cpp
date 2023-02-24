#include "EditorState.h"
/****************************************************/
//Private
/****************************************************/
void EditorState::mousePosUpdate(sf::Vector2f* a_mousePosOnCoords)
{
	MousePosOnGrid = Grid(a_mousePosOnCoords->x / 32, a_mousePosOnCoords->y / 32);
	//std::cout << MousePosOnGrid.x << " " << MousePosOnGrid.y << std::endl;
}
void EditorState::saveStages()
{
	ofstream saveFile;
	saveFile.open(p_dM->SaveFormat.SaveFileName);
	/// 
	/// Making save format to match with load function in Game.cpp
	/// 
	for (auto it = p_stageContainer->rbegin(); it != p_stageContainer->rend();++it) {
		saveFile << p_dM->SaveFormat.StageDefiner << " " << it->first << endl;

		for (const auto &it_01 : it->second.TileDeque) {
			saveFile << p_dM->SaveFormat.ObjectDefiner << " " << p_dM->SaveFormat.TileDefiner << " " << it_01.ID << " " << it_01.posOnGrid.x << " " << it_01.posOnGrid.y << std::endl;
		}
		//each obj type must be added here...
	}

	saveFile.close();
	std::cout  << "Stages saved" << std::endl;
}
void EditorState::buttonFunctions(const std::multimap<std::string, Button>::iterator& a_it)
{
	if (Window::CheckButton(a_it, p_dM->Lang.save)) {
		saveStages();
	}
}
void EditorState::mouseFunctions()
{
	if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold) {
		currentStage->addTile(MousePosOnGrid, 14);
	}
	if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::hold) {
		currentStage->removeTile(MousePosOnGrid);
	}
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void EditorState::Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords)
{
	updateOpenedWindowIt();
	currentStage->Update(a_mousePos);
	mousePosUpdate(a_mousePosOnCoords);
	mouseFunctions();

	std::multimap<std::string, Button>::iterator it = Windows.begin()->Buttons.begin();
	for (it = Windows.begin()->Buttons.begin(); it != Windows.begin()->Buttons.end(); ++it) {
		buttonFunctions(it);
	}
	//std::cout << "== GAMESTATE == Update Func" << std::endl;
}

void EditorState::Render(sf::RenderTarget* a_target)
{
	currentStage->Render(a_target);
	//std::cout << "== GAMESTATE == Render Func" << std::endl;
}
