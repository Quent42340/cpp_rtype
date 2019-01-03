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

#include <gk/core/IntTypes.hpp>

class SpriteComponent {
	public:
		SpriteComponent(const std::string &textureName)
			: m_textureName(textureName) {}

		const std::string &textureName() const { return m_textureName; }

	private:
		std::string m_textureName;
};

#endif // SPRITECOMPONENT_HPP_
