#ifndef YGG_ENTITY_H
#define YGG_ENTITY_H

#include <map>
#include <string>

/**
* @file entity.h
*/

namespace Ygg {

	typedef unsigned int ComponentHandle;

	/**
	* An entity for an entity component system.
	*/
	class Entity
	{
	public:
		/**
		 * Name of the entity.
		 */
		std::string name;

		/**
		 * A map of the entity's components.
		 */
		std::map<int, ComponentHandle> components;

		/**
		 * Initializes the component for use.
		 * @param name name of the entity
		 */
		void init(std::string const& name);
	};

} // end namespace

#endif // YGG_ENTITY_H
