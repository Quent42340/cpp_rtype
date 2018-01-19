/*
 * =====================================================================================
 *
 *       Filename:  Behaviour.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:44:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef BEHAVIOUR_HPP_
#define BEHAVIOUR_HPP_

#include "SceneObject.hpp"

class Behaviour {
	public:
		virtual void update(SceneObject &object) = 0;
};

#endif // BEHAVIOUR_HPP_
