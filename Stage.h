#pragma once
#include"Grid.h"
#include "ObjectMenager.h"
class Stage
{
public:
	enum class EState {
		none = -1,
		mainMenuState,
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
	std::deque<Tile> BackGroundTiles;
	std::deque<Tile> DecorTiles;

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

