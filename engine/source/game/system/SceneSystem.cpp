/*
 * =====================================================================================
 *
 *       Filename:  SceneSystem.cpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:57:09
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "BehaviourSystem.hpp"
#include "DrawingSystem.hpp"
#include "LifetimeSystem.hpp"
#include "MovementSystem.hpp"
#include "NetworkSystem.hpp"
#include "SceneSystem.hpp"

void SceneSystem::reset(SceneObjectList &objectList) {
	for(auto &object : objectList) resetObject(object);
}

void SceneSystem::update(SceneObjectList &objectList) {
	for(auto &object : objectList) updateObject(object);

	LifetimeSystem::process(objectList);
}

void SceneSystem::draw(const SceneObjectList &objectList, sf::RenderTarget &target, sf::RenderStates states) {
	for(const auto &object : objectList) drawObject(object, target, states);
}

void SceneSystem::resetObject(SceneObject &object) {
	// BehaviourSystem::reset(object);

	if(object.has<SceneObjectList>()) {
		reset(object.get<SceneObjectList>());
	}
}

void SceneSystem::updateObject(SceneObject &object) {
	BehaviourSystem::process(object);
	MovementSystem::process(object);
	NetworkSystem::process(object);

	if(object.has<SceneObjectList>()) {
		update(object.get<SceneObjectList>());
	}
}

void SceneSystem::drawObject(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states) {
	DrawingSystem::draw(object, target, states);

	if(object.has<SceneObjectList>()) {
		draw(object.get<SceneObjectList>(), target, states);
	}
}

