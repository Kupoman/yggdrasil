#include "engine.h"
#include "system.h"
#include "loader.h"

Ygg::Engine::~Engine()
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		delete *it;

	m_systems.clear();
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
	Loader loader = Loader();
	std::vector<ConverterData>* cdata;

	cdata = loader.LoadScene(filename, &m_entities);
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		(*it)->Convert(this, cdata);
}
