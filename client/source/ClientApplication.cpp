/*
 * =====================================================================================
 *
 *       Filename:  ClientClientApplication.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:31:02
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/audio/AudioPlayer.hpp>
#include <gk/core/input/GamePad.hpp>
#include <gk/resource/TextureLoader.hpp>

#include "AudioLoader.hpp"
#include "ClientApplication.hpp"
#include "Config.hpp"
#include "GameState.hpp"
#include "SpriteLoader.hpp"
#include "TitleScreenState.hpp"

void ClientApplication::init() {
	gk::CoreApplication::init();

	createWindow(Config::screenWidth, Config::screenHeight, "R-Type");

	gk::GamePad::init(m_keyboardHandler);

	m_shader.loadFromFile("resources/shaders/game.v.glsl", "resources/shaders/game.f.glsl");
	m_renderStates.shader = &m_shader;

	m_renderStates.vertexAttributes = gk::VertexAttribute::Only2d;
	m_renderStates.projectionMatrix = glm::ortho(0.0f, (float)Config::screenWidth, (float)Config::screenHeight, 0.0f);

	m_resourceHandler.loadConfigFile<AudioLoader>("resources/config/audio.xml");
	m_resourceHandler.loadConfigFile<gk::TextureLoader>("resources/config/textures.xml");
	m_resourceHandler.loadConfigFile<SpriteLoader>("resources/config/sprites.xml");
	m_resourceHandler.add<gk::Font>("font-default").loadFromFile("resources/fonts/arial.ttf");
	m_resourceHandler.add<gk::Font>("font-pdark").loadFromFile("resources/fonts/pdark.ttf");

	gk::ApplicationStateStack::getInstance().push<TitleScreenState>();
}

void ClientApplication::onEvent(const SDL_Event &event) {
	gk::CoreApplication::onEvent(event);

	m_keyboardHandler.updateState(event);

	// if (event.type == sf::Event::GainedFocus) {
	// 	gk::AudioPlayer::resumeMusic();
	// }
	// else if (event.type == sf::Event::LostFocus) {
	// 	gk::AudioPlayer::pauseMusic();
	// }
}

