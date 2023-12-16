#include "ObjectMenager.h"
/****************************************************/
//Private
/****************************************************/
Sprite* ObjectMenager::GetLastIDSpritePtr()
{
	/// //////////////////////////////////////
	/// all subobject classes should be added here when they want to be animated
	/// //////////////////////////////////////

	if (StaticObjectPtrContainer.find(Sprite::LAST_ID) != StaticObjectPtrContainer.end()) {
		std::cout << "Animation Created for static Object" << endl;
		return StaticObjectPtrContainer.find(Sprite::LAST_ID)->second;
	}
	else if (InteractableObjectPtrContainer.find(Sprite::LAST_ID) != InteractableObjectPtrContainer.end()) {
		std::cout << "Animation Created for interactable Object" << endl;
		return InteractableObjectPtrContainer.find(Sprite::LAST_ID)->second;

	}
	else if (PlayerObjectPtrContainer.find(Sprite::LAST_ID) != PlayerObjectPtrContainer.end()) {
		std::cout << "Animation Created for player Object" << endl;
		return PlayerObjectPtrContainer.find(Sprite::LAST_ID)->second;
	}
	else {
		//add some throw later
		std::cout << "Some random Error with object LASTID\n";
		return nullptr;
	}
}
void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5])
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			auto b = DEFAULT_MASK_FOR_BACKGROUND[Tile::g_lastID] + 1;
			//std::cout << Tile::g_lastID << " " << b << std::endl;
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), true, true, b, 0, p_dM);
			//std::cout << Tile::g_lastID  << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
	}
}

void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[11][5], bool a_isTilable, bool a_isWalkable, bool a_needBackgroundTile, unsigned int a_nbOfVariants)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), a_isTilable, a_isWalkable, a_needBackgroundTile, a_nbOfVariants, p_dM);
			//std::cout << j * 32 << " " << i * 32 << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
	}
}

void ObjectMenager::tilesetPrefabCreater(sf::Texture* a_texture, Tile* a_objArrPtr[5][7], bool a_isTilable, bool a_isWalkable, bool a_needBackgroundTile, unsigned int a_nbOfVariants)
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 5; j++) {
			a_objArrPtr[j][i] = new Tile(a_texture, sf::IntRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE), a_isTilable, a_isWalkable, a_needBackgroundTile, a_nbOfVariants, p_dM);
			//std::cout << j * 32 << " " << i * 32 << std::endl;
			TilePtrContainer.insert(std::pair<int, Tile*>(a_objArrPtr[j][i]->ID, a_objArrPtr[j][i]));
		}
		
	}
}

void ObjectMenager::addPrefab(int a_ID, Object* a_obj)
{
	ObjectsPrefabs.insert(std::pair<int, Object*>(a_ID, a_obj));
}

void ObjectMenager::createStaticObjPrefab(sf::Texture* a_texture, StaticObject* a_staticObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool a_isAnimated)
{
	a_staticObjPtr = new StaticObject(a_texture, m_area, m_solid, m_hitbox, a_isAnimated, p_dM);
	//std::cout << a_staticObjPtr->ID << std::endl;
	StaticObjectPtrContainer.insert(std::pair<int, StaticObject*>(a_staticObjPtr->ID, a_staticObjPtr));
	auto o = StaticObjectPtrContainer.find(a_staticObjPtr->ID);
	addPrefab(a_staticObjPtr->ID, o->second);
}

void ObjectMenager::createInteractableObjPrefab(sf::Texture* a_texture, InteractableObject* a_intractableObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool a_isAnimated)
{
	a_intractableObjPtr = new InteractableObject(a_texture, m_area, m_solid, m_hitbox, a_isAnimated, p_dM);
	//std::cout << a_intractableObjPtr->ID << std::endl;
	InteractableObjectPtrContainer.insert(std::pair<int, InteractableObject*>(a_intractableObjPtr->ID, a_intractableObjPtr));
	auto o = InteractableObjectPtrContainer.find(a_intractableObjPtr->ID);
	addPrefab(a_intractableObjPtr->ID, o->second);
}

void ObjectMenager::createPlayerObjPrefab(sf::Texture* a_texture, Player* a_playerObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool a_isAnimated)
{
	a_playerObjPtr = new Player(a_texture, m_area, m_solid, m_hitbox, a_isAnimated, p_dM);
	//std::cout << a_intractableObjPtr->ID << std::endl;
	PlayerObjectPtrContainer.insert(std::pair<int, Player*>(a_playerObjPtr->ID, a_playerObjPtr));
	auto o = PlayerObjectPtrContainer.find(a_playerObjPtr->ID);
	addPrefab(a_playerObjPtr->ID, o->second);
}

void ObjectMenager::createSpecialObjPrefab(sf::Texture* a_texture, SpecialObject* a_specialObjPtr, sf::IntRect m_area, bool m_solid, sf::IntRect m_hitbox, bool a_isAnimated, SpecialObject::SpecialType a_subType)
{
	a_specialObjPtr = new SpecialObject(a_texture, m_area, m_solid, m_hitbox, a_isAnimated, a_subType, p_dM);
	//std::cout << a_intractableObjPtr->ID << std::endl;
	SpecialObjectPtrContainer.insert(std::pair<int, SpecialObject*>(a_specialObjPtr->ID, a_specialObjPtr));
	auto o = SpecialObjectPtrContainer.find(a_specialObjPtr->ID);
	addSpecialObjectID(a_specialObjPtr->ID);
	addPrefab(a_specialObjPtr->ID, o->second);
}

void ObjectMenager::addAnimationToLastPrefab(string a_name, sf::Texture* a_texture, sf::Vector2f a_textureOffset, size_t a_nbOfFrames, float a_speed, sf::Vector2i a_sizeOfFrame, sf::Vector2i a_spriteSheetSize, Animation::repeatMode a_mode, sf::Sprite* a_sprite, sf::Texture a_defTexture, bool a_fliped, bool a_upsideDown)
{
	Sprite* sprite = GetLastIDSpritePtr();
	if (sprite == nullptr) {
		std::cout << "Sometging went wrong";
		return;
	}

	sprite->GetAnimationMenager()->CreateAnimation(a_name, a_texture, a_textureOffset, a_nbOfFrames, a_speed, a_sizeOfFrame, a_spriteSheetSize, a_mode, a_sprite, a_defTexture, a_fliped, a_upsideDown);
}

void ObjectMenager::createAnimation4DToLastPrefab(string a_name, string a_upFacingAnim, string a_downFacingAni, string a_leftFacingAnim, string a_rightFacingAnim)
{
	Sprite* sprite = GetLastIDSpritePtr();
	if (sprite == nullptr) {
		std::cout << "Sometging went wrong";
		return;
	}
	AnimationMenager* aMg = sprite->GetAnimationMenager();
	aMg->GetAnimationPtr(a_upFacingAnim)->setAnimationFamilyName(a_name);
	aMg->GetAnimationPtr(a_downFacingAni)->setAnimationFamilyName(a_name);
	aMg->GetAnimationPtr(a_leftFacingAnim)->setAnimationFamilyName(a_name);
	aMg->GetAnimationPtr(a_rightFacingAnim)->setAnimationFamilyName(a_name);
	sprite->GetAnimationMenager()->CreateAnimation4D(a_name, aMg->GetAnimationPtr(a_upFacingAnim), aMg->GetAnimationPtr(a_downFacingAni), aMg->GetAnimationPtr(a_leftFacingAnim), aMg->GetAnimationPtr(a_rightFacingAnim));
}

void ObjectMenager::addSpecialObjectID(unsigned int a_ID)
{
	SpecialObjectsIDs.push_back(a_ID);
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
bool ObjectMenager::IsIDSpecial(unsigned int a_ID)
{
	for (const auto& i : SpecialObjectsIDs) {
		if (i == a_ID)
			return true;
	}
	return false;
}