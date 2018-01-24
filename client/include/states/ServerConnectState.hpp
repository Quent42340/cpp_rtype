/*
 * =====================================================================================
 *
 *       Filename:  ServerConnectState.hpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 02:57:50
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SERVERCONNECTSTATE_HPP_
#define SERVERCONNECTSTATE_HPP_

#include "ApplicationState.hpp"
#include "Button.hpp"
#include "Image.hpp"
#include "TextInput.hpp"
#include "Timer.hpp"

class ServerConnectState : public ApplicationState {
	public:
		ServerConnectState();

		void onEvent(sf::Event &event) override;

		void update() override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		Image m_background{"background-space"};

		sf::Text m_text;
		sf::Text m_errorText;
		Timer m_errorTimer;

		TextInput m_serverAddressInput;

		bool m_isConnecting = false;

		Button m_back{"Back"};
};

#endif // SERVERCONNECTSTATE_HPP_
