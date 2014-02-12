#ifndef YGG_ENTITY_H
#define YGG_ENTITY_H

#include <map>
#include <string>

/**
* @file entity.h
*/

namespace Ygg {
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
		std::map<int, void*> *components;

		/**
		 * Default value constructor.
		 */
		Entity();

		/**
		 * Copy constructor.
		 */
		Entity(const Entity& other);

		/**
		 * Destructor.
		 */
		~Entity();

		/**
		 * Initializes the component for use.
		 * @param name name of the entity
		 */
		void init(std::string const& name);
	};

} // end namespace

#endif // YGG_ENTITY_H
