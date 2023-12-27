#include "Stage.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/


/****************************************************/
//Public
/****************************************************/
bool Stage::isVisible(const Sprite& a_sprite, sf::RenderTarget* a_target)
{
	if ((a_target->getView().getCenter().x - (a_target->getView().getSize().x / 2) < a_sprite.sprite.getPosition().x + 40) &&
		(a_target->getView().getCenter().x + (a_target->getView().getSize().x / 2) > a_sprite.sprite.getPosition().x)) {
		if ((a_target->getView().getCenter().y - (a_target->getView().getSize().y / 2) < a_sprite.sprite.getPosition().y + 40) &&
			(a_target->getView().getCenter().y + (a_target->getView().getSize().y / 2) > a_sprite.sprite.getPosition().y)) {
			return true;
		}
		return false;
	}
	return false;
}

void Stage::addTile(GridCell a_pos, unsigned int a_ID)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
		
	if (TileGrid.isTileOccupied(a_pos)) {
		TileGrid.RemoveTile(a_pos);
	}
	/// ////////////////////////////////////////////////////////
	TileGrid.AddTile(a_pos, it->second);
}

void Stage::addObject(sf::Vector2f a_pos, unsigned int a_ID, string a_properties)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	std::cout << a_ID << endl;
	////////////////////////////////////////////////////////
	/// searching for object by ID in corresponding multimap 
	///////////////////////////////////////////////////////
	std::multimap<int, StaticObject*>::iterator it = p_objMenager->StaticObjectPtrContainer.find(a_ID);
	if (it != p_objMenager->StaticObjectPtrContainer.end()) {
		TileGrid.AddObject(a_pos, it->second);
		return;
	}
	std::multimap<int, InteractableObject*>::iterator it_01 = p_objMenager->InteractableObjectPtrContainer.find(a_ID);
	if (it_01 != p_objMenager->InteractableObjectPtrContainer.end()) {
		TileGrid.AddObject(a_pos, it_01->second);
		return;
	}

	std::multimap<int, Player*>::iterator it_02 = p_objMenager->PlayerObjectPtrContainer.find(a_ID);
	if (it_02 != p_objMenager->PlayerObjectPtrContainer.end()) {
		TileGrid.AddObject(a_pos, it_02->second);
		return;
	}
	std::multimap<int, SpecialObject*>::iterator it_03 = p_objMenager->SpecialObjectPtrContainer.find(a_ID);
	if (it_03 != p_objMenager->SpecialObjectPtrContainer.end()) {
		TileGrid.AddObject(a_pos, it_03->second, a_properties);
		return;
	}
	
}

void Stage::fillDeque(GridCell a_pos, unsigned int a_ID, unsigned int a_vatiant)
{
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	TileGrid.AddTile(a_pos, it->second, a_vatiant);
}

void Stage::addBackgroundTile(GridCell a_pos, unsigned int a_ID)
{
	if (a_pos.x < 0 || a_pos.y < 0)
		return;
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	BackGroundTiles.push_back(*it->second);
	BackGroundTiles.back().SetPosition(a_pos);
}

Tile* Stage::getPrefTilePtr(int a_ID)
{
	std::multimap<int, Tile*>::iterator it = p_objMenager->TilePtrContainer.find(a_ID);
	return it->second;
}

Object* Stage::getPrefObjPtr(int a_ID)
{
	std::multimap<int, Object*>::iterator it = p_objMenager->ObjectsPrefabs.find(a_ID);
	return it->second;
}

void Stage::setCurrentState(Stage::EState a_state)
{
	currentState = a_state;
}

Stage::EState Stage::GetStateType()
{
	return currentState;
}

bool Stage::ChangeStage()
{
	return changeStage;
}
//Delete?
void Stage::SetChangeStage(bool a)
{
	changeStage = a;
	for (const auto& i : TileGrid.RenderEditorObjPtrVec) {
		auto SpcObj = dynamic_cast<SpecialObject*>(i);
		if (SpcObj) {
			SpcObj->changeState = a;
		}
	}
}
//
string Stage::GetNextStageName()
{
	return nextStageName;
}

void Stage::Update(sf::Vector2i* a_mousePos)
{

	for (int i = 0; i < TileGrid.GetSize().x; i++) {
		for (int j = 0; j < TileGrid.GetSize().y; j++) {
			if (TileGrid.TileGridPtr[i][j] != nullptr) {
				//if (isVisible(i, p_renderTarget))
				TileGrid.TileGridPtr[i][j]->Update(a_mousePos);
			}
		}
	}
	for (const auto& i : TileGrid.RenderEditorObjPtrVec) {
		i->Update(a_mousePos);
		auto SpcObj = dynamic_cast<SpecialObject*>(i);
		if (SpcObj) {
			if (SpcObj->changeState) {
				changeStage = true;
				nextStageName = SpcObj->getProperties();
			}
		}
	}
	for (const auto& i : TileGrid.RenderObjPtrVec) {
		i->Update(a_mousePos);
	}
}

void Stage::Render(sf::RenderTarget* a_target)
{
	//std::cout << BackGroundTiles.size() << endl;
	p_renderTarget = a_target;
	for (auto& i : BackGroundTiles) {
		//std::cout << i.GetPosition().x << " " << i.GetPosition().y << endl;
		if (isVisible(i, a_target)) {
			i.Render(a_target);
		}
	}
	for (int i = 0; i < TileGrid.GetSize().x; i++) {
		for (int j = 0; j < TileGrid.GetSize().y; j++) {
			if (TileGrid.TileGridPtr[i][j] != nullptr) {
				if(isVisible(*TileGrid.TileGridPtr[i][j], a_target))
					TileGrid.TileGridPtr[i][j]->Render(a_target);
			}
		}
	}
	
	for (const auto& i : TileGrid.RenderObjPtrVec) {
		if (currentState != Stage::EState::editorState) {
			i->RenderAnimation(a_target);
		}
		i->Render(a_target);
		if (currentState != Stage::EState::mainMenuState) {
			i->RenderHitboxes(a_target);
		}
	}

	for (const auto& i : TileGrid.RenderEditorObjPtrVec) {
		if (currentState == Stage::EState::editorState) {
			i->Render(a_target);
			i->RenderHitboxes(a_target);
		}
	}
	//std::cout << (int)currentState<< endl;
	//for (int y = 0; y < TileGrid.GetSize().y; y++) {
	//	for (int x = 0; x < TileGrid.GetSize().x; x++) {
	//		if (TileGrid.ObjGridPtr[x][y] != nullptr) {
	//			if (isVisible(*TileGrid.ObjGridPtr[x][y], a_target))
	//				TileGrid.ObjGridPtr[x][y]->Render(a_target);
	//		
	//		}
	//	}
	//}
}
