#include "GameState.h"

/****************************************************/
//Private
/****************************************************/

void GameState::ButtonFunctions(const std::multimap<std::string, Button>::iterator& a_it)
{
	if (Window::CheckButton(a_it, p_dM->Lang.quit)) {
		v_createQuitDial = true;
	}
}

void GameState::createQuitDial()
{
	if (!v_createQuitDial)
		return;
	v_createQuitDial = false;
	PushWindow(999, sf::Vector2f(250, 40), sf::Vector2f(200, 100), p_dM->Lang.quitDial, sf::Vector2f(100, 30), sf::Color::Black);
	OpenedWindow->AddButton(p_dM->Lang.yes, sf::Vector2f(50, 30), sf::Vector2f(300, 90), p_dM->Lang.yes, sf::Color(23, 23, 23));
	OpenedWindow->AddButton(p_dM->Lang.no, sf::Vector2f(50, 30), sf::Vector2f(360, 90), p_dM->Lang.no, sf::Color(23, 23, 23));
}

void GameState::switchCameraMode()
{
	if (Keyboard::checkKeyState(sf::Keyboard::Home) == Keyboard::KeyState::pressed) {
		freeCamEnable = !freeCamEnable;
		if (!freeCamEnable) {
			p_mainCamera->ActiveCamera();
		}
		else if (freeCamEnable) {
			p_freeCam->ActiveCamera();
			PushNotification("Free Camera Mode", sf::Color::White);
		}
	}
}

void GameState::cameraMovementSetup()
{
	if (!freeCamEnable)
		return;
	int speed = 2;
	if (Keyboard::checkKeyState(sf::Keyboard::LShift) == Keyboard::KeyState::hold)
		speed = 5;
	moveCamera(p_freeCam, speed);
}

void GameState::cameraFollowObject(Object* a_obj)
{
	if(a_obj != nullptr)
		p_mainCamera->setCenter(a_obj->GetPosition());
}

void GameState::cameraFollowObject(Object* a_obj, sf::FloatRect a_limits)
{
	if (a_obj == nullptr)
		return;
	float x, y;
	if (a_obj->GetPosition().x > a_limits.left && a_obj->GetPosition().x < a_limits.width)
		x = a_obj->GetPosition().x;
	else if (a_obj->GetPosition().x <= a_limits.left)
		x = a_limits.left;
	else if (a_obj->GetPosition().x >= a_limits.width)
		x = a_limits.width;

	if (a_obj->GetPosition().y > a_limits.top && a_obj->GetPosition().y < a_limits.height)
		y = a_obj->GetPosition().y;
	else if (a_obj->GetPosition().y <= a_limits.top)
		y = a_limits.top;
	else if (a_obj->GetPosition().y >= a_limits.height)
		y = a_limits.height;

	auto pos = sf::Vector2f(x, y);
	p_mainCamera->setCenter(pos);
}

bool GameState::canEnterTile(Object* a_obj, Directions a_dir)
{
	Tile* tile = nullptr;
	auto objPos = a_obj->GetPosition();

	auto gridPos = GridCell(objPos.x / TILE_SIZE, objPos.y / TILE_SIZE);
	switch (a_dir)
	{
	case Directions::up:
		objPos = sf::Vector2f(objPos.x, objPos.y + 31);
		gridPos = GridCell(objPos.x / TILE_SIZE, objPos.y / TILE_SIZE);
		tile = currentStage->TileGrid.GetTilePtr(GridCell(gridPos.x, gridPos.y - 1));
		break;
	case Directions::down:
		objPos = sf::Vector2f(objPos.x, objPos.y - 31);
		gridPos = GridCell(objPos.x / TILE_SIZE, objPos.y / TILE_SIZE);
		tile = currentStage->TileGrid.GetTilePtr(GridCell(gridPos.x, gridPos.y + 1));
		break;
	case Directions::left:
		objPos = sf::Vector2f(objPos.x + 31, objPos.y);
		gridPos = GridCell(objPos.x / TILE_SIZE, objPos.y / TILE_SIZE);
		tile = currentStage->TileGrid.GetTilePtr(GridCell(gridPos.x - 1, gridPos.y));
		break;
	case Directions::right:
		objPos = sf::Vector2f(objPos.x, objPos.y);		//x - 15 for edge walking
		gridPos = GridCell(objPos.x / TILE_SIZE, objPos.y / TILE_SIZE);
		tile = currentStage->TileGrid.GetTilePtr(GridCell(gridPos.x + 1, gridPos.y));
		break;
	}
	if(tile == nullptr)
		return false;
	if (!tile->isTileWalkable())
		return false;
	return true;
}

bool GameState::checkCollision(sf::Vector2f a_pointLeft, sf::Vector2f a_pointRight)
{
	/// <summary>
	///	checks collision in 5 point of one edge on sprite with all solid objects on map; 
	/// </summary>
	/// <returns>Returs true if collision accures</returns>
	bool horizontal = false;
	bool vertical = false;
	if (a_pointLeft.x == a_pointRight.x)
		vertical = true;
	else if (a_pointLeft.y == a_pointRight.y)
		horizontal = true;
	
	if (!vertical && !horizontal)	//if none are true return, in future add throw
		return false;
	
	auto l = (vertical) ? a_pointRight.y - a_pointLeft.y : a_pointRight.x - a_pointLeft.x;	//mesuring lenght of edge
	
	auto p = l / 4;					//cut lenght of edge into 5 parts 
	for (int i = 0; i < 5; i++) {
		auto x = (vertical) ? a_pointLeft.x : i * p + (a_pointLeft.x + 1);
		auto y = (horizontal) ? a_pointLeft.y : i * p + (a_pointLeft.y + 1);
		if (i == 4) {
			if (horizontal)
				x = x - 2;
			else
				y = y - 2;
		}
		for (Object* o : currentStage->TileGrid.SolidObjects) {
			if (o->getHitboxWorldRect().contains(sf::Vector2f(x, y))) {
				return true;
			}
		}
	}
	return false;
}

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void GameState::setActivePlayer(Player* a_player)
{
	if(a_player == nullptr)
		if(currentStage->TileGrid.PlayerObjStorageVec.size())
			ActivePlayer = currentStage->TileGrid.PlayerObjStorageVec.front();
}

void GameState::playerControl()
{
	auto plPos = ActivePlayer->GetObjectGridPosition();
	auto plBoxPos = ActivePlayer->getSpriteBoundariesPos(true);
	if (freeCamEnable)
		return;
	if (ActivePlayer == nullptr)
		return;
	if (Keyboard::checkKeyState(sf::Keyboard::Up) == Keyboard::KeyState::hold) {
		if(canEnterTile(ActivePlayer, Directions::up))
			if (!checkCollision(ActivePlayer->getHitboxVerticles().topLeft, ActivePlayer->getHitboxVerticles().topRight)) {
				currentStage->TileGrid.MoveObject(sf::Vector2f(0, -1), ActivePlayer);
			}
	}
	else if (Keyboard::checkKeyState(sf::Keyboard::Down) == Keyboard::KeyState::hold) {
		if (canEnterTile(ActivePlayer, Directions::down))
			if (!checkCollision(ActivePlayer->getHitboxVerticles().downLeft, ActivePlayer->getHitboxVerticles().downRight)) {
				currentStage->TileGrid.MoveObject(sf::Vector2f(0, 1), ActivePlayer);
			}
	}

	if (Keyboard::checkKeyState(sf::Keyboard::Left) == Keyboard::KeyState::hold) {
		if (canEnterTile(ActivePlayer, Directions::left))
			if (!checkCollision(ActivePlayer->getHitboxVerticles().topLeft, ActivePlayer->getHitboxVerticles().downLeft))
				currentStage->TileGrid.MoveObject(sf::Vector2f(-1, 0), ActivePlayer);
	}
	else if (Keyboard::checkKeyState(sf::Keyboard::Right) == Keyboard::KeyState::hold) {
		if (canEnterTile(ActivePlayer, Directions::right))
			if (!checkCollision(ActivePlayer->getHitboxVerticles().topRight, ActivePlayer->getHitboxVerticles().downRight))
				currentStage->TileGrid.MoveObject(sf::Vector2f(1, 0), ActivePlayer);
	}
	cameraFollowObject(ActivePlayer, sf::FloatRect(440, 350, 900, 1100));
}

void GameState::Update(sf::Vector2i* a_mousePos, sf::Vector2f* a_mousePosOnCoords)
{
	//if (MainDimmer != nullptr) {
	//	if (MainDimmer->getMode() != Dimmer::EMode::none)
	//		return;
	//}
	updateOpenedWindowIt();

	std::multimap<std::string, Button>::iterator it = Windows.begin()->Buttons.begin();
	for (it = Windows.begin()->Buttons.begin(); it != Windows.begin()->Buttons.end(); ++it) {
		ButtonFunctions(it);
	}
	switchCameraMode();
	cameraMovementSetup();
	
	playerControl();

	createQuitDial();
	currentStage->Update(a_mousePos);
	//std::cout << "== GAMESTATE == Update Func" << std::endl;
}

void GameState::Render(sf::RenderTarget* a_target)
{
	currentStage->Render(a_target);
	//std::cout << "== GAMESTATE == Render Func" << std::endl;
}
