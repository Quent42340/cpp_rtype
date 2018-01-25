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
		if(objects[i].has<LifetimeComponent>()) {
			auto &lifetimeComponent = objects[i].get<LifetimeComponent>();
			if (lifetimeComponent.dead(objects[i]) && lifetimeComponent.areClientsNotified()) {
				bool canDelete = true;
				if (objects[i].has<SceneObjectList>()) {
					for (SceneObject &object : objects[i].get<SceneObjectList>()) {
						if (object.has<LifetimeComponent>() && !object.get<LifetimeComponent>().dead(object)) {
							canDelete = false;
							break;
						}
					}
				}

				if (canDelete)
					objects.remove(i--);
			}
		}
	}
}

