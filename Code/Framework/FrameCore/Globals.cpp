#include <FrameCore/Globals.h>

#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameInput/Input.h>
#include <FrameAudio/AudioPlayer.h>

namespace Frame {

	class CRenderer * gRenderer = new CRenderer {};
	class CEntitySystem * gEntitySystem = new CEntitySystem {};
	class CInput * gInput = new CInput {};
	class CAudioPlayer * gAudioPlayer = new CAudioPlayer {};

	class CShader * gShaderInUsing = nullptr;

}