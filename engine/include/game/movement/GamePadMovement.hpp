/*
 * =====================================================================================
 *
 *       Filename:  GamePadMovement.hpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:41:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GAMEPADMOVEMENT_HPP_
#define GAMEPADMOVEMENT_HPP_

#include "Movement.hpp"

class GamePadMovement : public Movement {
	public:
		void process(SceneObject &object) override;
};

#endif // GAMEPADMOVEMENT_HPP_
