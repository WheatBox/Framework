#include <FrameCore/IApplication.h>
#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameInput/Input.h>
#include <FrameAudio/AudioPlayer.h>
#include <FrameCore/Camera.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>

namespace Frame {

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

	Frame::Vec2i IApplication::GetWindowSize() const {
		int w = 0, h = 0;
		glfwGetWindowSize(m_pWindow, & w, & h);
		return { w, h };
	}

	void IApplication::SetWindowSize(const Frame::Vec2i & siz) {
		glfwSetWindowSize(m_pWindow, siz.x, siz.y);
	}

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

		gRenderer->Initialize();
		glfwSetFramebufferSizeCallback(m_pWindow,
			[](GLFWwindow * pWindow, int width, int height) {
				pWindow;
				glViewport(0, 0, width, height);
				gCamera->__SetWindowSize({ width, height });
			}
		);

		gInput->Initialize(m_pWindow);
		gAudioPlayer->Initialize();
		gCamera->__SetWindowSize({ windowWidth, windowHeight });
		gCamera->SetViewSize({ windowWidth, windowHeight });

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

			gEntitySystem->ProcessBeforeUpdateEvent(frameTime);
			gEntitySystem->ProcessUpdateEvent(frameTime);
			gEntitySystem->ProcessAfterUpdateEvent(frameTime);

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

}