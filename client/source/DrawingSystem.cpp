/*
 * =====================================================================================
 *
 *       Filename:  DrawingSystem.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:49:51
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "DrawingSystem.hpp"
#include "HitboxComponent.hpp"
#include "Image.hpp"
#include "LifetimeComponent.hpp"
#include "PositionComponent.hpp"
#include "Sprite.hpp"

void DrawingSystem::draw(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states) {
	if (object.has<LifetimeComponent>() && object.get<LifetimeComponent>().dead(object))
		return;

	if (object.has<PositionComponent>())
		states.transform.translate(object.get<PositionComponent>());

	if(object.has<Image>()) {
		target.draw(object.get<Image>(), states);
	}

	if(object.has<Sprite>()) {
		target.draw(object.get<Sprite>(), states);
	}

	if(object.has<HitboxComponent>()) {
		// drawHitbox(object, target, states);
	}
}

void DrawingSystem::drawHitbox(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states) {
	auto &hitboxComponent = object.get<HitboxComponent>();

	const sf::FloatRect *hitbox = hitboxComponent.currentHitbox();
	if(hitbox) {
		sf::RectangleShape rect;
		rect.setPosition(hitbox->left, hitbox->top);
		rect.setSize(sf::Vector2f(hitbox->width, hitbox->height));
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color::White);
		rect.setFillColor(sf::Color::Transparent);

		target.draw(rect, states);
	}
}

