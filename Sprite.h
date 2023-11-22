#pragma once
#include "GridCell.h"
#include "AnimationMenager.h"

const int MAX_IDIES_FOR_TILES = 55; //taken from ObjectMenager.h size of arr
const int TILE_SIZE = 32;			//in pixels
const bool DEFAULT_MASK_FOR_BACKGROUND[MAX_IDIES_FOR_TILES] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
																1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
																1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
																1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
																1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 };		//premade bitmask for all tilesets

class Sprite
{
private:

	sf::Vector2f hitboxPos;

	void setSpriteForAnimations();
protected:
	sf::RectangleShape hitbox;
	DataMenager* p_dM;
	AnimationMenager* AnimMenager;
	bool hasHitbox;
	bool isAnimated;
public:
	struct Verticles {
		sf::Vector2f topLeft;
		sf::Vector2f topRight;
		sf::Vector2f downLeft;
		sf::Vector2f downRight;
	};
	unsigned int ID;
	sf::Sprite sprite;
	GridCell posOnGrid;
	static unsigned int ID_COUNTER;
	static unsigned int LAST_ID;
		
	Sprite() {
		p_dM = nullptr;
		AnimMenager = nullptr;
		//static unsigned int ID_COUNTER;
		ID = ID_COUNTER++;
		LAST_ID = ID;
		posOnGrid = GridCell(0, 0);
		hasHitbox = false;
		isAnimated = false;
		//std::cout << "sprite constructor " << ID << endl;
	};

	Sprite(sf::IntRect m_hitboxPos, DataMenager* m_dM) {
		p_dM = m_dM;
		AnimMenager = new AnimationMenager(p_dM);
		setSpriteForAnimations();
		isAnimated = false;
		//static unsigned int ID_COUNTER;
		ID = ID_COUNTER++;
		LAST_ID = ID;
		posOnGrid = GridCell(0, 0);
		hasHitbox = true;
		hitboxPos = sf::Vector2f(m_hitboxPos.left, m_hitboxPos.top);
		//std::cout << "sprite constructor " << ID << endl;
	};

	Sprite(const Sprite& p1) {
		ID = p1.ID;
		p_dM = p1.p_dM;
		AnimMenager = p1.AnimMenager;
		setSpriteForAnimations();
		posOnGrid = p1.posOnGrid;
		hasHitbox = p1.hasHitbox;
		hitboxPos = p1.hitboxPos;
		isAnimated = p1.isAnimated;
		//std::cout << "sprite copy constructor " << ID << endl;
	};
	~Sprite() {
		delete AnimMenager;
	};
	sf::Vector2f GetPosition();
	void SetPosition(GridCell a_pos);	//sets position on grid and multiplias it by 32 for in game pos DO NOT UPDATE RENDER ORDER
	void SetPosition(sf::Vector2f a_pos);	//sets position in pixels DO NOT UPDATE RENDER ORDER
	void MoveSprite(sf::Vector2f a_pos);	//moves position in pixels	DO NOT UPDATE RENDER ORDER
	void flipSprite();
	GridCell GetGridPosition();
	GridCell GetObjectGridPosition();
	AnimationMenager* GetAnimationMenager();
	sf::FloatRect getHitboxWorldRect();
	sf::FloatRect getSpriteBoundariesPos(bool a_intoGrid = false);
	Verticles getHitboxVerticles();
	virtual void Update(sf::Vector2i* a_mousePos) = 0;
	void Render(sf::RenderTarget* a_target);
};

