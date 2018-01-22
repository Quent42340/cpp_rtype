/*
 * =====================================================================================
 *
 *       Filename:  SpriteComponent.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 20:02:22
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SPRITECOMPONENT_HPP_
#define SPRITECOMPONENT_HPP_

#include <string>

#include "IntTypes.hpp"

class SpriteComponent {
	public:
		SpriteComponent(const std::string &textureName, u16 frameWidth = 0, u16 frameHeight = 0, u16 initialFrame = 0)
			: m_textureName(textureName), m_frameWidth(frameWidth), m_frameHeight(frameHeight), m_initialFrame(initialFrame) {}

		const std::string &textureName() const { return m_textureName; }

		u16 frameWidth() const { return m_frameWidth; }
		u16 frameHeight() const { return m_frameHeight; }

		u16 initialFrame() const { return m_initialFrame; }

	private:
		std::string m_textureName;

		u16 m_frameWidth;
		u16 m_frameHeight;

		u16 m_initialFrame;
};

#endif // SPRITECOMPONENT_HPP_
