/*
 * =====================================================================================
 *
 *       Filename:  EnemyInfo.hpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 08:13:39
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef ENEMYINFO_HPP_
#define ENEMYINFO_HPP_

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "IntTypes.hpp"

struct BulletInfo {
	std::string type;

	sf::Vector2f velocity;
	float speed;
};

struct EnemyInfo {
	std::string name;
	std::string texture;
	u16 health;

	sf::Vector2i hitboxPosition;
	sf::Vector2i hitboxSize;

	std::string movementType;
	float movementSpeed;

	std::vector<BulletInfo> bulletsInfo;
};

#endif // ENEMYINFO_HPP_
