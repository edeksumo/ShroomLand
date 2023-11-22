#include "Animation.h"

/****************************************************/
//Private
/****************************************************/
void Animation::cutTextureIntoFrames(size_t a_nbOfFr, sf::Vector2i a_sizeOfFrame, sf::Vector2i a_spriteSheetSize, bool a_fliped, bool a_upsideDown)
{
	int flip_01 = (a_fliped) ? 1 : 0;
	int flip_02 = (a_fliped) ? -1 : 1;
	int down_01 = (a_upsideDown) ? 1 : 0;
	int down_02 = (a_upsideDown) ? -1 : 1;
	frames.resize(a_nbOfFr);
	unsigned int currentFrame = 0;
	for (int i = 0; i < a_spriteSheetSize.x; i++) {
		for (int j = 0; j < a_spriteSheetSize.y; j++) {
			frames[currentFrame] = sf::IntRect((j + flip_01) * a_sizeOfFrame.x, (i + down_01) * a_sizeOfFrame.y, flip_02 * a_sizeOfFrame.x, down_02 *a_sizeOfFrame.y);
			currentFrame++;
			if (currentFrame > a_nbOfFr)
				break;
		}
	}
}
void Animation::setAnimationSpeed(float a_speed)
{
	frameInterval = 100 * a_speed;
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
void Animation::setSpritePointer(sf::Sprite* a_sprPtr)
{
	spritePtr = a_sprPtr;
}

void Animation::Play()
{
	if (restartAnimation) {
		currentFrame = 0;
		restartAnimation = false;
		spritePtr->setTexture(*texture);
		spritePtr->setTextureRect(frames[currentFrame]);
	}

	timer++;
	if (timer >= frameInterval) {
		timer = 0;
		currentFrame++;
		if (currentFrame > frames.size() - 1) {
			if (animMode == Animation::repeatMode::once) {
				spritePtr->setTexture(defTexture);
				currentFrame = frames.size();
				return;
			}
			else {
				currentFrame = 0;
			}
		}
		spritePtr->setTexture(*texture);
		spritePtr->setTextureRect(frames[currentFrame]);
	}
}

void Animation::Stop()
{
	currentFrame = 0;
	restartAnimation = true;
	timer = 0;
}
