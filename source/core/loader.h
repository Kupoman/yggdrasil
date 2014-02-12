#ifndef YGG_LOADER_H
#define YGG_LOADER_H

#include <utility>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include "entity.h"

/**
 * @file loader.h
 */

namespace Ygg {

/**
* Scoped Enum to indicate the data type held by ConverterData.
*/
enum class NodeType
{
	Scene,
	Mesh,
	Camera,
	Light,
};

/**
 * Contains data needed for conversion.
 */
struct ConverterData {
	NodeType type;
	const void *data;
	unsigned int entity_index;
};

/**
 * The file loader used by Engine.
 */
class Loader
{
	private:
		Assimp::Importer importer;
		std::vector<ConverterData> results;

		void AppendData(std::string const& name, const void* data, NodeType type, std::vector<Entity> *entity_list);
		void ParseScene(const aiScene* ascene, std::vector<Entity> *entity_list);

	public:
		/**
		 * Load a scene file into a vector of ConverterData for conversion.
		 * @param filename File containing scene data to be loaded
		 * @param entity_list List of entities to add newly loaded entities to
		 */
		std::vector<ConverterData>* LoadScene(const std::string filename, std::vector<Entity> *entity_list);
};

} // end namespace

#endif // YGG_LOADER_H
