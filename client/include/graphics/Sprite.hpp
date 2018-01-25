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
#include "SpriteAnimation.hpp"

class Sprite : public Image {
	public:
		Sprite(const std::string &textureName, u16 frameWidth, u16 frameHeight);

		void updateAnimations();

		void addAnimation(const SpriteAnimation &animation) { m_animations.emplace_back(animation); }

		u16 currentFrame() const { return m_currentFrame; }

		u16 frameWidth() const { return m_frameWidth; }
		u16 frameHeight() const { return m_frameHeight; }

		void setCurrentFrame(u16 currentFrame);
		void setCurrentAnimation(u16 currentAnimation);

	private:
		std::vector<SpriteAnimation> m_animations;

		u16 m_currentFrame = 0;
		u16 m_currentAnimation = 0;
		u16 m_previousAnimation = 0;

		u16 m_frameWidth = 0;
		u16 m_frameHeight = 0;
};

#endif // SPRITE_HPP_
