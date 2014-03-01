#include "name_example_system.h"

#include <iostream>

void *Ygg::NameExampleSystem::InitComponents()
{
	return new std::vector<NameExampleComponent>();
}

void Ygg::NameExampleSystem::Convert(std::vector<ConverterData>* cdata, void* components)
{
	std::vector<NameExampleComponent>* nes_components = (std::vector<NameExampleComponent>*)components;

	unsigned int last_size = nes_components->size();
	nes_components->resize(last_size + cdata->size());

	for (unsigned int i = 0; i != cdata->size(); ++i)
	{
		std::cout << "Converting Object" << std::endl;
		(*nes_components)[last_size + i] = {"Foo"};
	}
}

void Ygg::NameExampleSystem::Update(float dt, void *components)
{
	std::vector<NameExampleComponent>* nes_components = (std::vector<NameExampleComponent>*)components;

	std::cout << "===NameExampleSystem(dt=" << dt << ")===" << std::endl;
	for (unsigned int i = 0; i != nes_components->size(); ++i)
		std::cout << (*nes_components)[i].name << std::endl;
}
