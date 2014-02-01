#ifndef ENGINE_H
#define ENGINE_H

/**
 * @file Engine.h
 */

namespace Ygg {

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
};

} // end namespace

#endif // ENGINE_H
