#include "ObjectMenager.h"
/****************************************************/
//Private
/****************************************************/
void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5])
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			auto b = DEFAULT_MASK_FOR_BACKGROUND[Tile::g_lastID] + 1;
			//std::cout << Tile::g_lastID << " " << b << std::endl;
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), true, b, 0, p_dM);
			//std::cout << Tile::g_lastID  << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
	}
}

void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5], bool a_isTilable, bool a_needBackgroundTile, unsigned int a_nbOfVariants)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), a_isTilable, a_needBackgroundTile, a_nbOfVariants, p_dM);
			//std::cout << j * 32 << " " << i * 32 << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
	}
}

void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[5][7], bool a_isTilable, bool a_needBackgroundTile, unsigned int a_nbOfVariants)
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 5; j++) {
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), a_isTilable, a_needBackgroundTile, a_nbOfVariants, p_dM);
			//std::cout << j * 32 << " " << i * 32 << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
		
	}
}

void ObjectMenager::addPrefab(int a_ID, Object* a_obj)
{
	ObjectsPrefabs.insert(std::pair<int, Object*>(a_ID, a_obj));
}

void ObjectMenager::createStaticObjPrefab(sf::Texture* a_texture, StaticObject* a_staticObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox)
{
	a_staticObjPtr = new StaticObject(a_texture, m_area, true, m_hitbox, p_dM);
	//std::cout << a_staticObjPtr->ID << std::endl;
	StaticObjectPtrContainer.insert(std::pair<int, StaticObject*>(a_staticObjPtr->ID, a_staticObjPtr));
	auto o = StaticObjectPtrContainer.find(a_staticObjPtr->ID);
	addPrefab(a_staticObjPtr->ID, o->second);
}

void ObjectMenager::createInteractableObjPrefab(sf::Texture* a_texture, InteractableObject* a_intractableObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox)
{
	a_intractableObjPtr = new InteractableObject(a_texture, m_area, true, m_hitbox, p_dM);
	//std::cout << a_intractableObjPtr->ID << std::endl;
	InteractableObjectPtrContainer.insert(std::pair<int, InteractableObject*>(a_intractableObjPtr->ID, a_intractableObjPtr));
	auto o = InteractableObjectPtrContainer.find(a_intractableObjPtr->ID);
	addPrefab(a_intractableObjPtr->ID, o->second);
}

void ObjectMenager::createPlayerObjPrefab(sf::Texture* a_texture, Player* a_playerObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox)
{
	a_playerObjPtr = new Player(a_texture, m_area, true, m_hitbox, p_dM);
	//std::cout << a_intractableObjPtr->ID << std::endl;
	PlayerObjectPtrContainer.insert(std::pair<int, Player*>(a_playerObjPtr->ID, a_playerObjPtr));
	auto o = PlayerObjectPtrContainer.find(a_playerObjPtr->ID);
	addPrefab(a_playerObjPtr->ID, o->second);
}

Tile* ObjectMenager::getTilePtrById(int a_ID)
{
	std::cout << "2";
	//std::multimap<int, Tile*>::iterator it = TilePtrContainer.find(a_ID);
	//std::cout << "2";
	return TilePtrContainer.find(a_ID)->second;
}

Object* ObjectMenager::getObjectPtrById(int a_ID)
{
	return StaticObjectPtrContainer.find(a_ID)->second;
}

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
