#include "system_loader.h"
#include "engine.h"

DEFINE_COMPONENTID(Ygg::SystemLoader, MESH);
DEFINE_COMPONENTID(Ygg::SystemLoader, LIGHT);

void Ygg::SystemLoader::Init(Ygg::Engine *engine)
{
	REGISTER_COMPONENTID(MESH);
	REGISTER_COMPONENTID(LIGHT);
}
