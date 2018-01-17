/*
 * =====================================================================================
 *
 *       Filename:  BehaviourComponent.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:45:23
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef BEHAVIOURCOMPONENT_HPP_
#define BEHAVIOURCOMPONENT_HPP_

#include <functional>
#include <map>

#include "SceneObject.hpp"

class BehaviourComponent {
	using Action = std::function<void(SceneObject&)>;

	public:
		void addAction(const char *name, Action action) { m_actions.emplace(name, action); }
		void removeAction(const char *name) { m_actions.erase(name); }

		void update(SceneObject &object) {
			for(auto &it : m_actions) {
				it.second(object);
			}
		}

	private:
		std::map<std::string, Action> m_actions;
};

#endif // BEHAVIOURCOMPONENT_HPP_
