/*
 * =====================================================================================
 *
 *       Filename:  DrawingSystem.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:49:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef DRAWINGSYSTEM_HPP_
#define DRAWINGSYSTEM_HPP_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "SceneObject.hpp"

class DrawingSystem {
	public:
		static void draw(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states);
};

#endif // DRAWINGSYSTEM_HPP_
