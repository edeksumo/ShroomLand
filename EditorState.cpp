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
		for (const auto& it_01 : it->second.BackGroundTiles) {
			saveFile << p_dM->SaveFormat.ObjectDefiner << " " << p_dM->SaveFormat.BackTileDefiner << " " << it_01.ID << " " << it_01.posOnGrid.x << " " << it_01.posOnGrid.y << " " 
				<< static_cast<int>(it_01.shift) << std::endl;
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
	if (Window::CheckButton(a_it, "Tile_Type")) {
		currentTyleType++;
		if (currentTyleType == 0) {
			a_it->second.setText("Grass");
		}
		else if (currentTyleType == 1) {
			a_it->second.setText("Forrest");
		}
		else if (currentTyleType == 2) {
			a_it->second.setText("Dirt");
		}
		else if (currentTyleType == 3) {
			a_it->second.setText("Gravel");
		}
		else if (currentTyleType == 4) {
			a_it->second.setText("Sand");
		}
		else if (currentTyleType == 5) {
			a_it->second.setText("Water");
		}
		if (currentTyleType > 5) {
			currentTyleType = 0;
			a_it->second.setText("Grass");
		}
	}
	//if (Window::CheckButton(a_it, "Update_Tiles")) {

	//}
}

void EditorState::cursorUpdateAndRender(sf::RenderTarget* a_target)
{
	/////////////// setting up coursor size from slider /////////////
	if (OpenedWindow->getID() != 1)
		return;
	auto selectorSize = OpenedWindow->GetSliderValue("Cursor_Size");
	cursorShape.setSize(sf::Vector2f((selectorSize + 1) * 32, (selectorSize + 1) * 32));
	a_target->draw(cursorShape);
}

void EditorState::mouseFunctions()
{
	if (OpenedWindow->getID() != 1)
		return;
	if (OpenedWindow->isWindowBlockingMouse())
		return;
	auto selectorSize = OpenedWindow->GetSliderValue("Cursor_Size");
	auto tileType = currentTyleType;
	if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold) {
		//currentStage->addTile(MousePosOnGrid, 14);
		for (int i = 0; i < selectorSize + 1; i++) {
			currentStage->addTile(Grid(MousePosOnGrid.x + i, MousePosOnGrid.y + i), (tileType * MAX_IDIES_FOR_TILES) + 14);
			if (selectorSize>0) {
				currentStage->addTile(Grid(MousePosOnGrid.x, MousePosOnGrid.y + i), (tileType * MAX_IDIES_FOR_TILES) + 14);
				currentStage->addTile(Grid(MousePosOnGrid.x + i, MousePosOnGrid.y), (tileType * MAX_IDIES_FOR_TILES) + 14);
				if (selectorSize>1) {
					currentStage->addTile(Grid(MousePosOnGrid.x+i/2, MousePosOnGrid.y + i), (tileType * MAX_IDIES_FOR_TILES) + 14);
					currentStage->addTile(Grid(MousePosOnGrid.x + i, MousePosOnGrid.y+i/2), (tileType * MAX_IDIES_FOR_TILES) + 14);
				}
			}
		}
	}
		if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::hold) {
		//currentStage->removeTile(MousePosOnGrid);
		for (int i = 0; i < selectorSize + 1; i++) {
			currentStage->removeTile(Grid(MousePosOnGrid.x + i, MousePosOnGrid.y + i));
			if (selectorSize > 0) {
				currentStage->removeTile(Grid(MousePosOnGrid.x, MousePosOnGrid.y + i));
				currentStage->removeTile(Grid(MousePosOnGrid.x + i, MousePosOnGrid.y));
				if (selectorSize > 1) {
					currentStage->removeTile(Grid(MousePosOnGrid.x + i / 2, MousePosOnGrid.y + i));
					currentStage->removeTile(Grid(MousePosOnGrid.x + i, MousePosOnGrid.y + i / 2));
				}
			}
		}
	}

		if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::released) {
			updateTiles();
			setBackgroundTiles();
			std::cout << "relesd" << std::endl;
		}
		if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::released) {
			updateTiles();
			setBackgroundTiles();
			std::cout << "relesd" << std::endl;
		}
		//////////to do: add to type of tile and function to update idies of tiles (tile 14 id default)

}
void EditorState::updateTiles()
{
	currentStage->DecorTiles.clear();
	for (auto& it : currentStage->TileDeque) {
	//for (auto it = currentStage->TileDeque.rbegin(); it != currentStage->TileDeque.rend(); ++it){	
		auto sp = it.GetGridPosition();
		auto a = Grid(sp.x + 1, sp.y);
		auto b = Grid(sp.x, sp.y + 1);
		auto c = Grid(sp.x - 1, sp.y);
		auto d = Grid(sp.x, sp.y - 1);
		auto e = Grid(sp.x + 1, sp.y + 1);
		auto f = Grid(sp.x - 1, sp.y + 1);
		auto g = Grid(sp.x - 1, sp.y - 1);
		auto h = Grid(sp.x + 1, sp.y - 1);

		bool right = true;
		bool left = true;
		bool up = true;
		bool down = true;
		bool rightUp = true;
		bool rightDown = true;
		bool leftUp = true;
		bool leftDown = true;
		for (auto& it_01 : currentStage->TileDeque) {
			if (it_01.GetGridPosition() == a && it_01.GetTileType() == it.GetTileType()) {
				right = false;
			}
			if (it_01.GetGridPosition() == c && it_01.GetTileType() == it.GetTileType()) {
				left = false;
			}
			if (it_01.GetGridPosition() == b && it_01.GetTileType() == it.GetTileType()) {
				down = false;
			}
			if (it_01.GetGridPosition() == d && it_01.GetTileType() == it.GetTileType()) {
				up = false;
			}
			if (it_01.GetGridPosition() == h && it_01.GetTileType() == it.GetTileType()) {
				rightUp = false;
			}
			if (it_01.GetGridPosition() == e && it_01.GetTileType() == it.GetTileType()) {
				rightDown = false;
			}
			if (it_01.GetGridPosition() == h && it_01.GetTileType() == it.GetTileType()) {
				rightUp = false;
			}
			if (it_01.GetGridPosition() == g && it_01.GetTileType() == it.GetTileType()) {
				leftUp = false;
			}
			if (it_01.GetGridPosition() == f && it_01.GetTileType() == it.GetTileType()) {
				leftDown = false;
			}
			if (it_01.GetGridPosition() == a && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				right = false;
			}
			if (it_01.GetGridPosition() == c && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				left = false;
			}
			if (it_01.GetGridPosition() == b && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				down = false;
			}
			if (it_01.GetGridPosition() == d && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				up = false;
			}
			if (it_01.GetGridPosition() == h && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				rightUp = false;
			}
			if (it_01.GetGridPosition() == e && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				rightDown = false;
			}
			if (it_01.GetGridPosition() == h && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				rightUp = false;
			}
			if (it_01.GetGridPosition() == g && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				leftUp = false;
			}
			if (it_01.GetGridPosition() == f && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				leftDown = false;
			}
		}
		int id = 14;
		if (left)
			id = 13;
		if (right)
			id = 15;
		if (up)
			id = 6;
		if (down)
			id = 22;
		if (down && up)
			id = 2;
		if (left && right)
			id = 12;
		if (left && up)
			id = 5;
		if (left && down)
			id = 21;
		if (right && down)
			id = 23;
		if (right && up)
			id = 7;
		if (left && right && up)
			id = 4;
		if (left && right && down)
			id = 20;
		if (left && up && down)
			id = 1;
		if (right && up && down)
			id = 3;
		if (left && right && down && up)
			id = 0;

		if (right && up && leftDown && !down && !left)
			id = 9;
		if (left && down && !right && !up && rightUp)
			id = 16;
		if (right && down && leftUp && !left && !up)
			id = 17;
		if (up && left && rightDown && !right && !down)
			id = 8;

		if (leftUp && !up && !rightUp && !right && !rightDown && !down && !leftDown && !left)
			id = 37;
		if (leftDown && !up && !rightUp && !right && !rightDown && !down && !leftUp && !left)
			id = 29;
		if (rightUp && !up && !leftUp && !right && !rightDown && !down && !leftDown && !left)
			id = 36;
		if (rightDown && !up && !rightUp && !right && !leftUp && !down && !leftDown && !left)
			id = 28;


		if (leftUp && !up && rightUp && !right && rightDown && !down && leftDown && !left)
			id = 46;
		if (leftUp && !up && rightUp && !right && down && !left)
			id = 18;
		if (up && !right && rightDown && !down && leftDown && !left)
			id = 11;
		if (leftUp && !up && right && !down && leftDown && !left)
			id = 19;
		if (!up && rightUp && !right && rightDown && !down && left)
			id = 10;

		if (leftUp && !up && rightUp && !right && !rightDown && !down && !leftDown && !left)
			id = 40;
		if (!leftUp && !up && !rightUp && !right && rightDown && !down && leftDown && !left)
			id = 41;
		if (!leftUp && !up && rightUp && !right && rightDown && !down && !leftDown && !left)
			id = 42;
		if (leftUp && !up && !rightUp && !right && !rightDown && !down && leftDown && !left)
			id = 43;

		if (leftUp && !up && !rightUp && !right && down && !left)
			id = 35;
		if (!leftUp && !up && rightUp && !right && down && !left)
			id = 34;
		if (up && !right && !rightDown && !down && leftDown && !left)
			id = 27;
		if (up && !right && rightDown && !down && !leftDown && !left)
			id = 26;

		if (!leftUp && !up && right && !down && leftDown && !left)
			id = 25;
		if (!up && !rightUp && !right && rightDown && !down && left)
			id = 24;
		if (!up && rightUp && !right && !rightDown && !down && left)
			id = 32;
		if (leftUp && !up && right && !down && !leftDown && !left)
			id = 33;

		if (!leftUp && !up && rightUp && !right && rightDown && !down && leftDown && !left)
			id = 30;
		if (leftUp && !up && !rightUp && !right && rightDown && !down && leftDown && !left)
			id = 31;
		if (leftUp && !up && rightUp && !right && rightDown && !down && !leftDown && !left)
			id = 38;
		if (leftUp && !up && rightUp && !right && !rightDown && !down && leftDown && !left)
			id = 39;

		if (!leftUp && !up && rightUp && !right && !rightDown && !down && leftDown && !left)
			id = 44;
		if (leftUp && !up && !rightUp && !right && rightDown && !down && !leftDown && !left)
			id = 45;
		//if (it.ID - (static_cast<int>(it.GetTileType()) * MAX_IDIES_FOR_TILES) != id)
			currentStage->addTile(sp, (static_cast<int>(it.GetTileType()) * MAX_IDIES_FOR_TILES) + id);
			currentStage->addDecoration(sp, static_cast<int>(it.GetTileType()) * MAX_IDIES_FOR_TILES + id);
	}
}
void EditorState::setBackgroundTiles()
{
	while (!currentStage->BackGroundTiles.empty())
	{
		currentStage->BackGroundTiles.pop_front();
	}
	for (auto& it : currentStage->TileDeque) {
		auto sp = it.GetGridPosition();
		auto a = Grid(sp.x + 1, sp.y);
		auto b = Grid(sp.x, sp.y + 1);
		auto c = Grid(sp.x - 1, sp.y);
		auto d = Grid(sp.x, sp.y - 1);
		auto e = Grid(sp.x + 1, sp.y + 1);
		auto f = Grid(sp.x - 1, sp.y + 1);
		auto g = Grid(sp.x - 1, sp.y - 1);
		auto h = Grid(sp.x + 1, sp.y - 1);

		bool right = true;
		bool left = true;
		bool up = true;
		bool down = true;
		bool rightUp = true;
		bool rightDown = true;
		bool leftUp = true;
		bool leftDown = true;

		int i = it.ID - 14 - (MAX_IDIES_FOR_TILES * static_cast<int>(it.GetTileType()));
		if (i == 0)
			continue;

		for (auto& it_01 : currentStage->TileDeque) {
			if (it_01.GetGridPosition() == a && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				right = false;
			}
			if (it_01.GetGridPosition() == c && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				left = false;
			}
			if (it_01.GetGridPosition() == b && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				down = false;
			}
			if (it_01.GetGridPosition() == d && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				up = false;
			}
			if (it_01.GetGridPosition() == h && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				rightUp = false;
			}
			if (it_01.GetGridPosition() == e && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				rightDown = false;
			}
			if (it_01.GetGridPosition() == h && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				rightUp = false;
			}
			if (it_01.GetGridPosition() == g && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				leftUp = false;
			}
			if (it_01.GetGridPosition() == f && static_cast<int>(it.GetTileType()) < static_cast<int>(it_01.GetTileType())) {
				leftDown = false;
			}
		
			
			if (it.ID % MAX_IDIES_FOR_TILES == 0) {
			}

			if(left && it_01.GetGridPosition() == c && static_cast<int>(it.GetTileType()) > static_cast<int>(it_01.GetTileType()))
				currentStage->addBackgroundTile(it.GetGridPosition(), it.ID - MAX_IDIES_FOR_TILES * static_cast<int>(it.GetTileType()) + MAX_IDIES_FOR_TILES * static_cast<int>(it_01.GetTileType()), 7);
			if (right && it_01.GetGridPosition() == a && static_cast<int>(it.GetTileType()) > static_cast<int>(it_01.GetTileType()))
				currentStage->addBackgroundTile(it.GetGridPosition(), it.ID - MAX_IDIES_FOR_TILES * static_cast<int>(it.GetTileType()) + MAX_IDIES_FOR_TILES * static_cast<int>(it_01.GetTileType()), 3);
			if (up && it_01.GetGridPosition() == d && static_cast<int>(it.GetTileType()) > static_cast<int>(it_01.GetTileType()))
				currentStage->addBackgroundTile(it.GetGridPosition(), it.ID - MAX_IDIES_FOR_TILES * static_cast<int>(it.GetTileType()) + MAX_IDIES_FOR_TILES * static_cast<int>(it_01.GetTileType()), 1);
			if (down && it_01.GetGridPosition() == b && static_cast<int>(it.GetTileType()) > static_cast<int>(it_01.GetTileType()))
				currentStage->addBackgroundTile(it.GetGridPosition(), it.ID - MAX_IDIES_FOR_TILES * static_cast<int>(it.GetTileType()) + MAX_IDIES_FOR_TILES * static_cast<int>(it_01.GetTileType()), 5);
			
			if (rightUp && it_01.GetGridPosition() == h && static_cast<int>(it.GetTileType()) > static_cast<int>(it_01.GetTileType()))
				currentStage->addBackgroundTile(it.GetGridPosition(), 0 + MAX_IDIES_FOR_TILES * static_cast<int>(it_01.GetTileType()), 2);
			if (rightDown && it_01.GetGridPosition() == e && static_cast<int>(it.GetTileType()) > static_cast<int>(it_01.GetTileType()))
				currentStage->addBackgroundTile(it.GetGridPosition(), 0 + MAX_IDIES_FOR_TILES * static_cast<int>(it_01.GetTileType()), 4);
			if (leftUp && it_01.GetGridPosition() == g && static_cast<int>(it.GetTileType()) > static_cast<int>(it_01.GetTileType()))
				currentStage->addBackgroundTile(it.GetGridPosition(), 0 + MAX_IDIES_FOR_TILES * static_cast<int>(it_01.GetTileType()), 0);
			if (leftDown && it_01.GetGridPosition() == f && static_cast<int>(it.GetTileType()) > static_cast<int>(it_01.GetTileType()))
				currentStage->addBackgroundTile(it.GetGridPosition(), 0 + MAX_IDIES_FOR_TILES * static_cast<int>(it_01.GetTileType()), 6);
		}
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

	cursorShape.setPosition(MousePosOnGrid.x * 32, MousePosOnGrid.y * 32);

	std::multimap<std::string, Button>::iterator it = Windows.begin()->Buttons.begin();
	for (it = Windows.begin()->Buttons.begin(); it != Windows.begin()->Buttons.end(); ++it) {
		buttonFunctions(it);
	}
	//std::cout << "== GAMESTATE == Update Func" << std::endl;
}

void EditorState::Render(sf::RenderTarget* a_target)
{
	currentStage->Render(a_target);
	cursorUpdateAndRender(a_target);
	//std::cout << "== GAMESTATE == Render Func" << std::endl;
}
