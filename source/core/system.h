#ifndef YGG_SYSTEM_H
#define YGG_SYSTEM_H

/**
 * @file system.h
 */

#include <vector>
#include "entity.h"

namespace Ygg {

class Engine;
class Entity;

#define DECLARE_COMPONENTID(name) static const size_t CID_##name
#define DEFINE_COMPONENTID(class, name) const size_t class::CID_##name = GetNewComponentID()
#define REGISTER_COMPONENTID(name) engine->RegisterComponentHandler(CID_##name, this)

inline size_t GetNewComponentID() {
	static size_t i = 1;
	return i++;
}

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

	virtual void *GetComponent(size_t type, ComponentHandle handle) {return NULL;}
};

} // end namespace

#endif // YGG_SYSTEM_H
