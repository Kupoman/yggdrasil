#ifndef YGG_ASSIMPLOADER_H
#define YGG_ASSIMPLOADER_H

#include "core/system_loader.h"

namespace Ygg {

struct AssimpLightComponent
{
	LightComponent light;
};

class AssimpLoaderSystem: public SystemLoader
{
private:
	std::vector<AssimpLightComponent> m_light_components;

	int LoadLights(size_t eoffset, std::vector<Entity> *equeue, const aiScene *ascene);

public:
	AssimpLoaderSystem() {}
	virtual ~AssimpLoaderSystem() {}

	void Init();
	void LoadResource(Engine *engine, char *name);
	void Update(Engine *engine, float dt);
};

} // end namespace

#endif // YGG_ASSIMPLOADER_H
