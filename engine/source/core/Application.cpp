/*
 * =====================================================================================
 *
 *       Filename:  Application.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 18:52:17
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "GamePad.hpp"
#include "Mouse.hpp"
#include "TextureLoader.hpp"

// #include "GameState.hpp"

bool Application::quit = false;

void Application::init() {
	std::srand(std::time(nullptr));

	m_window.create(sf::VideoMode(screenWidth, screenHeight), "R-Type", sf::Style::Close);
	m_window.setKeyRepeatEnabled(false);

	Mouse::setWindow(m_window);

	ApplicationStateStack::setInstance(m_stateStack);
	ResourceHandler::setInstance(m_resourceHandler);

	m_resourceHandler.loadConfigFile<TextureLoader>("data/config/textures.xml");
	// m_resourceHandler.loadConfigFile<TilesetLoader>("data/config/tilesets.xml");
	// m_resourceHandler.loadConfigFile<LevelLoader>("data/config/levels.xml");

	GamePad::init(m_keyboardHandler);

	// sf::Font &defaultFont = m_resourceHandler.add<sf::Font>("font-default");
	// defaultFont.loadFromFile("fonts/terminus.ttf");

	// ApplicationStateStack::getInstance().push<TitleScreenState>();
	// ApplicationStateStack::getInstance().push<LevelListState>();
	// ApplicationStateStack::getInstance().push<LevelState>(0);
	// ApplicationStateStack::getInstance().push<GameState>();
}

void Application::handleEvents() {
	m_keyboardHandler.resetState();

	sf::Event event;
	while(m_window.pollEvent(event)) {
		if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		 || event.type == sf::Event::Closed) {
			m_window.close();
		}

		m_keyboardHandler.updateState(event);
	}
}

int Application::run() {
	try {
		init();
		mainLoop();
	}
	catch(const Exception &e) {
		std::cerr << "Fatal error " << e.what() << std::endl;
		return 1;
	}
	catch(const std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void Application::mainLoop() {
	while(m_window.isOpen()) {
		handleEvents();

		m_clock.updateGame([&] {
			if(quit) m_window.close();

			ApplicationStateStack::getInstance().top().update();
		});

		m_clock.drawGame([&] {
			m_window.clear();

			m_window.draw(ApplicationStateStack::getInstance().top());

			m_window.display();
		});
	}
}

