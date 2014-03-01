#include "engine.h"
#include "system.h"
#include "loader.h"

void Ygg::Engine::Update(float dt)
{
	for (unsigned int i = 0; i < m_systems.size(); ++i)
		m_systems[i]->Update(dt, m_components[m_systems[i]]);
}

void Ygg::Engine::AddSystem(System *system)
{
	m_systems.push_back(system);
	m_components[system] = system->InitComponents();
}

void Ygg::Engine::LoadLevel(const std::string filename)
{
	Loader loader = Loader();
	std::vector<ConverterData>* cdata;

	cdata = loader.LoadScene(filename, &m_entities);
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		(*it)->Convert(cdata, m_components[(*it)]);
}
