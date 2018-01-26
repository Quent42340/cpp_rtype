/*
 * =====================================================================================
 *
 *       Filename:  SpriteLoader.hpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 03:45:59
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SPRITELOADER_HPP_
#define SPRITELOADER_HPP_

#include "ResourceLoader.hpp"

class SpriteLoader : public ResourceLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler);
};

#endif // SPRITELOADER_HPP_
