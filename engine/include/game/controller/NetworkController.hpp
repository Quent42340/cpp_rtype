/*
 * =====================================================================================
 *
 *       Filename:  NetworkController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:21:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORKCONTROLLER_HPP_
#define NETWORKCONTROLLER_HPP_

#include "AbstractController.hpp"

class NetworkController : public AbstractController {
	public:
		void update(SceneObject &object) override;
};

#endif // NETWORKCONTROLLER_HPP_
