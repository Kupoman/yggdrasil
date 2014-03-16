#include <Ogre.h>
#include <utility>
#include "core/engine.h"
#include "core/entity.h"
#include "core/system_loader.h"

#include "ogrerender.h"

using namespace Ogre;

Ygg::OgreRenderSystem::OgreRenderSystem(unsigned long window, SystemLoader *loader)
    :m_parentwindow(window),
      m_loader(loader)
{
}

Ygg::OgreRenderSystem::~OgreRenderSystem()
{
	delete m_root;
}

void Ygg::OgreRenderSystem::Init(Ygg::Engine *engine)
{
	m_root = new Ogre::Root("", "", "");

	// Load required systems
	Ogre::StringVector required_plugins;
	required_plugins.push_back("./RenderSystem_GL");
	required_plugins.push_back("./Plugin_OctreeSceneManager");

	for (auto it = required_plugins.begin(); it != required_plugins.end(); ++it) {
#ifdef _DEBUG
		m_root->loadPlugin(*it + Ogre::String("_d"));
#else
		m_root->loadPlugin(*it);
#endif
	}

	// ToDo, check that plugins were actually loaded

	m_root->setRenderSystem(m_root->getRenderSystemByName("OpenGL Rendering Subsystem"));
	m_root->initialise(false);

	// Setup the window
	Ogre::NameValuePairList params;
	params.insert(std::make_pair("externalWindowHandle", Ogre::StringConverter::toString(m_parentwindow)));

	m_window = m_root->createRenderWindow("Yggdrasil", 800, 600, false, &params);
	m_window->setVisible(true);

	// Setup the scenemanager
	m_scenemgr = m_root->createSceneManager("OctreeSceneManager", "DefaultSceneManager");

	// Setup the camera
	m_camera = m_scenemgr->createCamera("Camera");
	m_camera->setPosition(Ogre::Vector3(10, 10, 10));
	m_camera->lookAt(Ogre::Vector3(0, 0, 0));
	m_camera->setNearClipDistance(5);

	// Setup the viewport
	Ogre::Viewport *vp = m_window->addViewport(m_camera);
	vp->setBackgroundColour(Ogre::ColourValue(0.5f, 1.0f, 0.0f));

	// Match the camera aspect ratio to the viewport
	m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	// Create a default material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
	                                 "DefaultMaterial",
	                                 Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_AMBIENT);
	material->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(0.0, 0.2, 1.0, 0.0));

	// Set ambient light
	m_scenemgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	// Create a light
	Ogre::Light *light = m_scenemgr->createLight("MainLight");
	light->setPosition(20, 80, 50);
}

static void convert_mesh(const std::string& mname, Ygg::Mesh *mdata)
{
	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(mname, "General");
	Ogre::SubMesh *submesh = mesh->createSubMesh();

	const size_t nverts = mdata->vertices.size();
	float verts[3 * 2 * nverts];
	const size_t ibufcount = 3 * mdata->indices.size();
	unsigned short faces[ibufcount];

	for (size_t i = 0; i < nverts; ++i) {
		verts[6*i+0] = mdata->vertices[i].x;
		verts[6*i+1] = mdata->vertices[i].y;
		verts[6*i+2] = mdata->vertices[i].z;

		verts[6*i+3] = mdata->normals[i].x;
		verts[6*i+4] = mdata->normals[i].y;
		verts[6*i+5] = mdata->normals[i].z;
	}

	for (size_t i = 0; i < mdata->indices.size(); ++i) {
		faces[i] = mdata->indices[i];
	}

	mesh->sharedVertexData = new Ogre::VertexData();
	mesh->sharedVertexData->vertexCount = nverts;
	mesh->sharedVertexData->vertexStart = 0;

	// Create declaration (memory format) of vertex data
	Ogre::VertexDeclaration *decl = mesh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;

	offset += decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION).getSize();

	offset += decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL).getSize();

	// Allocate vertex buffer
	Ogre::HardwareVertexBufferSharedPtr vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
	                                               decl->getVertexSize(0), nverts,
	                                               Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	// Upload the vertex data to the GPU
	vbuf->writeData(0, vbuf->getSizeInBytes(), verts, true);

	// Bind the vertex buffer
	Ogre::VertexBufferBinding *binding = mesh->sharedVertexData->vertexBufferBinding;
	binding->setBinding(0, vbuf);

	// Allocate index buffer
	Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
	                                              Ogre::HardwareIndexBuffer::IT_16BIT,
	                                              ibufcount,
	                                              Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	// Upload the index data to the GPU
	ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);

	// Set parameters of the submesh
	submesh->useSharedVertices = true;
	submesh->indexData->indexBuffer = ibuf;
	submesh->indexData->indexCount = ibufcount;
	submesh->indexData->indexStart = 0;

	// Set bounding information for culling
	// ToDo set better bounds
	mesh->_setBounds(Ogre::AxisAlignedBox(-100, -100, -100, 100, 100, 100));
	mesh->_setBoundingSphereRadius(1000);

	mesh->load();
}

void Ygg::OgreRenderSystem::Convert(Ygg::Engine *engine, std::vector<Entity> *entity_queue)
{
	for (auto it = entity_queue->begin(); it != entity_queue->end(); ++it) {
		Entity *entity = &(*it);

		std::cout << "OGRE: Converting " << entity->name << std::endl;

		// Convert mesh
		MeshComponent *mesh_component = (MeshComponent*)engine->GetComponent(entity, SystemLoader::CID_MESH);
		if (mesh_component != NULL)
		{
			std::cout << "\tFound Mesh" << std::endl;
			convert_mesh(entity->name, &(*m_loader->GetMeshes())[mesh_component->mesh_handles[0]]);
			Ogre::Entity *ogre_entity = m_scenemgr->createEntity(entity->name, entity->name);
			ogre_entity->setMaterialName("DefaultMaterial");

			Ogre::SceneNode *ogre_node = m_scenemgr->getRootSceneNode()->createChildSceneNode();
			ogre_node->attachObject(ogre_entity);
			ogre_node->setPosition(0, 0, 0);
		}
	}
}

void Ygg::OgreRenderSystem::Update(Ygg::Engine *engine, float dt)
{
	m_root->renderOneFrame();
}
