/*
 * =====================================================================================
 *
 *       Filename:  SpriteView.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:30:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/gui/Image.hpp>
#include <gk/gui/RectangleShape.hpp>
#include <gk/gui/Sprite.hpp>

#include "HitboxComponent.hpp"
#include "LifetimeComponent.hpp"
#include "PositionComponent.hpp"
#include "SpriteView.hpp"

void SpriteView::draw(const SceneObject &object, gk::RenderTarget &target, gk::RenderStates states) {
	if (object.has<LifetimeComponent>() && object.get<LifetimeComponent>().dead(object))
		return;

	if (object.has<PositionComponent>())
		states.transform.translate({object.get<PositionComponent>(), 0.f});

	if(object.has<gk::Image>()) {
		target.draw(object.get<gk::Image>(), states);
	}

	if(object.has<gk::Sprite>()) {
		target.draw(object.get<gk::Sprite>(), states);
	}

	if(object.has<HitboxComponent>()) {
		drawHitbox(object, target, states);
	}
}

void SpriteView::drawHitbox(const SceneObject &object, gk::RenderTarget &target, gk::RenderStates states) {
	auto &hitboxComponent = object.get<HitboxComponent>();

	const gk::FloatRect *hitbox = hitboxComponent.currentHitbox();
	if(hitbox) {
		gk::RectangleShape rect;
		rect.setPosition(hitbox->x, hitbox->y);
		rect.setSize(hitbox->width, hitbox->height);
		rect.setWireframeMode(true);
		rect.setColor(gk::Color::White);

		target.draw(rect, states);
	}
}


