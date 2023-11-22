#include "AnimationMenager.h"
/****************************************************/
//Private
/****************************************************/

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void AnimationMenager::CreateAnimation(string a_name, sf::Texture* a_texture, size_t a_nbOfFrames, float a_speed, sf::Vector2i a_sizeOfFrame, sf::Vector2i a_spriteSheetSize,
	Animation::repeatMode a_mode, sf::Sprite* a_sprite, sf::Texture a_defTexture, bool a_fliped, bool a_upsideDown)
{
	AnimationMap.emplace(a_name, Animation(a_name, a_texture, a_nbOfFrames, a_speed, a_sizeOfFrame, a_spriteSheetSize, a_mode, a_sprite, a_defTexture, a_fliped , a_upsideDown, p_dM));
}

void AnimationMenager::SetAnimationSprite(string a_name, sf::Sprite* a_sprite)
{
	if (AnimationMap.find(a_name) == AnimationMap.end()) {
		std::cout << "There is no such animation in Animation Menager: " << a_name << endl;
		return;
	}
	AnimationMap.find(a_name)->second.setSpritePointer(a_sprite);
}

void AnimationMenager::PlayAnimation(string a_name)
{
	if (AnimationMap.find(a_name) == AnimationMap.end()) {
		std::cout << "There is no such animation in Animation Menager: " << a_name << endl;
		return;
	}
	if (AnimationDeque.size())
		AnimationDeque.front().Stop();
	auto animIt = AnimationMap.find(a_name);
	auto& anim = animIt->second;
	AnimationDeque.push_front(anim);
}

void AnimationMenager::UpdateAnimation()
{
	if (!AnimationDeque.size())
		return;
	AnimationDeque.front().Play();
}
