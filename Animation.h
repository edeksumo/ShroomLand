#pragma once
#include "DataMenager.h"
#include <SFML/Graphics.hpp>

class Animation
{
public:
	enum class repeatMode {
		once,
		circle
	};
public:
	enum class Direction {
		down,
		up,
		left,
		right
	};
private:
	string name;
	string animationFamilyName;
	sf::Texture* texture;
	sf::Texture defTexture;
	std::vector<sf::IntRect> frames;
	repeatMode animMode;
	sf::Sprite* spritePtr;
	DataMenager* dataMenager;

	unsigned int frameInterval;
	unsigned int timer;
	unsigned int currentFrame;

	bool restartAnimation;
	bool ended;

	void cutTextureIntoFrames(sf::Vector2f a_textuteOffset, size_t a_nbOfFr, sf::Vector2i a_sizeOfFrame, sf::Vector2i a_spriteSheetSize, bool a_fliped, bool a_upsideDown);
	void setAnimationSpeed(float a_speed);
protected:

public:
	Animation() {
		name = "none";
		animationFamilyName = "none";
		texture = nullptr;
		//defTexture = nullptr;
		animMode = repeatMode::once;
		spritePtr = nullptr;
		dataMenager = nullptr;

		frameInterval = 100;
		timer = 0;
		currentFrame = 0;

		restartAnimation = true;
		ended = false;
	}
	Animation(string m_name, sf::Texture* m_texture, sf::Vector2f m_textureOffset, size_t m_nbOfFrames, float m_speed, sf::Vector2i m_sizeOfFrame/*size in pixels*/, sf::Vector2i m_spriteSheetSize /*size in frames*/, repeatMode m_mode, sf::Sprite* m_sprite, sf::Texture m_defTexture /*texture of original sprite*/, bool m_fliped, bool m_upsideDown, DataMenager* m_dM) {
		name = m_name;
		texture = m_texture;
		defTexture = m_defTexture;
		animMode = m_mode;
		spritePtr = m_sprite;
		dataMenager = m_dM;

		timer = 0;
		currentFrame = 0;

		restartAnimation = true;
		ended = false;

		cutTextureIntoFrames(m_textureOffset, m_nbOfFrames, m_sizeOfFrame, m_spriteSheetSize, m_fliped, m_upsideDown);
		setAnimationSpeed(m_speed);
	}
	void setSpritePointer(sf::Sprite* a_sprPtr);
	void setAnimationFamilyName(string a_name);
	string getAnimationFamilyname();
	string GetName();
	bool isEnded();
	void Play();
	void Stop();
};