#include <cstdio>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

#include "entity.h"
#include "loader.h"

void Ygg::Loader::AppendData(const std::string &name, const void* data, NodeType type, std::vector<Entity> *entity_list)
{
	Ygg::Entity entity;
	Ygg::ConverterData cdata;

	printf("Append Data (type=%d, name=%s)\n", type, name.c_str());

	entity_list->push_back(entity);
	cdata.type = type;
	cdata.data = data;
	cdata.entity_index = entity_list->size()-1;
	(*entity_list)[cdata.entity_index].init(name);
	this->results.push_back(cdata);
}

void Ygg::Loader::ParseScene(const aiScene* ascene, std::vector<Entity> *entity_list)
{

	// Scene
	this->AppendData("Scene", ascene, Ygg::NodeType::Scene, entity_list);

	// Cameras
	aiCamera *acamera;
	for (unsigned int i = 0; i < ascene->mNumCameras; ++i) {
		acamera = ascene->mCameras[i];
		this->AppendData(acamera->mName.C_Str(), acamera, Ygg::NodeType::Camera, entity_list);
	}

	// Meshes
	aiMesh *amesh;
	for (unsigned int i = 0; i < ascene->mNumMeshes; ++i) {
		amesh = ascene->mMeshes[i];
		this->AppendData(amesh->mName.C_Str(), amesh, Ygg::NodeType::Mesh, entity_list);
	}

	// Lights
	aiLight *alight;
	for (unsigned int i = 0; i < ascene->mNumLights; ++i) {
		alight = ascene->mLights[i];
		this->AppendData(alight->mName.C_Str(), alight, Ygg::NodeType::Light, entity_list);
	}
}

std::vector<Ygg::ConverterData>* Ygg::Loader::LoadScene(const std::string filename, std::vector<Entity> *entity_list)
{
	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SLM_VERTEX_LIMIT, 65536);
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT | aiPrimitiveType_LINE);
	const aiScene* ascene = importer.ReadFile(filename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_FindDegenerates |
		aiProcess_SplitLargeMeshes |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!ascene)
	{
		std::fprintf(stderr, "%s\n", importer.GetErrorString());
		return &this->results;
	}

	// Get path for relative textures
	int split = (int)filename.rfind("/");
	std::string path = filename.substr(0, split + 1);

	// Now we can access the file's contents.
	this->ParseScene(ascene, entity_list);

	return &this->results;
}
