#ifndef YGG_NAME_EXAMPLE_SYSTEM_H
#define YGG_NAME_EXAMPLE_SYSTEM_H

/**
 * @file name_example_system.h
 */

#include "core/system.h"
#include <string>

namespace Ygg {

class Engine;

struct NameExampleComponent
{
	std::string name;
};

/**
 * Base class for systems.
 */
class NameExampleSystem: public System
{
private:
	std::vector<NameExampleComponent> m_components;
public:
	NameExampleSystem() {}
	virtual ~NameExampleSystem() {}

	void Init(Engine* engine);

	void Convert(Engine* engine, std::vector<Entity>* cdata);

	/**
	 * Step the system
	 * @param dt the timestep
	 */
	void Update(Engine* engine, float dt);
};

} // end namespace

#endif // YGG_NAME_EXAMPLE_SYSTEM_H
