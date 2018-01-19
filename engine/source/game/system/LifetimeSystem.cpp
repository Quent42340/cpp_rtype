/*
 * =====================================================================================
 *
 *       Filename:  LifetimeSystem.cpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 04:15:07
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "LifetimeComponent.hpp"
#include "LifetimeSystem.hpp"

void LifetimeSystem::process(SceneObjectList &objects) {
	for(size_t i = 0 ; i < objects.size() ; i++) {
		if(objects[i].has<LifetimeComponent>() && objects[i].get<LifetimeComponent>().dead(objects[i])) {
			objects.remove(i--);
		}
	}
}

