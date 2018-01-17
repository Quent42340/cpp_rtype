/*
 * =====================================================================================
 *
 *       Filename:  Movement.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:41:30
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

#include "SceneObject.hpp"

class Movement {
	public:
		virtual ~Movement() = default;

		bool isFinished() const { return m_isFinished; }

		virtual void process(SceneObject &object) = 0;

	protected:
		bool m_isFinished = false;
};

#endif // MOVEMENT_HPP_
