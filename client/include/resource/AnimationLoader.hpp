/*
 * =====================================================================================
 *
 *       Filename:  AnimationLoader.hpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 03:45:59
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef ANIMATIONLOADER_HPP_
#define ANIMATIONLOADER_HPP_

#include "ResourceLoader.hpp"

class AnimationLoader : public ResourceLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler);
};

#endif // ANIMATIONLOADER_HPP_
