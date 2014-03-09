#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

#include "core/engine.h"
#include "core/entity.h"

#include "assimploader.h"

void Ygg::AssimpLoaderSystem::Init(Engine *engine)
{
	std::hash<std::string> hash_func;
	engine->RegisterComponentHandler(hash_func("mesh"), this);
}

int Ygg::AssimpLoaderSystem::LoadLights(size_t eoffset, std::vector<Entity> *equeue, const aiScene *ascene)
{
	size_t coffset = m_light_components.size();

	std::hash<std::string> hash_func;
	size_t id = hash_func("light");

	m_light_components.resize(coffset + ascene->mNumLights);
	equeue->resize(eoffset + ascene->mNumLights);

	AssimpLightComponent *light_component;
	aiLight *alight;
	ComponentHandle chandle;

	for (unsigned int i = 0; i < ascene->mNumLights; i++) {
		light_component = &m_light_components[coffset + i];
		alight = ascene->mLights[i];

		light_component->light.angle_inner = alight->mAngleInnerCone;
		light_component->light.angle_outer = alight->mAngleOuterCone;

		light_component->light.att_constant = alight->mAttenuationConstant;
		light_component->light.att_linear = alight->mAttenuationLinear;
		light_component->light.att_quadratic = alight->mAttenuationQuadratic;

		light_component->light.color_ambient[0] = alight->mColorAmbient.r;
		light_component->light.color_ambient[1] = alight->mColorAmbient.g;
		light_component->light.color_ambient[2] = alight->mColorAmbient.b;

		light_component->light.color_diffuse[0] = alight->mColorDiffuse.r;
		light_component->light.color_diffuse[1] = alight->mColorDiffuse.g;
		light_component->light.color_diffuse[2] = alight->mColorDiffuse.b;

		light_component->light.color_specular[0] = alight->mColorSpecular.r;
		light_component->light.color_specular[1] = alight->mColorSpecular.g;
		light_component->light.color_specular[2] = alight->mColorSpecular.b;

		(*equeue)[eoffset + i].name = std::string(ascene->mLights[i]->mName.C_Str());
		chandle = (ComponentHandle) (m_light_components.size() - 1);
		(*equeue)[eoffset + i].components.insert(std::pair<int, ComponentHandle>((int)id, chandle));
	}

	return ascene->mNumLights;
}

int Ygg::AssimpLoaderSystem::ParseMeshNodes(std::vector<Entity> *equeue, aiNode *node)
{
	int mesh_count = node->mNumMeshes;
	int entity_count = 0;
	ComponentHandle chandle;

	if (mesh_count) {
		equeue->resize(equeue->size() + 1);
		Entity *e = &equeue->back();
		m_mesh_components.resize(m_mesh_components.size() + 1);
		MeshComponent *c = &m_mesh_components.back();

		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			c->mesh_handles.push_back((int)(node->mMeshes[i]));
		}

		std::hash<std::string> hash_func;
		size_t id = hash_func("mesh");

		e->name = std::string(node->mName.C_Str());
		chandle = (ComponentHandle)(m_mesh_components.size() - 1);
		e->components.insert(std::pair<int, ComponentHandle>((int)id, chandle));
		entity_count++;
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		entity_count += ParseMeshNodes(equeue, node->mChildren[i]);
	}

	return entity_count;
}

int Ygg::AssimpLoaderSystem::LoadMeshes(size_t eoffset, std::vector<Entity> *equeue, const aiScene *ascene)
{
	// Gather mesh list
	size_t moffset = m_meshes.size();
	m_meshes.resize(ascene->mNumMeshes);
	Ygg::Mesh *ymesh;
	aiMesh *amesh;
	for (unsigned int i = 0; i < ascene->mNumMeshes; i++) {
		ymesh = &m_meshes[moffset + i];
		amesh = ascene->mMeshes[i];

		// Vertex positions and normals
		ymesh->vertices.resize(amesh->mNumVertices);
		ymesh->normals.resize(amesh->mNumVertices);
		for (unsigned int j = 0; j < amesh->mNumVertices; j++) {
			ymesh->vertices[j].x = amesh->mVertices[j].x;
			ymesh->vertices[j].y = amesh->mVertices[j].y;
			ymesh->vertices[j].z = amesh->mVertices[j].z;

			ymesh->normals[j].x = amesh->mNormals[j].x;
			ymesh->normals[j].y = amesh->mNormals[j].y;
			ymesh->normals[j].z = amesh->mNormals[j].z;
		}

		// Indices
		ymesh->indices.resize(amesh->mNumFaces * 3);
		for (unsigned int j = 0; j < amesh->mNumFaces; j++) {
			ymesh->indices[3 * j + 0] = amesh->mFaces[j].mIndices[0];
			ymesh->indices[3 * j + 1] = amesh->mFaces[j].mIndices[1];
			ymesh->indices[3 * j + 2] = amesh->mFaces[j].mIndices[2];
		}
	}

	// Find nodes to convert to entities
	return ParseMeshNodes(equeue, ascene->mRootNode);
}


void Ygg::AssimpLoaderSystem::LoadResource(Engine *engine, const char *name)
{
	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SLM_VERTEX_LIMIT, 65536);
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT | aiPrimitiveType_LINE);
	const aiScene* ascene = importer.ReadFile(name,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_FindDegenerates |
		aiProcess_SplitLargeMeshes |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!ascene)
	{
		std::fprintf(stderr, "%s\n", importer.GetErrorString());
		return;
	}

	std::vector<Entity> equeue;

	size_t eoffset = 0;

	eoffset += this->LoadLights(eoffset, &equeue, ascene);
	eoffset += this->LoadMeshes(eoffset, &equeue, ascene);

	engine->ConvertEntities(&equeue);
}

void Ygg::AssimpLoaderSystem::Update(Engine *engine, float dt)
{

}

std::vector<Ygg::Mesh> *Ygg::AssimpLoaderSystem::GetMeshes()
{
	return &m_meshes;
}

void *Ygg::AssimpLoaderSystem::GetComponent(size_t type, Ygg::ComponentHandle handle)
{
	std::hash<std::string> hash_func;

	if (type == hash_func("mesh"))
		return &m_mesh_components[handle];

	return NULL;
}
