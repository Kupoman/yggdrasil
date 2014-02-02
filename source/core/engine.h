#ifndef YGG_ENGINE_H
#define YGG_ENGINE_H

/**
 * @file engine.h
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

#endif // YGG_ENGINE_H
