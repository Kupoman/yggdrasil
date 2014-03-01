#ifndef YGG_ASSIMPLOADER_H
#define YGG_ASSIMPLOADER_H

#include "core/system_loader.h"

namespace Ygg {

struct AssimpLoaderComponent
{
	std::string name;
};

class AssimpLoaderSystem: public SystemLoader
{
private:
	std::vector<AssimpLoaderComponent> m_components;

public:
	AssimpLoaderSystem() {}
	virtual ~AssimpLoaderSystem() {}

	void Init();
	void LoadResource(Engine *engine, char *name);
	void Update(Engine *engine, float dt);
};

} // end namespace

#endif // YGG_ASSIMPLOADER_H
