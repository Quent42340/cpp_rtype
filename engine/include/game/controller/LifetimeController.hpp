/*
 * =====================================================================================
 *
 *       Filename:  LifetimeController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:19:16
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef LIFETIMECONTROLLER_HPP_
#define LIFETIMECONTROLLER_HPP_

#include "AbstractController.hpp"

class LifetimeController : public AbstractController {
	public:
		void update(SceneObjectList &objectList) override;
		void update(SceneObject &) override {}
};

#endif // LIFETIMECONTROLLER_HPP_
