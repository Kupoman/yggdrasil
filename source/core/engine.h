#ifndef YGG_ENGINE_H
#define YGG_ENGINE_H

/**
 * @file engine.h
 */

#include <vector>
#include <map>
#include <string>

namespace Ygg {

class System;
class Entity;

/**
 * The core engine.
 */
class Engine
{
public:
	Engine();
	~Engine();

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

	void RegisterComponentHandler(size_t type, System *system);

	void *GetComponent(Entity *entity, size_t type);

	void LoadLevel(const std::string filename);

	void ConvertEntities(std::vector<Entity>* new_entities);



private:
	std::vector<System*> m_systems;
	std::vector<Entity> *m_entities;
	std::map<size_t, System*> m_handlers;
};

} // end namespace

#endif // YGG_ENGINE_H
