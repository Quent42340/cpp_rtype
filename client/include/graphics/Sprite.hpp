/*
 * =====================================================================================
 *
 *       Filename:  Sprite.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:48:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "Image.hpp"

class Sprite : public Image {
	public:
		Sprite(const std::string &textureName, u16 frameWidth, u16 frameHeight);

		u16 currentFrame() const { return m_currentFrame; }

		u16 frameWidth() const { return m_frameWidth; }
		u16 frameHeight() const { return m_frameHeight; }

		void setCurrentFrame(u16 currentFrame);

	private:
		u16 m_currentFrame;

		u16 m_frameWidth;
		u16 m_frameHeight;
};

#endif // SPRITE_HPP_
