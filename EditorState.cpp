#include "EditorState.h"
/****************************************************/
//Private
/****************************************************/
void EditorState::mousePosUpdate(sf::Vector2f* a_mousePosOnCoords)
{
	mousePosVec = *a_mousePosOnCoords;
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
	for (auto it = p_stgM->StageContainer.rbegin(); it != p_stgM->StageContainer.rend();++it) {
		saveFile << p_dM->SaveFormat.StageDefiner << " " << it->first << endl;
		
		// saving tiles
		
		for (int i = 0; i < it->second.TileGrid.GetSize().x; i++) {
			for (int j = 0; j < it->second.TileGrid.GetSize().y; j++) {
				if (it->second.TileGrid.TileGridPtr[i][j] != nullptr)
					saveFile << p_dM->SaveFormat.ObjectDefiner << " " << p_dM->SaveFormat.TileDefiner << " " << it->second.TileGrid.TileGridPtr[i][j]->ID << " " << it->second.TileGrid.TileGridPtr[i][j]->posOnGrid.x
					<< " " << it->second.TileGrid.TileGridPtr[i][j]->posOnGrid.y << " " << it->second.TileGrid.TileGridPtr[i][j]->currentVariant << std::endl;
			}
		}

		// saving background tiles

		for (const auto& it_01 : it->second.BackGroundTiles) {
			saveFile << p_dM->SaveFormat.ObjectDefiner << " " << p_dM->SaveFormat.BackTileDefiner << " " << it_01.ID << " " << it_01.posOnGrid.x << " " << it_01.posOnGrid.y << std::endl;
		}

		// saving static objects

		for (const auto& it_02 : it->second.TileGrid.StaticObjStorageVec) {
			saveFile << p_dM->SaveFormat.ObjectDefiner << " " << p_dM->SaveFormat.StaticObjectDefiner << " " << it_02->ID << " " << it_02->sprite.getPosition().x << " " << it_02->sprite.getPosition().y << std::endl;
		}
		
		// saving interactable objects
		
		for (const auto& it_03 : it->second.TileGrid.InteractableObjStorageVec) {
			saveFile << p_dM->SaveFormat.ObjectDefiner << " " << p_dM->SaveFormat.InteractableObjectDefiner << " " << it_03->ID << " " << it_03->sprite.getPosition().x << " " << it_03->sprite.getPosition().y << std::endl;
		}

		// saving player objects

		for (const auto& it_04 : it->second.TileGrid.PlayerObjStorageVec) {
			saveFile << p_dM->SaveFormat.ObjectDefiner << " " << p_dM->SaveFormat.PlayerObjectDefiner << " " << it_04->ID << " " << it_04->sprite.getPosition().x << " " << it_04->sprite.getPosition().y << std::endl;
		}

		// saving special objects

		for (const auto& it_05 : it->second.TileGrid.SpecialObjStorageVec) {
			saveFile << p_dM->SaveFormat.ObjectDefiner << " " << p_dM->SaveFormat.SpecialObjectDefiner << " " << it_05->ID << " " << it_05->sprite.getPosition().x << " " << it_05->sprite.getPosition().y << " " << it_05->getProperties() << std::endl;
		}
		//each obj type must be added here...
	}

	saveFile.close();
	Keyboard::resetButtons();
	std::cout  << "Stages saved" << std::endl;
}
void EditorState::buttonFunctions(const std::multimap<std::string, Button>::iterator& a_it)
{
	if (Windows.begin()->getID() == 1) {
		if (Window::CheckButton(a_it, p_dM->Lang.save)) {
			saveStages();
		}
		if (Window::CheckButton(a_it, "Editor_Func")) {
			editorFunction(a_it);
		}
		if (Window::CheckButton(a_it, "Add_Stage")) {
			v_addStageDial = true;
		}
		if (Window::CheckButton(a_it, "Next_Stage")) {
			changeStage(true);
		}
		if (Window::CheckButton(a_it, "Back_Stage")) {
			changeStage(false);
		}
		if (Window::CheckButton(a_it, "Clear_Stage")) {
			v_createClearDial = true;
		}
		if (Window::CheckButton(a_it, "Delete_Stage")) {
			v_delStageDial = true;
		}
	}
	else if (Windows.begin()->getID() == 99)
	{
		if (Window::CheckButton(a_it, p_dM->Lang.yes)) {
			clearStage();
		}
		if (Window::CheckButton(a_it, p_dM->Lang.no)) {
			v_closeClearDial = true;
		}
	}
	else if (Windows.begin()->getID() == 201) {
		if (Window::CheckButton(a_it, p_dM->Lang.yes)) {
			addStage();
		}
		if (Window::CheckButton(a_it, p_dM->Lang.no)) {
			v_closeAddStageDial = true;
		}
	}
	else if (Windows.begin()->getID() == 202) {
		if (Window::CheckButton(a_it, p_dM->Lang.yes)) {
			deleteStage();
		}
		if (Window::CheckButton(a_it, p_dM->Lang.no)) {
			v_closeDelStageDial = true;
		}
	}
	else if (Windows.begin()->getID() == 203) {
		if (Window::CheckButton(a_it, p_dM->Lang.yes)) {
			auto a = Tile::g_lastTileID;
			currentStage->addObject(mousePosPressed_SpcObj, a + objectIdOffset, inputString);
			v_closeSpecialObjectDial = true;
		}
		if (Window::CheckButton(a_it, p_dM->Lang.no)) {
			v_closeSpecialObjectDial = true;
		}
	}
}

void EditorState::placeTiles()
{
	auto selectorSize = OpenedWindow->GetSliderValue("Cursor_Size") + 1;
	auto tileType = currentTyleType;

	if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold) {
		for (int i = 0; i < selectorSize; i++) {
			for (int j = 0; j < selectorSize; j++) {
				currentStage->addTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y + j), (tileType * MAX_IDIES_FOR_TILES) + currentTileID);
				addTilesToUpdate(MousePosOnGrid.x + i, MousePosOnGrid.y + j);
			}
		}
	}
	if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::hold) {
		for (int i = 0; i < selectorSize; i++) {
			for (int j = 0; j < selectorSize; j++) {
				currentStage->TileGrid.RemoveTile(GridCell(MousePosOnGrid.x + i, MousePosOnGrid.y + j));
				addTilesToUpdate(MousePosOnGrid.x + i, MousePosOnGrid.y + j);
			}
		}
	}

	if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::released) {
		updateTiles();
		updateTiles();
		tileUpdateMap.clear();
		setBackgroundTiles();
	}
	if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::released) {
		updateTiles();
		updateTiles();
		tileUpdateMap.clear();
		setBackgroundTiles();
	}
}

void EditorState::addTilesToUpdate(int a_x, int a_y)
{
	/// /////////////////////////////////
	/// adding neibour tiles to update
	/// /////////////////////////////////
	//int a = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (a_x + i <= 0 || a_y + j <= 0)
				continue;
			tileUpdateMap[a_x + i][a_y + j] = GridCell(a_x + i, a_y + j);
		
		}
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
	int a = 0;
	if(Keyboard::checkMouseButtonState(sf::Mouse::Left) != Keyboard::KeyState::hold){
		for (auto i : currentStage->TileGrid.RenderObjPtrVec) {
			if (i->getHitboxWorldRect().contains(mousePosVec)) {
				selectedObject = i;
				break;
			}
			else {
				selectedObject = nullptr;
			}
		}
		if (selectedObject == nullptr) {
			for (auto i : currentStage->TileGrid.RenderEditorObjPtrVec) {
				if (i->getHitboxWorldRect().contains(mousePosVec)) {
					selectedObject = i;
					break;
				}
				else {
					selectedObject = nullptr;
				}
			}
		}
	}
	if (Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::pressed) {
		//currentStage->addTile(MousePosOnGrid, 14);
		//std::cout << Tile::g_lastTileID;
		mousePosPressed = mousePosVec;
		if (currentFunction == EditorState::EditorFunction::specialObjects && !v_addSpecialObjectDial) {
			mousePosPressed_SpcObj = mousePosVec;
			v_addSpecialObjectDial = true;
			return;
		}
		if (selectedObject != nullptr) {
			tempObjPos = selectedObject->sprite.getPosition();
			return;
		}
		auto a = Tile::g_lastTileID;
		currentStage->addObject(mousePosVec, a + objectIdOffset);
	}
	else if (Keyboard::checkMouseButtonState(sf::Mouse::Right) == Keyboard::KeyState::pressed) {
		if (selectedObject == nullptr)
			return;
		Object* tmp = selectedObject;
		selectedObject = nullptr;
		currentStage->TileGrid.RemoveObject(tmp);
	}else if(Keyboard::checkMouseButtonState(sf::Mouse::Left) == Keyboard::KeyState::hold){
		if (selectedObject == nullptr)
			return;
		auto tempMouse = mousePosVec - mousePosPressed;
		
		currentStage->TileGrid.MoveOnPos(tempObjPos + tempMouse, selectedObject);
		//selectedObject->SetPosition(tempObjPos + tempMouse);
	}
}

void EditorState::wheelFunctions()
{
	if (currentFunction == EditorState::EditorFunction::placeTile) {
		if (Keyboard::mouseWheel() == Keyboard::MouseWheel::up) {
			if (!singleTileMode)
				currentTyleType--;

			if (currentTyleType < 0) {
				currentTyleType = MAX_TILE_TYPES;
			}

			if (currentTyleType == static_cast<int>(Tile::groundTileType::other)) {
				if (!singleTileMode)
					currentTileID = Tile::g_lastID + 1;
				singleTileMode = true;
				OpenedWindow->SetElementValue("Cursor_Size", 0);
				currentTileID--;
				if (currentTileID < 0) {
					singleTileMode = false;
					OpenedWindow->SetElementValue("Cursor_Size", 1);
					currentTyleType--;
					currentTileID = DEFAULT_BASE_TILE;
				}
			}
			else {
				currentTileID = DEFAULT_BASE_TILE;
			}
		}
		else if (Keyboard::mouseWheel() == Keyboard::MouseWheel::down) {
			if (!singleTileMode)
				currentTyleType++;

			if (currentTyleType == static_cast<int>(Tile::groundTileType::other)) {
				if (!singleTileMode)
					currentTileID = -1;
				singleTileMode = true;
				OpenedWindow->SetElementValue("Cursor_Size", 0);
				currentTileID++;
				if (currentTileID > Tile::g_lastID) {
					singleTileMode = false;
					OpenedWindow->SetElementValue("Cursor_Size", 1);
					currentTyleType++;
					currentTileID = DEFAULT_BASE_TILE;
				}
			}
			if (currentTyleType > MAX_TILE_TYPES) {
				currentTyleType = 0;
			}

		}
	}
	else if (currentFunction == EditorState::EditorFunction::placeObject) {
		auto a = Tile::g_lastTileID;
		if (Keyboard::mouseWheel() == Keyboard::MouseWheel::up) {
			objectIdOffset++;
			for (int i = 0; i < p_oM->SpecialObjectsIDs.size(); i++) {
				if (p_oM->IsIDSpecial(objectIdOffset + a))
					objectIdOffset++;
			}
			if (a + objectIdOffset > Sprite::LAST_ID) {
				objectIdOffset = 0;
			}
		}
		else if (Keyboard::mouseWheel() == Keyboard::MouseWheel::down) {
			objectIdOffset--;
			if (objectIdOffset == UINT_MAX)
				objectIdOffset = Sprite::LAST_ID - a;
			for (int i = 0; i < p_oM->SpecialObjectsIDs.size(); i++) {
				if (p_oM->IsIDSpecial(objectIdOffset + a))
					objectIdOffset--;
			}
		}
	}
	else if (currentFunction == EditorState::EditorFunction::specialObjects) {
		auto a = Tile::g_lastTileID;
		if (Keyboard::mouseWheel() == Keyboard::MouseWheel::up) {
			spcObjWheelOffset++;
			if (spcObjWheelOffset == p_oM->SpecialObjectsIDs.size())
				spcObjWheelOffset = 0;
			objectIdOffset = p_oM->SpecialObjectsIDs.front() + spcObjWheelOffset - a;
		}
		else if (Keyboard::mouseWheel() == Keyboard::MouseWheel::down) {
			spcObjWheelOffset--;
			if (spcObjWheelOffset == UINT_MAX)
				spcObjWheelOffset = p_oM->SpecialObjectsIDs.size() - 1;
			objectIdOffset = p_oM->SpecialObjectsIDs.front() + spcObjWheelOffset - a;
		}
	}
	updateText();
}

void EditorState::updateText()
{
	if(currentFunction == EditorState::EditorFunction::placeTile)
		OpenedWindow->SetElementValue("Current_Obj_Name", p_dM->tileNames[currentTyleType]);
	else if (currentFunction == EditorState::EditorFunction::changeVariant) {
		if (selectedTile == nullptr) {
			OpenedWindow->SetElementValue("Current_Obj_Name", "");
		}
		else {
			OpenedWindow->SetElementValue("Current_Obj_Name", p_dM->tileNames[static_cast<int>(selectedTile->GetTileType())]);
		}
	}
}

void EditorState::cursorUpdateAndRender(sf::RenderTarget* a_target)
{
	if (OpenedWindow->getID() != 1)
		return;
	OpenedWindow->SetElementValue("Current_Stage_Name", currentStage->Name);
	cursorShape.setPosition(MousePosOnGrid.x * TILE_SIZE, MousePosOnGrid.y * TILE_SIZE);
	if (currentFunction == EditorState::EditorFunction::placeTile) {
		auto selectorSize = OpenedWindow->GetSliderValue("Cursor_Size");
		cursorShape.setSize(sf::Vector2f((selectorSize + 1) * TILE_SIZE, (selectorSize + 1) * TILE_SIZE));
		Tile* p = currentStage->getPrefTilePtr(MAX_IDIES_FOR_TILES * currentTyleType + currentTileID);
		activeSprite = p->sprite;
		OpenedWindow->SetElementValue("Tile_Image", &activeSprite);
		OpenedWindow->SetElementValue("Obj_Image", &emptySprite);
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
		OpenedWindow->SetElementValue("Tile_Image", &activeSprite);
		a_target->draw(cursorShape);
	}
	if (currentFunction == EditorState::EditorFunction::placeObject || currentFunction == EditorState::EditorFunction::specialObjects)
	{
		if (selectedObject != nullptr) {
			activeSprite = selectedObject->sprite;
		} 
		else
		{
			auto a = Tile::g_lastTileID;
			Object* p = currentStage->getPrefObjPtr(a + objectIdOffset);
			activeSprite = p->sprite;
			//activeSprite.setTexture(p_dM->emptyTxt);
		}
		OpenedWindow->SetElementValue("Tile_Image", &emptySprite);
		OpenedWindow->SetElementValue("Current_Obj_Name", "");
		OpenedWindow->SetElementValue("Obj_Image", &activeSprite);
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
	else if (currentFunction == EditorState::EditorFunction::placeObject || currentFunction == EditorState::EditorFunction::specialObjects) {
		placeObjects();
	}

}
void EditorState::updateTiles()
{
	auto RNG = p_dM->seed + 10000;
	auto TileRNG = RNG;
	for(const auto& it_01 : tileUpdateMap){
		for (const auto& it_02 : it_01.second) {
			auto it = currentStage->TileGrid.TileGridPtr[it_02.second.x][it_02.second.y];
			if (it == nullptr)
				continue;
			if (!it->isTilable)
				continue;
			auto sp = it->GetGridPosition();
			auto a = GridCell(sp.x + 1, sp.y);		//right
			auto b = GridCell(sp.x, sp.y + 1);		//down
			auto c = GridCell(sp.x - 1, sp.y);		//left
			auto d = GridCell(sp.x, sp.y - 1);		//up
			auto e = GridCell(sp.x + 1, sp.y + 1);	//right Down
			auto f = GridCell(sp.x - 1, sp.y + 1);	//left Down
			auto g = GridCell(sp.x - 1, sp.y - 1);	//left Up
			auto h = GridCell(sp.x + 1, sp.y - 1);	//right Up			cgd	dha aeb bfc

			bool right = false;
			bool left = false;
			bool up = false;
			bool down = false;
			bool rightUp = false;
			bool rightDown = false;
			bool leftUp = false;
			bool leftDown = false;
			bool keepType = false;

			auto type = it->GetTileType();

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
				currentStage->TileGrid.RemoveTile(sp);
				continue;
			}

			if (currentStage->TileGrid.isTileOccupied(a) && static_cast<int>(type) == static_cast<int>(currentStage->TileGrid.GetTilePtr(a)->GetTileType())) {
				right = true;
			}
			if (currentStage->TileGrid.isTileOccupied(c) && static_cast<int>(type) == static_cast<int>(currentStage->TileGrid.GetTilePtr(c)->GetTileType())) {
				left = true;
			}
			if (currentStage->TileGrid.isTileOccupied(b) && static_cast<int>(type) == static_cast<int>(currentStage->TileGrid.GetTilePtr(b)->GetTileType())) {
				down = true;
			}
			if (currentStage->TileGrid.isTileOccupied(d) && static_cast<int>(type) == static_cast<int>(currentStage->TileGrid.GetTilePtr(d)->GetTileType())) {
				up = true;
			}
			if (currentStage->TileGrid.isTileOccupied(e) && static_cast<int>(type) == static_cast<int>(currentStage->TileGrid.GetTilePtr(e)->GetTileType())) {
				rightDown = true;
			}
			if (currentStage->TileGrid.isTileOccupied(h) && static_cast<int>(type) == static_cast<int>(currentStage->TileGrid.GetTilePtr(h)->GetTileType())) {
				rightUp = true;
			}
			if (currentStage->TileGrid.isTileOccupied(g) && static_cast<int>(type) == static_cast<int>(currentStage->TileGrid.GetTilePtr(g)->GetTileType())) {
				leftUp = true;
			}
			if (currentStage->TileGrid.isTileOccupied(f) && static_cast<int>(type) == static_cast<int>(currentStage->TileGrid.GetTilePtr(f)->GetTileType())) {
				leftDown = true;
			}

			if (left && leftUp && up)
				keepType = true;
			if (up && rightUp && right)
				keepType = true;
			if (right && rightDown && down)
				keepType = true;
			if (down && leftDown && left)
				keepType = true;

			if (!keepType) {
				if (currentStage->TileGrid.isTileOccupied(a)) {
					if (currentStage->TileGrid.GetTilePtr(a)->GetTileType() != it->GetTileType())
						if(currentStage->TileGrid.GetTilePtr(a)->GetTileType() != Tile::groundTileType::other)
							type = currentStage->TileGrid.GetTilePtr(a)->GetTileType();

				}
				if (currentStage->TileGrid.isTileOccupied(c)) {
					if (currentStage->TileGrid.GetTilePtr(c)->GetTileType() != it->GetTileType())
						if (currentStage->TileGrid.GetTilePtr(c)->GetTileType() != Tile::groundTileType::other)
							type = currentStage->TileGrid.GetTilePtr(c)->GetTileType();
				}
				if (currentStage->TileGrid.isTileOccupied(b)) {
					if (currentStage->TileGrid.GetTilePtr(b)->GetTileType() != it->GetTileType())
						if (currentStage->TileGrid.GetTilePtr(b)->GetTileType() != Tile::groundTileType::other)
							type = currentStage->TileGrid.GetTilePtr(b)->GetTileType();
				}
				if (currentStage->TileGrid.isTileOccupied(d)) {
					if (currentStage->TileGrid.GetTilePtr(d)->GetTileType() != it->GetTileType())
						if (currentStage->TileGrid.GetTilePtr(d)->GetTileType() != Tile::groundTileType::other)
							type = currentStage->TileGrid.GetTilePtr(d)->GetTileType();
				}
				////if still type is the same add corner options
			}

			//////////////////////////////////////////////
			/// seting up type
			//////////////////////////////////////////////
			
			right = true;
			left = true;
			up = true;
			down = true;
			rightUp = true;
			rightDown = true;
			leftUp = true;
			leftDown = true;


			if (currentStage->TileGrid.isTileOccupied(a) && currentStage->TileGrid.GetTilePtr(a)->GetTileType() == type) {
				right = false;
			}
			if (currentStage->TileGrid.isTileOccupied(c) && currentStage->TileGrid.GetTilePtr(c)->GetTileType() == type) {
				left = false;
			}
			if (currentStage->TileGrid.isTileOccupied(b) && currentStage->TileGrid.GetTilePtr(b)->GetTileType() == type) {
				down = false;
			}
			if (currentStage->TileGrid.isTileOccupied(d) && currentStage->TileGrid.GetTilePtr(d)->GetTileType() == type) {
				up = false;
			}
			if (currentStage->TileGrid.isTileOccupied(e) && currentStage->TileGrid.GetTilePtr(e)->GetTileType() == type) {
				rightDown = false;
			}
			if (currentStage->TileGrid.isTileOccupied(h) && currentStage->TileGrid.GetTilePtr(h)->GetTileType() == type) {
				rightUp = false;
			}
			if (currentStage->TileGrid.isTileOccupied(g) && currentStage->TileGrid.GetTilePtr(g)->GetTileType() == type) {
				leftUp = false;
			}
			if (currentStage->TileGrid.isTileOccupied(f) && currentStage->TileGrid.GetTilePtr(f)->GetTileType() == type) {
				leftDown = false;
			}

			if (currentStage->TileGrid.isTileOccupied(a) && static_cast<int>(type) < static_cast<int>(currentStage->TileGrid.GetTilePtr(a)->GetTileType())) {
				right = false;
			}
			if (currentStage->TileGrid.isTileOccupied(c) && static_cast<int>(type) < static_cast<int>(currentStage->TileGrid.GetTilePtr(c)->GetTileType())) {
				left = false;
			}
			if (currentStage->TileGrid.isTileOccupied(b) && static_cast<int>(type) < static_cast<int>(currentStage->TileGrid.GetTilePtr(b)->GetTileType())) {
				down = false;
			}
			if (currentStage->TileGrid.isTileOccupied(d) && static_cast<int>(type) < static_cast<int>(currentStage->TileGrid.GetTilePtr(d)->GetTileType())) {
				up = false;
			}
			if (currentStage->TileGrid.isTileOccupied(e) && static_cast<int>(type) < static_cast<int>(currentStage->TileGrid.GetTilePtr(e)->GetTileType())) {
				rightDown = false;
			}
			if (currentStage->TileGrid.isTileOccupied(h) && static_cast<int>(type) < static_cast<int>(currentStage->TileGrid.GetTilePtr(h)->GetTileType())) {
				rightUp = false;
			}
			if (currentStage->TileGrid.isTileOccupied(g) && static_cast<int>(type) < static_cast<int>(currentStage->TileGrid.GetTilePtr(g)->GetTileType())) {
				leftUp = false;
			}
			if (currentStage->TileGrid.isTileOccupied(f) && static_cast<int>(type) < static_cast<int>(currentStage->TileGrid.GetTilePtr(f)->GetTileType())) {
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
				int a[3] = { 30, 40, 50 };
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
			
			currentStage->addTile(sp, (static_cast<int>(type) * MAX_IDIES_FOR_TILES) + id);
			RNG--;
		}
	}
}
void EditorState::setBackgroundTiles()
{
	//while (!currentStage->BackGroundTiles.empty())
	//{
	//	currentStage->BackGroundTiles.pop_front();
	//}
	currentStage->BackGroundTiles.clear();
	for (int i = 0; i < currentStage->TileGrid.GetSize().x; i++) {
		for (int j = 0; j < currentStage->TileGrid.GetSize().y; j++) {
			if (currentStage->TileGrid.TileGridPtr[i][j] != nullptr) {
				auto it = currentStage->TileGrid.TileGridPtr[i][j];
				if (!it->needBackgroundTile)
					continue;
				auto sp = it->GetGridPosition();
				auto a = GridCell(sp.x + 1, sp.y);		//right
				auto b = GridCell(sp.x, sp.y + 1);		//down
				auto c = GridCell(sp.x - 1, sp.y);		//left
				auto d = GridCell(sp.x, sp.y - 1);		//up
				auto e = GridCell(sp.x + 1, sp.y + 1);	//right Down
				auto f = GridCell(sp.x - 1, sp.y + 1);	//left Down
				auto g = GridCell(sp.x - 1, sp.y - 1);	//left Up
				auto h = GridCell(sp.x + 1, sp.y - 1);	//right Up

				if (currentStage->TileGrid.isTileOccupied(c) && static_cast<int>(it->GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(c)->GetTileType())) {
					if (currentStage->TileGrid.isTileOccupied(c) && currentStage->TileGrid.isTileOccupied(a)) {
						currentStage->addBackgroundTile(it->GetGridPosition(), currentStage->TileGrid.GetTilePtr(c)->ID);	//7c
						continue;
					}
				}
				if (currentStage->TileGrid.isTileOccupied(a) && static_cast<int>(it->GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(a)->GetTileType())) {
					if (currentStage->TileGrid.isTileOccupied(c) && currentStage->TileGrid.isTileOccupied(a)) {
						currentStage->addBackgroundTile(it->GetGridPosition(), currentStage->TileGrid.GetTilePtr(a)->ID);	//3a
						continue;
					}
				}
				if (currentStage->TileGrid.isTileOccupied(b) && static_cast<int>(it->GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(b)->GetTileType())) {
					if (currentStage->TileGrid.isTileOccupied(b) && currentStage->TileGrid.isTileOccupied(d)) {
						currentStage->addBackgroundTile(it->GetGridPosition(), currentStage->TileGrid.GetTilePtr(b)->ID);	//5b
						continue;
					}
				}
				if (currentStage->TileGrid.isTileOccupied(d) && static_cast<int>(it->GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(d)->GetTileType())) {
					if (currentStage->TileGrid.isTileOccupied(b) && currentStage->TileGrid.isTileOccupied(d)) {
						currentStage->addBackgroundTile(it->GetGridPosition(), currentStage->TileGrid.GetTilePtr(d)->ID);	//1d
						continue;
					}
				}



				if (currentStage->TileGrid.isTileOccupied(h) && static_cast<int>(it->GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(h)->GetTileType()))
					currentStage->addBackgroundTile(it->GetGridPosition(), currentStage->TileGrid.GetTilePtr(h)->ID);	//2h
				if (currentStage->TileGrid.isTileOccupied(e) && static_cast<int>(it->GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(e)->GetTileType()))
					currentStage->addBackgroundTile(it->GetGridPosition(), currentStage->TileGrid.GetTilePtr(e)->ID);	//4e
				if (currentStage->TileGrid.isTileOccupied(g) && static_cast<int>(it->GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(g)->GetTileType()))
					currentStage->addBackgroundTile(it->GetGridPosition(), currentStage->TileGrid.GetTilePtr(g)->ID);	//0g
				if (currentStage->TileGrid.isTileOccupied(f) && static_cast<int>(it->GetTileType()) > static_cast<int>(currentStage->TileGrid.GetTilePtr(f)->GetTileType()))
					currentStage->addBackgroundTile(it->GetGridPosition(), currentStage->TileGrid.GetTilePtr(f)->ID);	//6 f
			}
		}
	}
}

void EditorState::editorFunction(const std::multimap<std::string, Button>::iterator& a_it)
{
	auto a = Tile::g_lastTileID;
	if (currentFunction == EditorState::EditorFunction::placeTile) {
		currentFunction = EditorState::EditorFunction::changeVariant;
		a_it->second.setText(editorFuncNames[static_cast<int>(currentFunction)]);
		return;
	}
	if (currentFunction == EditorState::EditorFunction::changeVariant) {
		currentFunction = EditorState::EditorFunction::placeObject;
		a_it->second.setText(editorFuncNames[static_cast<int>(currentFunction)]);
		objectIdOffset = 0;
		return;
	}
	if (currentFunction == EditorState::EditorFunction::placeObject) {
		currentFunction = EditorState::EditorFunction::specialObjects;
		a_it->second.setText(editorFuncNames[static_cast<int>(currentFunction)]);
		objectIdOffset = p_oM->SpecialObjectsIDs.front() - a;
		return;
	}
	if (currentFunction == EditorState::EditorFunction::specialObjects) {
		currentFunction = EditorState::EditorFunction::placeTile;
		a_it->second.setText(editorFuncNames[static_cast<int>(currentFunction)]);
		return;
	}
		
}
void EditorState::clearStage()
{
	//while (!currentStage->BackGroundTiles.empty())
	//{
	//	currentStage->BackGroundTiles.pop_front();
	//}
	currentStage->BackGroundTiles.clear();
	std::map<int, std::map<int, GridCell>> _temp;
	for (int i = 0; i < currentStage->TileGrid.GetSize().x; i++) {
		for (int j = 0; j < currentStage->TileGrid.GetSize().y; j++) {
			if (currentStage->TileGrid.TileGridPtr[i][j] != nullptr) {
				_temp[i][j] = GridCell(i, j);
			}
		}
	}
	for (const auto& it_01 : _temp) {
		for (const auto& it_02 : it_01.second) {
			currentStage->TileGrid.RemoveTile(GridCell(it_02.second.x, it_02.second.y));
		}
	}
	v_closeClearDial = true;
}

void EditorState::closeDialWindow()
{
	if (!v_closeClearDial)
		return;
	v_closeClearDial = false;
	if (Windows.size()) {
		Windows.begin()->setToClose = true;
		return;
	}
}

void EditorState::createClearDial()
{
	if (!v_createClearDial)
		return;
	v_createClearDial = false;
	PushWindow(99, sf::Vector2f(260, 40), sf::Vector2f(260, 100), "Do you want clear stage?", sf::Vector2f(128, 30), sf::Color::Black);
	Windows.begin()->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(330, 90), p_dM->Lang.yes, sf::Color(23, 23, 23));
	Windows.begin()->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(400, 90), p_dM->Lang.no, sf::Color(23, 23, 23));
}

void EditorState::closeAddStageDial()
{
	if (!v_closeAddStageDial)
		return;
	v_closeAddStageDial = false;
	if (Windows.size()) {
		Windows.begin()->setToClose = true;
		return;
	}
}

void EditorState::inputWindowMenager()
{

	if (Windows.begin()->getID() == 201 || Windows.begin()->getID() == 203) {
		inputTimer();
		if (p_event->type == sf::Event::TextEntered) {
			if (p_event->text.unicode < 128) {
				if (v_inputTimer != 0)
					return;
				v_inputTimer = 8;
				input += p_event->text.unicode;
				inputString = input;
				OpenedWindow->SetElementValue("Input", inputString);
			}
		}
	}
}

void EditorState::inputTimer()
{
	if(v_inputTimer != 0)
		v_inputTimer--;
}

void EditorState::closeDelStageDial()
{
	if (!v_closeDelStageDial)
		return;
	v_closeDelStageDial = false;
	if (Windows.size()) {
		Windows.begin()->setToClose = true;
		return;
	}
}

void EditorState::createAddStageDial()
{
	if (!v_addStageDial)
		return;
	v_addStageDial = false;
	inputString = "";
	input = inputString;
	PushWindow(201, sf::Vector2f(260, 40), sf::Vector2f(260, 150), "Enter Stage name?", sf::Vector2f(128, 30), sf::Color::Black);
	Windows.begin()->AddText("Input", sf::Vector2f(375, 90), sf::Color::Black, inputString);
	Windows.begin()->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(330, 140), p_dM->Lang.yes, sf::Color(23, 23, 23));
	Windows.begin()->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(400, 140), p_dM->Lang.no, sf::Color(23, 23, 23));
}

void EditorState::closeAddSpecialObjDial()
{
	if (!v_closeSpecialObjectDial)
		return;
	v_closeSpecialObjectDial = false;
	if (Windows.size()) {
		Windows.begin()->setToClose = true;
		return;
	}
}

void EditorState::createAddSpecialObjDial()
{
	if (!v_addSpecialObjectDial)
		return;
	v_addSpecialObjectDial = false;
	inputString = "";
	input = inputString;
	PushWindow(203, sf::Vector2f(260, 40), sf::Vector2f(260, 150), "Enter Special Propeties?", sf::Vector2f(128, 30), sf::Color::Black);
	Windows.begin()->AddText("Input", sf::Vector2f(375, 90), sf::Color::Black, inputString);
	Windows.begin()->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(330, 140), p_dM->Lang.yes, sf::Color(23, 23, 23));
	Windows.begin()->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(400, 140), p_dM->Lang.no, sf::Color(23, 23, 23));
}

void EditorState::createDelStageDial()
{
	if (!v_delStageDial)
		return;
	v_delStageDial = false;
	PushWindow(202, sf::Vector2f(260, 40), sf::Vector2f(260, 100), "Delete this stage?", sf::Vector2f(128, 30), sf::Color::Black);
	Windows.begin()->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(330, 90), p_dM->Lang.yes, sf::Color(23, 23, 23));
	Windows.begin()->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(400, 90), p_dM->Lang.no, sf::Color(23, 23, 23));
}
void EditorState::changeStage(bool a_next)
{
	if (a_next)
		stageOffset++;
	else
		stageOffset--;
	if (stageOffset == UINT_MAX)
		stageOffset = p_stgM->StageNames.size() - 1;
	if (stageOffset > p_stgM->StageNames.size() - 1)
		stageOffset = 0;
	auto s = p_stgM->StageNames.at(stageOffset);
	std::multimap<std::string, Stage>::iterator it; 
	it = p_stgM->StageContainer.find(s);
	currentStage = &it->second;
	std::cout << it->first << endl;
}

void EditorState::deleteStage()
{
	if (p_stgM->StageContainer.size() <= 1) {
		std::cout << "== EDITOR STATE == Can't delete last stage" << std::endl;
		return;
	}

	auto& stgName = p_stgM->StageNames.at(0), currName = currentStage->Name;
	stageOffset = 0;
	if (p_stgM->StageNames.at(0) == currName) {
		stgName = p_stgM->StageNames.at(1);
	}
	int a = 0;
	for (auto& i : p_stgM->StageNames) {
		if (i == currentStage->Name)
			break;
		a++;
	}
	std::multimap<std::string, Stage>::iterator it;
	it = p_stgM->StageContainer.find(stgName);
	currentStage = &it->second;
	p_stgM->StageNames.erase(p_stgM->StageNames.begin() + a);
	p_stgM->StageContainer.erase(currName);
	v_closeClearDial = true;

}

void EditorState::addStage()
{
	cout << inputString << endl;
	p_stgM->StageContainer.insert(std::pair<std::string, Stage>(inputString, Stage(p_oM, inputString, p_dM)));
	p_stgM->StageNames.push_back(inputString);
	std::multimap<std::string, Stage>::iterator it;
	it = p_stgM->StageContainer.find(inputString);
	currentStage = &it->second;
	v_closeAddStageDial = true;
	std::cout << "== EDITOR STATE == Stage Created" << std::endl;
	
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
	createClearDial();
	closeDialWindow();
	createAddStageDial();
	closeAddStageDial();
	closeAddSpecialObjDial();
	createAddSpecialObjDial();
	inputWindowMenager();


	currentStage->Update(a_mousePos);
	mousePosUpdate(a_mousePosOnCoords);
	mouseFunctions();

	moveCamera(p_mainCamera);

	createDelStageDial();
	closeDelStageDial();

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
