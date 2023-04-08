#include "EditorState.h"
/****************************************************/
//Private
/****************************************************/
void EditorState::mousePosUpdate(sf::Vector2f* a_mousePosOnCoords)
{
	MousePosOnGrid = GridCell(a_mousePosOnCoords->x / TILE_SIZE, a_mousePosOnCoords->y / TILE_SIZE);
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

		for (const auto &it_01 : it->second.TileGrid.TileDeque) {
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
	if (Window::CheckButton(a_it, "Editor_Func")) {
		editorFunction(a_it);
	}
	//if (Window::CheckButton(a_it, "Update_Tiles")) {

	//}
}

void EditorState::placeTiles()
{
	auto selectorSize = OpenedWindow->GetSliderValue("Cursor_Size") + 1;
	auto tileType = currentTyleType;

	if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold) {
		//currentStage->addTile(MousePosOnGrid, 14);
		for (int i = 0; i < selectorSize + 1; i++) {
			currentStage->addTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y + i), (tileType * MAX_IDIES_FOR_TILES) + DEFAULT_BASE_TILE);
			if (selectorSize > 0) {
				currentStage->addTile(GridCell(MousePosOnGrid.x, MousePosOnGrid.y + i), (tileType * MAX_IDIES_FOR_TILES) + DEFAULT_BASE_TILE);
				currentStage->addTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y), (tileType * MAX_IDIES_FOR_TILES) + DEFAULT_BASE_TILE);
				if (selectorSize > 1) {
					currentStage->addTile(GridCell(MousePosOnGrid.x + i / 2, MousePosOnGrid.y + i), (tileType * MAX_IDIES_FOR_TILES) + DEFAULT_BASE_TILE);
					currentStage->addTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y + i / 2), (tileType * MAX_IDIES_FOR_TILES) + DEFAULT_BASE_TILE);
					if (selectorSize > 2) {
						currentStage->addTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y + 3), (tileType * MAX_IDIES_FOR_TILES) + DEFAULT_BASE_TILE);
						currentStage->addTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y + 2), (tileType * MAX_IDIES_FOR_TILES) + DEFAULT_BASE_TILE);
					}
				}
			}
		}
	}
	if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::hold) {
		//currentStage->removeTile(MousePosOnGrid);
		for (int i = 0; i < selectorSize + 1; i++) {
			currentStage->TileGrid.RemoveTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y + i));
			if (selectorSize > 0) {
				currentStage->TileGrid.RemoveTile(GridCell(MousePosOnGrid.x, MousePosOnGrid.y + i));
				currentStage->TileGrid.RemoveTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y));
				if (selectorSize > 1) {
					currentStage->TileGrid.RemoveTile(GridCell(MousePosOnGrid.x + i / 2, MousePosOnGrid.y + i));
					currentStage->TileGrid.RemoveTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y + i / 2));
				}
			}
		}
	}

	if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::released) {
		updateTiles();
		updateTiles();
		setBackgroundTiles();
	}
	if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::released) {
		updateTiles();
		updateTiles();
		setBackgroundTiles();
	}
}

void EditorState::changeVariants()
{
	if (selectedTile == nullptr)
		return;
	if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::pressed) {
		selectedTile->changeVariant(true);
	}
	if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::pressed) {
		selectedTile->changeVariant(false);
	}
}

void EditorState::placeObjects()
{
}

void EditorState::wheelFunctions()
{
	if (currentFunction == EditorState::EditorFunction::placeTile) {
		if (Keyboard::mouseWheel() == Keyboard::MouseWheel::up) {
			currentTyleType--;
			if (currentTyleType < 0) {
				currentTyleType = MAX_TILE_TYPES;
			}
			//updateText();
		}
		else if (Keyboard::mouseWheel() == Keyboard::MouseWheel::down) {
			currentTyleType++;
			if (currentTyleType > MAX_TILE_TYPES) {
				currentTyleType = 0;
			}

		}
	}
	updateText();
}

void EditorState::updateText()
{
	if(currentFunction == EditorState::EditorFunction::placeTile)
		OpenedWindow->SetElementValue("Current_Obj_Name", p_dM->tileNames[currentTyleType]);
	else if(currentFunction == EditorState::EditorFunction::changeVariant)
		OpenedWindow->SetElementValue("Current_Obj_Name", " ");
}

void EditorState::cursorUpdateAndRender(sf::RenderTarget* a_target)
{
	if (OpenedWindow->getID() != 1)
		return;
	cursorShape.setPosition(MousePosOnGrid.x * TILE_SIZE, MousePosOnGrid.y * TILE_SIZE);
	if (currentFunction == EditorState::EditorFunction::placeTile) {
		auto selectorSize = OpenedWindow->GetSliderValue("Cursor_Size");
		cursorShape.setSize(sf::Vector2f((selectorSize + 2) * TILE_SIZE, (selectorSize + 2) * TILE_SIZE));
		Tile* p = currentStage->getPrefTilePtr(MAX_IDIES_FOR_TILES * currentTyleType + DEFAULT_BASE_TILE);
		activeSprite = p->sprite;
		OpenedWindow->SetElementValue("Obj_Image", &activeSprite);
		a_target->draw(cursorShape);
	}
	if (currentFunction == EditorState::EditorFunction::changeVariant) {
		cursorShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		selectedTile = currentStage->TileGrid.GetTilePtr(MousePosOnGrid);
		if (selectedTile != nullptr) {
			activeSprite = selectedTile->sprite;
		}
		else {
			activeSprite.setTexture(p_dM->emptyTxt);
		}
		OpenedWindow->SetElementValue("Obj_Image", &activeSprite);
		a_target->draw(cursorShape);
	}
}

void EditorState::mouseFunctions()
{
	if (OpenedWindow->getID() != 1)
		return;
	if (OpenedWindow->isWindowBlockingMouse())
		return;
	if (currentFunction == EditorState::EditorFunction::placeTile) {
		placeTiles();
	}
	else if (currentFunction == EditorState::EditorFunction::changeVariant) {
		changeVariants();
	}
	else if (currentFunction == EditorState::EditorFunction::placeObject) {
		placeObjects();
	}

}
void EditorState::updateTiles()
{
	currentStage->DecorTiles.clear();
	auto RNG = p_dM->seed + 10000;
	auto TileRNG = RNG;

	for (auto& it : currentStage->TileGrid.TileDeque) {
		if (!it.isTilable)
			continue;
		//if (it.currentVariant != 0)
		//	continue;
		auto sp = it.GetGridPosition();
		auto a = GridCell(sp.x + 1, sp.y);		//right
		auto b = GridCell(sp.x, sp.y + 1);		//down
		auto c = GridCell(sp.x - 1, sp.y);		//left
		auto d = GridCell(sp.x, sp.y - 1);		//up
		auto e = GridCell(sp.x + 1, sp.y + 1);	//right Down
		auto f = GridCell(sp.x - 1, sp.y + 1);	//left Down
		auto g = GridCell(sp.x - 1, sp.y - 1);	//left Up
		auto h = GridCell(sp.x + 1, sp.y - 1);	//right Up			cgd	dha aeb bfc

		bool right = true;
		bool left = true;
		bool up = true;
		bool down = true;
		bool rightUp = true;
		bool rightDown = true;
		bool leftUp = true;
		bool leftDown = true;

		auto checker = false;

		if (currentStage->TileGrid.GetTilePtr(c) != nullptr && currentStage->TileGrid.GetTilePtr(g) != nullptr && currentStage->TileGrid.GetTilePtr(d) != nullptr) {
			checker = true;
		}
		if (currentStage->TileGrid.GetTilePtr(d) != nullptr && currentStage->TileGrid.GetTilePtr(h) != nullptr && currentStage->TileGrid.GetTilePtr(a) != nullptr) {
			checker = true;
		}
		if (currentStage->TileGrid.GetTilePtr(a) != nullptr && currentStage->TileGrid.GetTilePtr(e) != nullptr && currentStage->TileGrid.GetTilePtr(b) != nullptr) {
			checker = true;
		}
		if (currentStage->TileGrid.GetTilePtr(b) != nullptr && currentStage->TileGrid.GetTilePtr(f) != nullptr && currentStage->TileGrid.GetTilePtr(c) != nullptr) {
			checker = true;
		}
		if (!checker) {
			currentStage->TileGrid.TileGridPtr[sp.x][sp.y] = nullptr;
			continue;
		}

		if (currentStage->TileGrid.isTileOccupied(a) && currentStage->TileGrid.GetTilePtr(a)->GetTileType() == it.GetTileType()) {
			right = false;
		}
		if (currentStage->TileGrid.isTileOccupied(c) && currentStage->TileGrid.GetTilePtr(c)->GetTileType() == it.GetTileType()) {
			left = false;
		}
		if (currentStage->TileGrid.isTileOccupied(b) && currentStage->TileGrid.GetTilePtr(b)->GetTileType() == it.GetTileType()) {
			down = false;
		}
		if (currentStage->TileGrid.isTileOccupied(d) && currentStage->TileGrid.GetTilePtr(d)->GetTileType() == it.GetTileType()) {
			up = false;
		}
		if (currentStage->TileGrid.isTileOccupied(e) && currentStage->TileGrid.GetTilePtr(e)->GetTileType() == it.GetTileType()) {
			rightDown = false;
		}
		if (currentStage->TileGrid.isTileOccupied(h) && currentStage->TileGrid.GetTilePtr(h)->GetTileType() == it.GetTileType()) {
			rightUp = false;
		}
		if (currentStage->TileGrid.isTileOccupied(g) && currentStage->TileGrid.GetTilePtr(g)->GetTileType() == it.GetTileType()) {
			leftUp = false;
		}
		if (currentStage->TileGrid.isTileOccupied(f) && currentStage->TileGrid.GetTilePtr(f)->GetTileType() == it.GetTileType()) {
			leftDown = false;
		}

		if (currentStage->TileGrid.isTileOccupied(a) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(a)->GetTileType())) {
			right = false;
		}
		if (currentStage->TileGrid.isTileOccupied(c) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(c)->GetTileType())) {
			left = false;
		}
		if (currentStage->TileGrid.isTileOccupied(b) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(b)->GetTileType())) {
			down = false;
		}
		if (currentStage->TileGrid.isTileOccupied(d) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(d)->GetTileType())) {
			up = false;
		}
		if (currentStage->TileGrid.isTileOccupied(e) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(e)->GetTileType())) {
			rightDown = false;
		}
		if (currentStage->TileGrid.isTileOccupied(h) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(h)->GetTileType())) {
			rightUp = false;
		}
		if (currentStage->TileGrid.isTileOccupied(g) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(g)->GetTileType())) {
			leftUp = false;
		}
		if (currentStage->TileGrid.isTileOccupied(f) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(f)->GetTileType())) {
			leftDown = false;
		}

		//////////////////////////////////////////////
		/// seting up ID
		//////////////////////////////////////////////
		int id = DEFAULT_BASE_TILE;								//defaut all sides taken

		if (left && !up && !rightUp && !right && !rightDown && !down) {		//left side free
			if (TileRNG % 3 == 1)
				id = 11;
			else if (TileRNG % 3 > 1)
				id = 22;
			else
				id = 33;
			//int a[3] = { 30, 40, 50 };
			//id = p_dM->RNG(TileRNG, a);
			TileRNG--;
		}
		if (!left && !leftUp && !up && right && !down && !leftDown) {			//right side free
			if (TileRNG % 3 == 1)
				id = 15;
			else if (TileRNG % 3 > 1)
				id = 26;
			else
				id = 37;
			TileRNG--;
		}
		if (!left && up && !right && !rightDown && !down && !leftDown) {		//up free
			if (TileRNG % 3 == 1)
				id = 1;
			else if (TileRNG % 3 > 1)
				id = 2;
			else
				id = 3;
			TileRNG--;
		}
		if (!left && !leftUp && !up && !rightUp && !right && down) {			//down free
			if (TileRNG % 3 == 1)
				id = 45;
			else if (TileRNG % 3 > 1)
				id = 46;
			else
				id = 47;
			TileRNG--;
		}

		if (left && up)
			id = 0;
		if (right && up)
			id = 4;
		if (left && down)
			id = 44;
		if (right && down)
			id = 48;

		if (!left && leftUp && !up && !rightUp && !right && !rightDown && !down && !leftDown)
			id = 12;
		if (!left && !leftUp && !up && rightUp && !right && !rightDown && !down && !leftDown)
			id = 13;
		if (!left && !leftUp && !up && !rightUp && !right && !rightDown && !down && leftDown)
			id = 23;
		if (!left && !leftUp && !up && !rightUp && !right && rightDown && !down && !leftDown)
			id = 24;

		if (!left && leftUp && !up && !rightUp && !right && rightDown && !down && !leftDown)
			id = 14;
		if (!left && !leftUp && !up && rightUp && !right && !rightDown && !down && leftDown)
			id = 36;

		if (!left && leftUp && !up && !rightUp && right && rightDown && !down && !leftDown)
			id = 4;
		if (left && leftUp && !up && !rightUp && !right && rightDown && !down && !leftDown)
			id = 44;
		if (left && !leftUp && !up && rightUp && !right && !rightDown && !down && leftDown)
			id = 0;
		if (!left && !leftUp && !up && rightUp && right && !rightDown && !down && leftDown)
			id = 48;

		if (!left && !leftUp && !up && rightUp && !right && !rightDown && down && leftDown)
			id = 48;
		if (!left && !leftUp && up && rightUp && !right && !rightDown && !down && leftDown)
			id = 0;
		if (!left && leftUp && up && !rightUp && !right && rightDown && !down && !leftDown)
			id = 4;
		if (!left && leftUp && !up && !rightUp && !right && rightDown && down && !leftDown)
			id = 44;

		if (id == DEFAULT_BASE_TILE) {
			int arr[] = { 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34 ,34, 34, 34, 34, 34 ,34 ,34, 34, 34, 34, 34, 16, 17, 18, 19, 20, 21, 27, 28, 29, 30, 31, 32, 38, 39, 40, 41, 42, 43, 49, 50, 51, 52, 53, 54 };
			id = p_dM->RNG(TileRNG--, arr, sizeof(arr) / sizeof(int));
		}
			
		//////////////////////////////////////////////
		/// seting up type
		//////////////////////////////////////////////

		right = false;
		left = false;
		up = false;
		down = false;
		rightUp = false;
		rightDown = false;
		leftUp = false;
		leftDown = false;
		auto type = currentStage->getTileByGrid(sp).GetTileType();
		bool keepType = false;

		if (currentStage->TileGrid.isTileOccupied(a) && static_cast<int>(it.GetTileType()) == static_cast<int>(currentStage->TileGrid.GetTilePtr(a)->GetTileType())) {
			right = true;
		}
		if (currentStage->TileGrid.isTileOccupied(c) && static_cast<int>(it.GetTileType()) == static_cast<int>(currentStage->TileGrid.GetTilePtr(c)->GetTileType())) {
			left = true;
		}
		if (currentStage->TileGrid.isTileOccupied(b) && static_cast<int>(it.GetTileType()) == static_cast<int>(currentStage->TileGrid.GetTilePtr(b)->GetTileType())) {
			down = true;
		}
		if (currentStage->TileGrid.isTileOccupied(d) && static_cast<int>(it.GetTileType()) == static_cast<int>(currentStage->TileGrid.GetTilePtr(d)->GetTileType())) {
			up = true;
		}
		if (currentStage->TileGrid.isTileOccupied(e) && static_cast<int>(it.GetTileType()) == static_cast<int>(currentStage->TileGrid.GetTilePtr(e)->GetTileType())) {
			rightDown = true;
		}
		if (currentStage->TileGrid.isTileOccupied(h) && static_cast<int>(it.GetTileType()) == static_cast<int>(currentStage->TileGrid.GetTilePtr(h)->GetTileType())) {
			rightUp = true;
		}
		if (currentStage->TileGrid.isTileOccupied(g) && static_cast<int>(it.GetTileType()) == static_cast<int>(currentStage->TileGrid.GetTilePtr(g)->GetTileType())) {
			leftUp = true;
		}
		if (currentStage->TileGrid.isTileOccupied(f) && static_cast<int>(it.GetTileType()) == static_cast<int>(currentStage->TileGrid.GetTilePtr(f)->GetTileType())) {
			leftDown = true;
		}

		if (left && leftUp)
			keepType = true;
		if (up && rightUp)
			keepType = true;
		if (right && rightDown)
			keepType = true;
		if (down && leftDown)
			keepType = true;

		if (keepType) {
			currentStage->addTile(sp, (static_cast<int>(type) * MAX_IDIES_FOR_TILES) + id);
			continue;
		}

		if (!keepType) {
			if (currentStage->TileGrid.isTileOccupied(a)) {
				if (currentStage->TileGrid.GetTilePtr(a)->GetTileType() != it.GetTileType())
					type = currentStage->TileGrid.GetTilePtr(a)->GetTileType();
			}
			if (currentStage->TileGrid.isTileOccupied(c)) {
				if (currentStage->TileGrid.GetTilePtr(c)->GetTileType() != it.GetTileType())
					type = currentStage->TileGrid.GetTilePtr(c)->GetTileType();
			}
			if (currentStage->TileGrid.isTileOccupied(b)) {
				if (currentStage->TileGrid.GetTilePtr(b)->GetTileType() != it.GetTileType())
					type = currentStage->TileGrid.GetTilePtr(b)->GetTileType();
			}
			if (currentStage->TileGrid.isTileOccupied(d)) {
				if (currentStage->TileGrid.GetTilePtr(d)->GetTileType() != it.GetTileType()) 
					type = currentStage->TileGrid.GetTilePtr(d)->GetTileType();
			}
		}

		currentStage->addTile(sp, (static_cast<int>(type) * MAX_IDIES_FOR_TILES) + id);
		//currentStage->addDecoration(sp, static_cast<int>(it.GetTileType()) * MAX_IDIES_FOR_TILES + id, RNG);
		RNG--;
	}
	checkDeletedTiles();
}
void EditorState::setBackgroundTiles()
{
	while (!currentStage->BackGroundTiles.empty())
	{
		currentStage->BackGroundTiles.pop_front();
	}
	for (auto& it : currentStage->TileGrid.TileDeque) {
		if (!it.needBackgroundTile)
			continue;
		auto sp = it.GetGridPosition();
		auto a = GridCell(sp.x + 1, sp.y);
		auto b = GridCell(sp.x, sp.y + 1);
		auto c = GridCell(sp.x - 1, sp.y);
		auto d = GridCell(sp.x, sp.y - 1);
		auto e = GridCell(sp.x + 1, sp.y + 1);
		auto f = GridCell(sp.x - 1, sp.y + 1);
		auto g = GridCell(sp.x - 1, sp.y - 1);
		auto h = GridCell(sp.x + 1, sp.y - 1);

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

		if (currentStage->TileGrid.isTileOccupied(a) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(a)->GetTileType())) {
			right = false;
		}
		if (currentStage->TileGrid.isTileOccupied(c) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(c)->GetTileType())) {
			left = false;
		}
		if (currentStage->TileGrid.isTileOccupied(b) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(b)->GetTileType())) {
			down = false;
		}
		if (currentStage->TileGrid.isTileOccupied(d) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(d)->GetTileType())) {
			up = false;
		}
		if (currentStage->TileGrid.isTileOccupied(e) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(e)->GetTileType())) {
			rightDown = false;
		}
		if (currentStage->TileGrid.isTileOccupied(h) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(h)->GetTileType())) {
			rightUp = false;
		}
		if (currentStage->TileGrid.isTileOccupied(g) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(g)->GetTileType())) {
			leftUp = false;
		}
		if (currentStage->TileGrid.isTileOccupied(f) && static_cast<int>(it.GetTileType()) < static_cast<int>(currentStage->TileGrid.GetTilePtr(f)->GetTileType())) {
			leftDown = false;
		}


		if (left && currentStage->TileGrid.isTileOccupied(c) && static_cast<int>(it.GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(c)->GetTileType())) {
			if(currentStage->TileGrid.isTileOccupied(c) && currentStage->TileGrid.isTileOccupied(a))
				currentStage->addBackgroundTile(it.GetGridPosition(), currentStage->TileGrid.GetTilePtr(c)->ID);	//7c
		}
		if (right && currentStage->TileGrid.isTileOccupied(a) && static_cast<int>(it.GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(a)->GetTileType())) {
			if (currentStage->TileGrid.isTileOccupied(c) && currentStage->TileGrid.isTileOccupied(a))
				currentStage->addBackgroundTile(it.GetGridPosition(), currentStage->TileGrid.GetTilePtr(a)->ID);	//3a
		}
		if (down && currentStage->TileGrid.isTileOccupied(b) && static_cast<int>(it.GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(b)->GetTileType())) {
			if (currentStage->TileGrid.isTileOccupied(b) && currentStage->TileGrid.isTileOccupied(d))
				currentStage->addBackgroundTile(it.GetGridPosition(), currentStage->TileGrid.GetTilePtr(b)->ID);	//5b
		}
		if (up && currentStage->TileGrid.isTileOccupied(d) && static_cast<int>(it.GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(d)->GetTileType())) {
			if (currentStage->TileGrid.isTileOccupied(b) && currentStage->TileGrid.isTileOccupied(d))
				currentStage->addBackgroundTile(it.GetGridPosition(), currentStage->TileGrid.GetTilePtr(d)->ID);	//1d
		}



		if (rightUp && currentStage->TileGrid.isTileOccupied(h) && static_cast<int>(it.GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(h)->GetTileType()))
			currentStage->addBackgroundTile(it.GetGridPosition(), currentStage->TileGrid.GetTilePtr(h)->ID);	//2h
		if (rightDown && currentStage->TileGrid.isTileOccupied(e) && static_cast<int>(it.GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(e)->GetTileType()))
			currentStage->addBackgroundTile(it.GetGridPosition(), currentStage->TileGrid.GetTilePtr(e)->ID);	//4e
		if (leftUp && currentStage->TileGrid.isTileOccupied(g) && static_cast<int>(it.GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(g)->GetTileType()))
			currentStage->addBackgroundTile(it.GetGridPosition(), currentStage->TileGrid.GetTilePtr(g)->ID);	//0g
		if (leftDown && currentStage->TileGrid.isTileOccupied(f) && static_cast<int>(it.GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(f)->GetTileType()))
			currentStage->addBackgroundTile(it.GetGridPosition(), currentStage->TileGrid.GetTilePtr(f)->ID);	//6 f
	}
}
void EditorState::checkDeletedTiles()
{
	for (auto& it : currentStage->TileGrid.TileDeque) {
		auto sp = it.GetGridPosition();
		if (currentStage->TileGrid.GetTilePtr(sp) == nullptr) {
			currentStage->TileGrid.RemoveTile(sp);
		}
	}
}
void EditorState::editorFunction(const std::multimap<std::string, Button>::iterator& a_it)
{
	if (currentFunction == EditorState::EditorFunction::placeTile) {
		currentFunction = EditorState::EditorFunction::changeVariant;
		a_it->second.setText(editorFuncNames[static_cast<int>(currentFunction)]);
		return;
	}
	if (currentFunction == EditorState::EditorFunction::changeVariant) {
		currentFunction = EditorState::EditorFunction::placeObject;
		a_it->second.setText(editorFuncNames[static_cast<int>(currentFunction)]);
		return;
	}
	if (currentFunction == EditorState::EditorFunction::placeObject) {
		currentFunction = EditorState::EditorFunction::placeTile;
		a_it->second.setText(editorFuncNames[static_cast<int>(currentFunction)]);
		return;
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
	
	wheelFunctions();
	//std::cout << "== GAMESTATE == Update Func" << std::endl;
}

void EditorState::Render(sf::RenderTarget* a_target)
{
	currentStage->Render(a_target);
	cursorUpdateAndRender(a_target);
	//std::cout << "== GAMESTATE == Render Func" << std::endl;
}
