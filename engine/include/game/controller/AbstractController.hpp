/*
 * =====================================================================================
 *
 *       Filename:  AbstractController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 00:40:03
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef ABSTRACTCONTROLLER_HPP_
#define ABSTRACTCONTROLLER_HPP_

#include "SceneObjectList.hpp"

class AbstractController {
	public:
		virtual void reset(SceneObject &) {}
		virtual void update(SceneObject &object) = 0;

		virtual void reset(SceneObjectList &objectList) {
			for(auto &object : objectList) {
				reset(object);

				if (object.has<SceneObjectList>())
					reset(object.get<SceneObjectList>());
			}
		}

		virtual void update(SceneObjectList &objectList) {
			for(auto &object : objectList) {
				update(object);

				if (object.has<SceneObjectList>())
					update(object.get<SceneObjectList>());
			}
		}
};

#endif // ABSTRACTCONTROLLER_HPP_
