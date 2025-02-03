#pragma once

#ifdef _WIN32
#ifdef FRAMEWORK_EXPORTS
#define FRAME_API __declspec(dllexport)
#else
#define FRAME_API __declspec(dllimport)
#endif
#else
#define FRAME_API
#endif

namespace Frame {

	extern FRAME_API class CRenderer * gRenderer;
	extern FRAME_API class CEntitySystem * gEntitySystem;
	extern FRAME_API class CInput * gInput;
	extern FRAME_API class CAudioPlayer * gAudioPlayer;
	extern FRAME_API class CCamera * gCamera;

	extern FRAME_API class CShader * gShaderInUsing;

}
