#pragma once
#include "Animation4D.h"
#include <deque>

class AnimationMenager
{
private:
	DataMenager* p_dM;
protected:

public:
	AnimationMenager() {
		p_dM = nullptr;
	}
	AnimationMenager(DataMenager* m_dM) {
		p_dM = m_dM;
	}

	std::map<string, Animation> AnimationMap;
	std::deque<Animation> AnimationDeque;

	std::map<string, Animation4D> Animation4DMap;

	void CreateAnimation(string a_name, sf::Texture* a_texture, sf::Vector2f a_textureOffset, size_t a_nbOfFrames, float a_speed, sf::Vector2i a_sizeOfFrame/*size in pixels*/, sf::Vector2i a_spriteSheetSize /*size in frames*/,
		Animation::repeatMode a_mode, sf::Sprite* a_sprite, sf::Texture a_defTexture /*texture of original sprite*/, bool a_fliped, bool a_upsideDown);
	void CreateAnimation4D(string a_name, Animation* m_up, Animation* m_down, Animation* m_left, Animation* m_right);
	void SetAnimationSprite(string a_name, sf::Sprite* a_sprite);
	string GetCurrentAnimationName();
	Animation* GetAnimationPtr(string a_name);
	void PlayAnimation(string a_name);
	void PlayAnimation(string a_name, Animation::Direction a_direction);
	void StopPlayedAnimation();
	void UpdateAnimation();
};

