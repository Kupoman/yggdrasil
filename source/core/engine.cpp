#include "engine.h"
#include "system.h"


void Ygg::Engine::Update(float dt)
{
	for (unsigned int i = 0; i < m_systems.size(); ++i)
		m_systems[i]->Update(dt);
}

void Ygg::Engine::AddSystem(System *system)
{
	m_systems.push_back(system);
}
