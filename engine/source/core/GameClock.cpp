/*
 * =====================================================================================
 *
 *       Filename:  GameClock.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:07:36
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "GameClock.hpp"

sf::Clock GameClock::clock;
u32 GameClock::ticks = 0;

u32 GameClock::getTicks(bool realTime) {
	if(realTime) {
		return clock.getElapsedTime().asMilliseconds();
	} else {
		return ticks;
	}
}

void GameClock::measureLastFrameDuration() {
	u32 now = getTicks(true) - m_timeDropped;
	u32 lastFrameDuration = now - m_lastFrameDate;

	m_lastFrameDate = now;
	m_lag += lastFrameDuration;

	if(m_lag >= 200) {
		m_timeDropped += m_lag - m_timestep;
		m_lag = m_timestep;
		m_lastFrameDate = getTicks(true) - m_timeDropped;
	}
}

void GameClock::updateGame(std::function<void(void)> updateFunc) {
	m_numUpdates = 0;

	while(m_lag >= m_timestep && m_numUpdates < 10) {
		ticks += m_timestep;

		updateFunc();

		m_lag -= m_timestep;
		m_numUpdates++;
	}
}

void GameClock::drawGame(std::function<void(void)> drawFunc) {
	if(m_numUpdates > 0) {
		drawFunc();
	}

	u32 lastFrameDuration = getTicks(true) - m_timeDropped - m_lastFrameDate;

	if(lastFrameDuration < m_timestep) {
		sf::sleep(sf::milliseconds(m_timestep - lastFrameDuration));
	}

	measureLastFrameDuration();
}

