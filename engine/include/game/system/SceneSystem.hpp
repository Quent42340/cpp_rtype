/*
 * =====================================================================================
 *
 *       Filename:  SceneSystem.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:56:42
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SCENESYSTEM_HPP_
#define SCENESYSTEM_HPP_

#include <SFML/Graphics/Drawable.hpp>

#include "SceneObject.hpp"
#include "SceneObjectList.hpp"

class SceneSystem {
	public:
		static void reset(SceneObjectList &objectList);
		static void update(SceneObjectList &objectList);
		static void draw(const SceneObjectList &objectList, sf::RenderTarget &target, sf::RenderStates states);

		static void resetObject(SceneObject &object);
		static void updateObject(SceneObject &object);
		static void drawObject(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states);
};

#endif // SCENESYSTEM_HPP_
