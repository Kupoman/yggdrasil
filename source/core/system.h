#ifndef YGG_SYSTEM_H
#define YGG_SYSTEM_H

/**
 * @file system.h
 */

namespace Ygg {

/**
 * Base class for systems.
 */
class System
{
public:
	virtual ~System() {}

	/**
	 * Step the system
	 * @param dt the timestep
	 */
	virtual void Update(float dt) = 0;
};

} // end namespace

#endif // YGG_SYSTEM_H
