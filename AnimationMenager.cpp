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

void AnimationMenager::CreateAnimation(string a_name, sf::Texture* a_texture, sf::Vector2f a_textureOffset, size_t a_nbOfFrames, float a_speed, sf::Vector2i a_sizeOfFrame, sf::Vector2i a_spriteSheetSize,
	Animation::repeatMode a_mode, sf::Sprite* a_sprite, sf::Texture a_defTexture, bool a_fliped, bool a_upsideDown)
{
	AnimationMap.emplace(a_name, Animation(a_name, a_texture, a_textureOffset, a_nbOfFrames, a_speed, a_sizeOfFrame, a_spriteSheetSize, a_mode, a_sprite, a_defTexture, a_fliped , a_upsideDown, p_dM));
}

void AnimationMenager::CreateAnimation4D(string a_name, Animation* m_up, Animation* m_down, Animation* m_left, Animation* m_right)
{
	Animation4DMap.emplace(a_name, Animation4D(a_name, m_up, m_down, m_left, m_right));
}

void AnimationMenager::SetAnimationSprite(string a_name, sf::Sprite* a_sprite)
{
	if (AnimationMap.find(a_name) == AnimationMap.end()) {
		std::cout << "There is no such animation in Animation Menager: " << a_name << endl;
		return;
	}
	AnimationMap.find(a_name)->second.setSpritePointer(a_sprite);
}

string AnimationMenager::GetCurrentAnimationName()
{
	return AnimationDeque.front().GetName();
}

Animation* AnimationMenager::GetAnimationPtr(string a_name)
{
	if (AnimationMap.find(a_name) == AnimationMap.end()) {
		std::cout << "There is no such animation in Animation Menager: " << a_name << endl;
		return nullptr;
	}
	return &AnimationMap.find(a_name)->second;
}

void AnimationMenager::PlayAnimation(string a_name)
{
	if (AnimationMap.find(a_name) == AnimationMap.end()) {
		std::cout << "There is no such animation in Animation Menager: " << a_name << endl;
		return;
	}
	if (AnimationDeque.size() && AnimationDeque.front().GetName() == a_name)
		return;
	if (AnimationDeque.size())
		AnimationDeque.front().Stop();
	auto animIt = AnimationMap.find(a_name);
	auto& anim = animIt->second;
	AnimationDeque.push_front(anim);
}

void AnimationMenager::PlayAnimation(string a_name, Animation::Direction a_direction)
{
	string animationName = "";
	if (Animation4DMap.find(a_name) == Animation4DMap.end()) {
		std::cout << "There is no such animation4D in Animation Menager: " << a_name << endl;
		return;
	}
	auto &animation4D = Animation4DMap.find(a_name)->second;
	
	animationName = animation4D.GetAnimation(a_direction)->GetName();

	PlayAnimation(animationName);
}

void AnimationMenager::StopPlayedAnimation()
{
	if (!AnimationDeque.size())
		return;
	AnimationDeque.front().Stop();
	AnimationDeque.pop_front();
}

void AnimationMenager::UpdateAnimation()
{
	if (AnimationDeque.size() && AnimationDeque.front().isEnded())
		AnimationDeque.pop_front();
	if (!AnimationDeque.size())
		return;
	AnimationDeque.front().Play();
}
