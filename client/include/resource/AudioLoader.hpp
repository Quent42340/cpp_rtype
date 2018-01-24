/*
 * =====================================================================================
 *
 *       Filename:  AudioLoader.hpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 21:32:56
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef AUDIOLOADER_HPP_
#define AUDIOLOADER_HPP_

#include "ResourceLoader.hpp"

class AudioLoader : public ResourceLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler);
};

#endif // AUDIOLOADER_HPP_
