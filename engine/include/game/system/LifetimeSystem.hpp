/*
 * =====================================================================================
 *
 *       Filename:  LifetimeSystem.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 04:14:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef LIFETIMESYSTEM_HPP_
#define LIFETIMESYSTEM_HPP_

#include "SceneObjectList.hpp"

class LifetimeSystem {
	public:
		static void process(SceneObjectList &objects);
};

#endif // LIFETIMESYSTEM_HPP_
