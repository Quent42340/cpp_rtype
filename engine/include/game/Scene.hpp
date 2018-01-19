/*
 * =====================================================================================
 *
 *       Filename:  Scene.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:34:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <functional>

#include <SFML/Graphics/Drawable.hpp>

#include "SceneObject.hpp"
#include "SceneObjectList.hpp"

class Scene : public sf::Drawable {
	public:
		void reset();
		void update();

		SceneObject &addObject(SceneObject &&object);

		void addCollisionChecker(std::function<void(SceneObject &)> checker);
		void checkCollisionsFor(SceneObject &object);

		const SceneObjectList &objects() { return m_objects; }

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		SceneObjectList m_objects;
};

#endif // SCENE_HPP_
