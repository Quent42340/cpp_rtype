/*
 * =====================================================================================
 *
 *       Filename:  EasyMovement.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:27:45
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef EASYMOVEMENT_HPP_
#define EASYMOVEMENT_HPP_

#include <functional>

#include "Movement.hpp"

class EasyMovement : public Movement {
	public:
		EasyMovement(const std::function<void(SceneObject &)> &func) : m_func(func) {}

		void process(SceneObject &object) override {
			m_func(object);
		}

	private:
		std::function<void(SceneObject &)> m_func;
};

#endif // EASYMOVEMENT_HPP_
