/*
 * =====================================================================================
 *
 *       Filename:  EnemyInfoLoader.hpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 08:08:23
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef ENEMYINFOLOADER_HPP_
#define ENEMYINFOLOADER_HPP_

#include <gk/resource/IResourceLoader.hpp>

class EnemyInfoLoader : public gk::IResourceLoader {
	public:
		void load(const char *xmlFilename, gk::ResourceHandler &handler);
};

#endif // ENEMYINFOLOADER_HPP_
