/*
 * =====================================================================================
 *
 *       Filename:  ResourceLoader.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:31:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef RESOURCELOADER_HPP_
#define RESOURCELOADER_HPP_

#include <string>

#include "ResourceHandler.hpp"

class ResourceLoader {
	public:
		ResourceLoader() = default;
		ResourceLoader(const ResourceLoader &) = delete;
		ResourceLoader(ResourceLoader &&) = default;
		virtual ~ResourceLoader() = default;

		ResourceLoader &operator=(const ResourceLoader &) = delete;
		ResourceLoader &operator=(ResourceLoader &&) = default;

		virtual void load(const char *xmlFilename, ResourceHandler &handler) = 0;
};

#endif // RESOURCELOADER_HPP_
