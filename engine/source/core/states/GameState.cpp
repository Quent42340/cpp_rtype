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
#include "ResourceHandler.hpp"
#include "Scene.hpp"

#include "TestBulletFactory.hpp"
#include "TestEntityFactory.hpp"

sf::View GameState::view{sf::FloatRect(0, 0, Application::screenWidth, Application::screenHeight)};

GameState::GameState() {
	view.reset(sf::FloatRect(0, 0, Application::screenWidth, Application::screenHeight));

	// Scene::player = &m_player;

	m_scene.addObject(TestEntityFactory::create(20, 50));
}

void GameState::update() {
	m_scene.update();
}

void GameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.setView(view);

	target.draw(m_scene, states);

	target.setView(target.getDefaultView());
}
