#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

#include "core/engine.h"

#include "assimploader.h"

void Ygg::AssimpLoaderSystem::Init()
{

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
		(*equeue)[eoffset + i].components = new std::map<int, void*>();
		(*equeue)[eoffset + i].components->insert(std::pair<int, void*>(id, light_component));
	}

	return ascene->mNumLights;
}

void Ygg::AssimpLoaderSystem::LoadResource(Engine *engine, char *name)
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
}

void Ygg::AssimpLoaderSystem::Update(Engine *engine, float dt)
{

}
