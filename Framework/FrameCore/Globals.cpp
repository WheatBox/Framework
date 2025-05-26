#include "Globals.h"

#include "../FrameRender/Renderer.h"
#include "../FrameEntity/EntitySystem.h"
#include "../FrameInput/Input.h"
#include "../FrameAudio/AudioPlayer.h"
#include "../FrameCore/Camera.h"

namespace Frame {

	FRAME_API class CRenderer * gRenderer = new CRenderer {};
	FRAME_API class CEntitySystem * gEntitySystem = new CEntitySystem {};
	FRAME_API class CInput * gInput = new CInput {};
	FRAME_API class CAudioPlayer * gAudioPlayer = new CAudioPlayer {};
	FRAME_API class CCamera * gCamera = new CCamera {};

	FRAME_API class CShader * gShaderInUsing = nullptr;

}