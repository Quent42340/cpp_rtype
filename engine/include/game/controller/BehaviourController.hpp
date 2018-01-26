/*
 * =====================================================================================
 *
 *       Filename:  BehaviourController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:25:12
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef BEHAVIOURCONTROLLER_HPP_
#define BEHAVIOURCONTROLLER_HPP_

#include "AbstractController.hpp"

class BehaviourController : public AbstractController {
	public:
		void update(SceneObject &object) override;
};

#endif // BEHAVIOURCONTROLLER_HPP_
