/*
 * =====================================================================================
 *
 *       Filename:  MovementController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:17:11
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef MOVEMENTCONTROLLER_HPP_
#define MOVEMENTCONTROLLER_HPP_

#include "AbstractController.hpp"

class MovementController : public AbstractController {
	public:
		void update(SceneObject &object) override;
};

#endif // MOVEMENTCONTROLLER_HPP_
