/*
 * =====================================================================================
 *
 *       Filename:  TestBulletFactory.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:22:21
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TESTBULLETFACTORY_HPP_
#define TESTBULLETFACTORY_HPP_

#include "SceneObject.hpp"

class TestBulletFactory {
	public:
		static SceneObject create(const sf::Vector2f &pos, const sf::Vector2f &v);
};

#endif // TESTBULLETFACTORY_HPP_
