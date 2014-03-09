#ifndef YGG_OGRERENDER_H
#define YGG_OGRERENDER_H

#include "core/system.h"

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
	class Camera;
}

namespace Ygg {

class Engine;
class SystemLoader;
class Mesh;

/**
 * System for using Ogre for rendering.
 */
class OgreRenderSystem: public System
{
public:
	OgreRenderSystem(unsigned long window, SystemLoader *loader);
	~OgreRenderSystem();

	virtual void Init(Engine *engine);

	virtual void Convert(Engine *engine, std::vector<Entity>* entity_queue);

	virtual void Update(Engine *engine, float dt);

private:
	unsigned long m_parentwindow;
	Ogre::Root *m_root;
	Ogre::RenderWindow *m_window;
	Ogre::SceneManager *m_scenemgr;
	Ogre::Camera *m_camera;
	SystemLoader *m_loader;

	void ConvertMesh(Ygg::Mesh *mdata);
};

} // end namespace

#endif // YGG_OGRERENDER_H
