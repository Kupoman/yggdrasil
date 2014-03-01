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

	virtual void Init(class Engine* engine)=0;

	virtual void Convert(class Engine* engine, std::vector<ConverterData>* entity_queue)=0;

	/**
	 * Step the system
	 * @param dt the timestep
	 */
	virtual void Update(class Engine* engine, float dt) = 0;
};

} // end namespace

#endif // YGG_SYSTEM_H
