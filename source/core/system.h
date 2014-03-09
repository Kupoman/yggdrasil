#ifndef YGG_SYSTEM_H
#define YGG_SYSTEM_H

/**
 * @file system.h
 */

#include <vector>

namespace Ygg {

class Engine;
class Entity;

/**
 * Base class for systems.
 */
class System
{
public:
	virtual ~System() {}

	virtual void Init(Engine* engine)=0;

	virtual void Convert(Engine* engine, std::vector<Entity>* new_entities) = 0;

	/**
	 * Step the system
	 * @param dt the timestep
	 */
	virtual void Update(Engine* engine, float dt) = 0;
};

} // end namespace

#endif // YGG_SYSTEM_H
