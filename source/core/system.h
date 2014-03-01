#ifndef YGG_SYSTEM_H
#define YGG_SYSTEM_H

/**
 * @file system.h
 */

#include <vector>
#include "loader.h"

namespace Ygg {

/**
 * Base class for systems.
 */
class System
{
public:
	virtual ~System() {}

	virtual void* InitComponents()=0;

	virtual void Convert(std::vector<ConverterData>* cdata, void* components)=0;

	/**
	 * Step the system
	 * @param dt the timestep
	 */
	virtual void Update(float dt, void* componetns) = 0;
};

} // end namespace

#endif // YGG_SYSTEM_H
