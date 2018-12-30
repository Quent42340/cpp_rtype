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

#include <gk/resource/IResourceLoader.hpp>

class SpriteLoader : public gk::IResourceLoader {
	public:
		void load(const char *xmlFilename, gk::ResourceHandler &handler) override;
};

#endif // SPRITELOADER_HPP_
