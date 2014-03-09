#ifndef YGG_SYSTEM_LOADER_H
#define YGG_SYSTEM_LOADER_H

/**
 * @file system_loader.h
 */

#include "system.h"

namespace Ygg {

struct LightComponent
{
	float angle_inner;
	float angle_outer;
	float att_constant;
	float att_linear;
	float att_quadratic;
	float color_ambient[3];
	float color_diffuse[3];
	float color_specular[3];
};

typedef unsigned int MeshHandle;

struct DataVec3 {
	union {
		float data[3];
		struct {
			float x;
			float y;
			float z;
		};
	};
};

struct Mesh
{
	std::vector<DataVec3> vertices;
	std::vector<DataVec3> normals;
	std::vector<unsigned short> indices;
};

struct MeshComponent
{
	std::vector<MeshHandle> mesh_handles;
};

/**
 * Base class for loader systems.
 */
class SystemLoader: public System
{
public:
	virtual ~SystemLoader() {}

	virtual void Init(Engine *engine)=0;

	virtual void Convert(Engine *engine, std::vector<Entity> *new_entities){};

	/**
	 * Open and load data from a resource of the given name
	 * The resource could be something that is loaded from once, such as a file, or streamed
	 * @param engine the engine controlling this system
	 * @param name the name of the resource
	 */
	virtual void LoadResource(Engine *engine, const char *name) = 0;

	/**
	 * Step the system
	 * This may not be used by file loaders, but stream loaders will need to update
	 * @param engine the engine controlling this system
	 * @param dt the timestep
	 */
	virtual void Update(Engine *engine, float dt) = 0;

	/**
	 * Get mesh information from the system
	 * Meshes can be reused and are stored separately from mesh components to avoid data dupilcation
	 */
	virtual std::vector<Mesh>* GetMeshes() = 0;


	virtual void *GetComponent(size_t type, ComponentHandle handle) = 0;
};

} // end namespace

#endif // YGG_SYSTEM_LOADER_H
