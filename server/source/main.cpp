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
	Server server;
	try {
		server.init();

		while (true) {
			server.setRunning(true);
			server.setGameStarted(false);
			ServerApplication app{server};
			app.run();
		}
	}
	catch(const Exception &e) {
		std::cerr << "Fatal error " << e.what() << std::endl;
		return 1;
	}
	catch(const std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 1;
	}
	catch(...) {
		std::cerr << "Fatal error: Unknown error." << std::endl;
		return 1;
	}
}

