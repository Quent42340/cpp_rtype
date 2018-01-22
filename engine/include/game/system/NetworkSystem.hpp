/*
 * =====================================================================================
 *
 *       Filename:  NetworkSystem.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 16:45:49
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORKSYSTEM_HPP_
#define NETWORKSYSTEM_HPP_

#include "SceneObject.hpp"

class NetworkSystem {
	public:
		static void process(SceneObject &object);
};

#endif // NETWORKSYSTEM_HPP_
