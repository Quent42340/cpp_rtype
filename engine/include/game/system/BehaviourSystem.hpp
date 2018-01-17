/*
 * =====================================================================================
 *
 *       Filename:  BehaviourSystem.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:45:35
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef BEHAVIOURSYSTEM_HPP_
#define BEHAVIOURSYSTEM_HPP_

#include "SceneObject.hpp"

class BehaviourSystem {
	public:
		static void process(SceneObject &object);
};

#endif // BEHAVIOURSYSTEM_HPP_
