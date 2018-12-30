/*
 * =====================================================================================
 *
 *       Filename:  PositionComponent.hpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 00:04:22
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include <gk/core/Vector2.hpp>

class PositionComponent : public gk::Vector2f {
	public:
		PositionComponent(float x, float y) : gk::Vector2f(x, y) {}
		PositionComponent(const gk::Vector2f &pos) : gk::Vector2f(pos) {}
};

#endif // POSITIONCOMPONENT_HPP_
