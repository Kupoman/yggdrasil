#include "engine.h"
#include "system.h"
#include "entity.h"

Ygg::Engine::Engine()
{
	m_entities = new std::vector<Entity>();
}

Ygg::Engine::~Engine()
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		delete *it;

	m_systems.clear();

	delete m_entities;
}

void Ygg::Engine::Update(float dt)
{
	for (unsigned int i = 0; i < m_systems.size(); ++i)
		m_systems[i]->Update(this, dt);
}

void Ygg::Engine::AddSystem(System *system)
{
	m_systems.push_back(system);
	system->Init(this);
}

void Ygg::Engine::LoadLevel(const std::string filename)
{

}

void Ygg::Engine::ConvertEntities(std::vector<Ygg::Entity>* new_entities)
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		(*it)->Convert(this, new_entities);

	m_entities->insert(m_entities->end(), new_entities->begin(), new_entities->end());
}
