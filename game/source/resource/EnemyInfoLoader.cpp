/*
 * =====================================================================================
 *
 *       Filename:  EnemyInfoLoader.cpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 08:09:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "EnemyInfo.hpp"
#include "EnemyInfoLoader.hpp"
#include "XMLFile.hpp"

void EnemyInfoLoader::load(const char *xmlFilename, ResourceHandler &handler) {
	XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *enemyElement = doc.FirstChildElement("enemies").FirstChildElement("enemy").ToElement();
	while (enemyElement) {
		EnemyInfo enemyInfo;
		enemyInfo.name = enemyElement->Attribute("name");
		enemyInfo.texture = enemyElement->Attribute("texture");
		enemyInfo.health = enemyElement->IntAttribute("health");

		tinyxml2::XMLElement *hitboxElement = enemyElement->FirstChildElement("hitbox");
		if (hitboxElement) {
			enemyInfo.hitboxPosition.x = hitboxElement->IntAttribute("x");
			enemyInfo.hitboxPosition.y = hitboxElement->IntAttribute("y");
			enemyInfo.hitboxSize.x = hitboxElement->IntAttribute("width");
			enemyInfo.hitboxSize.y = hitboxElement->IntAttribute("height");
		}

		tinyxml2::XMLElement *movementElement = enemyElement->FirstChildElement("movement");
		if (movementElement) {
			enemyInfo.movementType = movementElement->Attribute("type");
			enemyInfo.movementSpeed = movementElement->FloatAttribute("speed");
		}

		tinyxml2::XMLElement *bulletElement = enemyElement->FirstChildElement("bullet");
		while (bulletElement) {
			BulletInfo bulletInfo;
			bulletInfo.type = bulletElement->Attribute("type");
			bulletInfo.velocity.x = bulletElement->FloatAttribute("vx");
			bulletInfo.velocity.y = bulletElement->FloatAttribute("vy");
			bulletInfo.speed = bulletElement->FloatAttribute("speed");

			enemyInfo.bulletsInfo.emplace_back(std::move(bulletInfo));

			bulletElement = bulletElement->NextSiblingElement("bullet");
		}

		handler.add<EnemyInfo>("info-" + enemyInfo.name, enemyInfo);

		enemyElement = enemyElement->NextSiblingElement("enemy");
	}
}

