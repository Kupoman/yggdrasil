#ifndef YGG_NAME_EXAMPLE_SYSTEM_H
#define YGG_NAME_EXAMPLE_SYSTEM_H

/**
 * @file name_example_system.h
 */

#include "core/system.h"
#include <string>
namespace Ygg {

struct NameExampleComponent
{
	std::string name;
};

/**
 * Base class for systems.
 */
class NameExampleSystem: public System
{
public:
	NameExampleSystem() {}
	virtual ~NameExampleSystem() {}

	void* InitComponents();

	void Convert(std::vector<ConverterData>* cdata, void* components);

	/**
	 * Step the system
	 * @param dt the timestep
	 */
	void Update(float dt, void* components);
};

} // end namespace

#endif // YGG_NAME_EXAMPLE_SYSTEM_H
