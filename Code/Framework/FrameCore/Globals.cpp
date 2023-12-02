#include <FrameCore/Globals.h>

#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
//#include <FrameInput/InputManager.h>

namespace Frame {

	class CRenderer * gRenderer = new CRenderer {};
	class CEntitySystem * gEntitySystem = new CEntitySystem {};
	//class CInputManager * gInputManager = new CInputManager {};

	class CShader * gShaderInUsing = nullptr;

}