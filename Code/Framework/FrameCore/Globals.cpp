#include <FrameCore/Globals.h>

#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameAsset/AssetsManager.h>

namespace Frame {

	class CRenderer * gRenderer = new CRenderer {};
	class CEntitySystem * gEntitySystem = new CEntitySystem {};
	class CAssetsManager * gAssetsManager = new CAssetsManager {};

}