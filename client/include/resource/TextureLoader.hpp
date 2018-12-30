/*
 * =====================================================================================
 *
 *       Filename:  TextureLoader.hpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:49:40
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TEXTURELOADER_HPP_
#define TEXTURELOADER_HPP_

#include <gk/resource/IResourceLoader.hpp>

class TextureLoader : public gk::IResourceLoader {
	public:
		void load(const char *xmlFilename, gk::ResourceHandler &handler) override;
};

#endif // TEXTURELOADER_HPP_
