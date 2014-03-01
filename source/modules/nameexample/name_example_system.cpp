#include "name_example_system.h"
#include "core/engine.h"

#include <iostream>

void Ygg::NameExampleSystem::Init(Engine* engine)
{
}

void Ygg::NameExampleSystem::Convert(Engine* engine, std::vector<ConverterData>* cdata)
{
	unsigned int last_size = m_components.size();
	m_components.resize(last_size + cdata->size());

	for (unsigned int i = 0; i != cdata->size(); ++i)
	{
		std::cout << "Converting Object" << std::endl;
		m_components[last_size + i] = {"Foo"};
	}
}

void Ygg::NameExampleSystem::Update(Engine* engine, float dt)
{
	std::cout << "===NameExampleSystem(dt=" << dt << ")===" << std::endl;
	for (unsigned int i = 0; i != m_components.size(); ++i)
		std::cout << m_components[i].name << std::endl;
}
