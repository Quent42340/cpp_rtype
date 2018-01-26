/*
 * =====================================================================================
 *
 *       Filename:  GamePadController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:27:13
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GAMEPADCONTROLLER_HPP_
#define GAMEPADCONTROLLER_HPP_

#include "AbstractController.hpp"
#include "ServerInfo.hpp"

class GamePadController : public AbstractController {
	public:
		GamePadController(ServerInfo &serverInfo) : m_serverInfo(serverInfo) {}

		void update(SceneObject &object) override;

	private:
		ServerInfo &m_serverInfo;
};

#endif // GAMEPADCONTROLLER_HPP_
