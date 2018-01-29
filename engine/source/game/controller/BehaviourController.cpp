/*
 * =====================================================================================
 *
 *       Filename:  BehaviourController.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:26:06
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "BehaviourComponent.hpp"
#include "BehaviourController.hpp"
#include "LifetimeComponent.hpp"

void BehaviourController::update(SceneObject &object) {
	if(object.has<BehaviourComponent>() && (!object.has<LifetimeComponent>() || !object.get<LifetimeComponent>().dead(object))) {
		object.get<BehaviourComponent>().update(object);
	}
}

