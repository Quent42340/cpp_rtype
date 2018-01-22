/*
 * =====================================================================================
 *
 *       Filename:  TestEntityFactory.hpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:36:44
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TESTENTITYFACTORY_HPP_
#define TESTENTITYFACTORY_HPP_

#include "SceneObject.hpp"

class TestEntityFactory {
	public:
		static SceneObject create(u16 x, u16 y);

		static SceneObject createClient(const std::string &name, const std::string &type, u16 port, u16 x, u16 y);
		static SceneObject createServer(u16 x, u16 y, u16 senderPort);
};

#endif // TESTENTITYFACTORY_HPP_
