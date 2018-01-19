/*
 * =====================================================================================
 *
 *       Filename:  Scene.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:34:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "CollisionComponent.hpp"
#include "CollisionSystem.hpp"
#include "Scene.hpp"
#include "SceneSystem.hpp"

void Scene::reset() {
	SceneSystem::reset(m_objects);
}

void Scene::update() {
	SceneSystem::update(m_objects);
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	SceneSystem::draw(m_objects, target, states);
}

SceneObject &Scene::addObject(SceneObject &&object) {
	SceneObject &obj = m_objects.addObject(std::move(object));

	if(obj.has<CollisionComponent>()) {
		obj.get<CollisionComponent>().addChecker([&](SceneObject &object) {
			checkCollisionsFor(object);
		});
	}

	return obj;
}

void Scene::addCollisionChecker(std::function<void(SceneObject &)> checker) {
	for (SceneObject &object : m_objects) {
		if (object.has<CollisionComponent>()) {
			object.get<CollisionComponent>().addChecker(checker);
		}
	}
}

void Scene::checkCollisionsFor(SceneObject &object) {
	for(SceneObject &object2 : m_objects) {
		if(&object != &object2) {
			CollisionSystem::checkCollision(object, object2);

			if (object.has<SceneObjectList>())
				for (SceneObject &child : object.get<SceneObjectList>())
					CollisionSystem::checkCollision(child, object2);

			if (object2.has<SceneObjectList>())
				for (SceneObject &child : object2.get<SceneObjectList>())
					CollisionSystem::checkCollision(object, child);
		}
	}
}


