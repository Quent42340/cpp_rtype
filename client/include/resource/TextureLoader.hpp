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

#include "ResourceLoader.hpp"

class TextureLoader : public ResourceLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler);
};

#endif // TEXTURELOADER_HPP_
