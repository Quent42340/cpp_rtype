/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 18:44:59
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "ServerApplication.hpp"

int main() {
	bool isRunning = true;
	while (isRunning) {
		ServerApplication app;
		if (app.run())
			isRunning = false;
		else
			sf::sleep(sf::seconds(4));
	}
}

