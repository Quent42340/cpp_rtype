/*
 * =====================================================================================
 *
 *       Filename:  Sprite.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:48:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Sprite.hpp"

Sprite::Sprite(const std::string &textureName, u16 frameWidth, u16 frameHeight) : Image(textureName) {
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;

	setPosRect(0, 0, frameWidth, frameHeight);
}

void Sprite::setCurrentFrame(u16 currentFrame) {
	u16 frameX = (currentFrame % (width() / m_frameWidth)) * m_frameWidth;
	u16 frameY = (currentFrame / (width() / m_frameWidth)) * m_frameHeight;

	setClipRect(frameX, frameY, m_frameWidth, m_frameHeight);

	m_currentFrame = currentFrame;
}

