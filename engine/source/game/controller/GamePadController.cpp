/*
 * =====================================================================================
 *
 *       Filename:  GamePadController.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:27:52
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "GamePad.hpp"
#include "GamePadController.hpp"
#include "PlayerComponent.hpp"
#include "ServerInfo.hpp"

void GamePadController::update(SceneObject &object) {
	if (object.has<PlayerComponent>()) {
		Client *client = ServerInfo::getInstance().getClient(object.get<PlayerComponent>().clientId());
		if (client)
			GamePad::init(client->inputHandler);
	}
}

