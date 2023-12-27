#pragma once
#include"Grid.h"
#include "ObjectMenager.h"
class Stage
{
public:
	enum class EState {
		none = -1,
		mainMenuState = 0,
		gameState,
		editorState
	};
private:
	ObjectMenager* p_objMenager;
	sf::RenderTarget* p_renderTarget;
	DataMenager* p_dM;

	EState currentState;
	bool changeStage;
	string nextStageName;
protected:

public:
	std::vector<Tile> BackGroundTiles;

	std::string Name;
	Grid TileGrid;

	Stage() {
		p_objMenager = nullptr;
		p_renderTarget = nullptr;
		p_dM = nullptr;
		changeStage = false;
		nextStageName = "";
		currentState = Stage::EState::none;
	}

	Stage(ObjectMenager* m_objMenager, std::string m_name, DataMenager* m_dM) {
		p_objMenager = m_objMenager;
		p_dM = m_dM;
		p_renderTarget = nullptr;
		Name = m_name;
		changeStage = false;
		nextStageName = "";
		currentState = Stage::EState::none;
	}

	Stage(const Stage& p1) {
		p_objMenager = p1.p_objMenager;
		p_dM = p1.p_dM;
		p_renderTarget = p1.p_renderTarget;
		Name = p1.Name;
		changeStage = p1.changeStage;
		currentState = p1.currentState;
		TileGrid = p1.TileGrid;
		BackGroundTiles = p1.BackGroundTiles;

		TileGrid.SolidObjects.clear();
		TileGrid.CollisionObjects.clear();
		TileGrid.RenderEditorObjPtrVec.clear();
		TileGrid.RenderObjPtrVec.clear();
		TileGrid.StaticObjStorageVec.clear();
		TileGrid.InteractableObjStorageVec.clear();
		TileGrid.PlayerObjStorageVec.clear();
		TileGrid.SpecialObjStorageVec.clear();

		for (auto i : p1.TileGrid.StaticObjStorageVec) {
			addObject(i->GetPosition(), i->ID);
		}
		for (auto i : p1.TileGrid.InteractableObjStorageVec) {
			addObject(i->GetPosition(), i->ID);
		}
		for (auto i : p1.TileGrid.PlayerObjStorageVec) {
			addObject(i->GetPosition(), i->ID);
		}
		for (auto i : p1.TileGrid.SpecialObjStorageVec) {
			addObject(i->GetPosition(), i->ID, i->getProperties());
		}
	}

	bool isVisible(const Sprite& a_sprite, sf::RenderTarget* a_target);
	void addTile(GridCell a_pos, unsigned int a_ID);	
	void addObject(sf::Vector2f a_pos, unsigned int a_ID, string a_properties = "");
	void fillDeque(GridCell a_pos, unsigned int a_ID, unsigned int a_vatiant);
	void addBackgroundTile(GridCell a_pos, unsigned int a_ID);
	Tile* getPrefTilePtr(int a_ID);
	Object* getPrefObjPtr(int a_ID);

	void setCurrentState(Stage::EState a_state);
	Stage::EState GetStateType();

	bool ChangeStage();
	void SetChangeStage(bool a);
	string GetNextStageName();

	void Update(sf::Vector2i* a_mousePos);
	void Render(sf::RenderTarget* a_target);
};

