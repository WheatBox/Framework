#include <FrameCore/IApplication.h>
#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameInput/Input.h>
#include <FrameAudio/AudioPlayer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>

namespace Frame {

	bool IApplication::InitializeWindow(const char * title, int windowWidth, int windowHeight) {
		
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		m_pWindow = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
		if(!m_pWindow) {
			Log::Log(Log::ELevel::Fatal, "Failed to create the window \"%s\"", title);
			return false;
		}
		glfwMakeContextCurrent(m_pWindow);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Log::Log(Log::ELevel::Fatal, "Failed to initialize GLAD");
			return false;
		}

		gRenderer->Initialize(windowWidth, windowHeight);
		glfwSetFramebufferSizeCallback(m_pWindow,
			[](GLFWwindow * pWindow, int width, int height) {
				pWindow;
				glViewport(0, 0, width, height);
				gRenderer->FramebufferResizeCallback(width, height);
			}
		);

		gInput->Initialize(m_pWindow);
		gAudioPlayer->Initialize();

		return true;
	}

	void IApplication::Run() {
		while(!glfwWindowShouldClose(m_pWindow)) {
			static std::chrono::steady_clock::time_point prevTimePoint = std::chrono::steady_clock::now(), beforeLoopTimePoint;
			static float frameTime = 0.f;

			beforeLoopTimePoint = std::chrono::steady_clock::now();

			frameTime = std::chrono::duration<float>(beforeLoopTimePoint - prevTimePoint).count();
			prevTimePoint = beforeLoopTimePoint;

			gInput->Process();
			gAudioPlayer->Process();

			gRenderer->RenderBegin();

			MainLoopPriority();
			/* ------------- Main Loop ------------- */

			gEntitySystem->ProcessUpdateEvent(frameTime);

			gEntitySystem->ProcessRenderEvent();

			/* ------------------------------------- */
			MainLoopLast();

			gRenderer->RenderEnd();

			glfwSwapBuffers(m_pWindow);
			glfwPollEvents();

			if(!m_bVSync && m_maxFPS != 0) {
				std::this_thread::sleep_until(beforeLoopTimePoint + m_maxFrameDelay);
			}
		}

		Terminate();
	}

	void IApplication::SetVSync(bool bEnable) {
		m_bVSync = bEnable;
		glfwSwapInterval(bEnable);
	}

	void IApplication::Terminate() {
		delete gRenderer;
		gRenderer = nullptr;
		
		delete gEntitySystem;
		gEntitySystem = nullptr;
		
		delete gInput;
		gInput = nullptr;

		delete gAudioPlayer;
		gAudioPlayer = nullptr;

		delete gShaderInUsing;
		gShaderInUsing = nullptr;

		glfwTerminate();
	}

#if 0

	void IApplication::ProcessSdlEvent(SDL_Event & sdlEvent) {
		switch(sdlEvent.type) {
		case SDL_EventType::SDL_QUIT:
			m_quit = true;
			break;
		case SDL_EventType::SDL_KEYDOWN:
			 SDL_Log("DOWN %d | %s", sdlEvent.key.keysym.sym, SDL_GetKeyName(sdlEvent.key.keysym.sym));
			gInputManager->pKeyboard->SetInputState(static_cast<EInputKeyId>(sdlEvent.key.keysym.sym), EInputState::eIS_Press);
			break;
		case SDL_EventType::SDL_KEYUP:
			gInputManager->pKeyboard->SetInputState(static_cast<EInputKeyId>(sdlEvent.key.keysym.sym), EInputState::eIS_Release);
			break;
		}
	}
#endif

}