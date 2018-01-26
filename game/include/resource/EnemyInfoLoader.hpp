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

#include "ResourceLoader.hpp"

class EnemyInfoLoader : public ResourceLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler);
};

#endif // ENEMYINFOLOADER_HPP_
