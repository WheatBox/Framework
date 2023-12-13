#include <FrameCore/Globals.h>

#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameInput/Input.h>

namespace Frame {

	class CRenderer * gRenderer = new CRenderer {};
	class CEntitySystem * gEntitySystem = new CEntitySystem {};
	class CInput * gInput = new CInput {};

	class CShader * gShaderInUsing = nullptr;

}