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

#include <gk/core/ApplicationState.hpp>
#include <gk/core/Timer.hpp>
#include <gk/gui/Image.hpp>

#include "Button.hpp"
#include "TextInput.hpp"

class ServerConnectState : public gk::ApplicationState {
	public:
		ServerConnectState();

		void onEvent(const SDL_Event &event) override;

		void update() override;

	private:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

		gk::Image m_background{"background-space"};

		gk::Text m_text;
		gk::Text m_errorText;
		gk::Timer m_errorTimer;

		TextInput m_serverAddressInput;

		bool m_isConnecting = false;

		Button m_back{"Back"};
};

#endif // SERVERCONNECTSTATE_HPP_
