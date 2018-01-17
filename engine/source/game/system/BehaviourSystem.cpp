/*
 * =====================================================================================
 *
 *       Filename:  BehaviourSystem.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:45:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "BehaviourComponent.hpp"
#include "BehaviourSystem.hpp"

void BehaviourSystem::process(SceneObject &object) {
	if(object.has<BehaviourComponent>()) {
		object.get<BehaviourComponent>().update(object);
	}
}

