#include "entity.h"

Ygg::Entity::Entity()
{
	this->name = "";
	this->components = NULL;
}

Ygg::Entity::Entity(const Entity& other)
{
	this->name = other.name;
	if (other.components) {
		this->components = new std::map<int, void*>();
		*this->components = *other.components;
	}
	else
		this->components = NULL;
}

Ygg::Entity::~Entity()
{
	if (this->components) {
		delete this->components;
		this->components = NULL;
	}
}

void Ygg::Entity::init(std::string const& name)
{
	this->name = name;
	this->components = new std::map<int, void*>();
}
