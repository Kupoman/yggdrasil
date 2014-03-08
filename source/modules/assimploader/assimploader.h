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
	std::vector<MeshComponent> m_mesh_components;
	std::vector<Mesh> m_meshes;

	int LoadLights(size_t eoffset, std::vector<Entity> *equeue, const aiScene *ascene);
	int LoadMeshes(size_t eoffset, std::vector<Entity> *equeue, const aiScene *ascene);
	int ParseMeshNodes(std::vector<Entity> *equeue, aiNode *node);

public:
	AssimpLoaderSystem() {}
	virtual ~AssimpLoaderSystem() {}

	void Init(Engine *engine);
	void LoadResource(Engine *engine, char *name);
	void Update(Engine *engine, float dt);

	std::vector<Mesh> *GetMeshes();
};

} // end namespace

#endif // YGG_ASSIMPLOADER_H
