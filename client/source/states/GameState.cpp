/*
 * =====================================================================================
 *
 *       Filename:  GameState.cpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:45:11
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "GameState.hpp"
#include "NetworkCommandHandler.hpp"
#include "ResourceHandler.hpp"
#include "Scene.hpp"

GameState::GameState() {
	NetworkCommandHandler::connect();

	// m_spawnTimer.start();
}

void GameState::update() {
	// if (m_spawnTimer.time() > 2000) {
	// 	m_spawnTimer.reset();
	// 	m_spawnTimer.start();
    //
	// 	m_scene.addObject(TestEnemyFactory::create({Application::screenWidth + 20, static_cast<float>(std::rand() % (Application::screenHeight - 40))}));
	// }

	NetworkCommandHandler::update(m_scene);

	m_background.move(-0.03, 0);

	// m_scene.update();
}

void GameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	// target.setView(view);

	target.draw(m_background, states);
	target.draw(m_scene, states);

	// target.setView(target.getDefaultView());
}

