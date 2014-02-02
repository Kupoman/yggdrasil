#ifndef YGG_ENGINE_H
#define YGG_ENGINE_H

/**
 * @file engine.h
 */

#include <vector>

namespace Ygg {

class System;

/**
 * The core engine.
 */
class Engine
{
public:
	/**
	 * Step the engine.
	 * @param dt the timestep
	 */
	void Update(float dt);

	/**
	 * Add a System to the engine.
	 * @param system the system to add
	 */
	void AddSystem(System *system);

private:
	std::vector<System*> m_systems;
};

} // end namespace

#endif // YGG_ENGINE_H
