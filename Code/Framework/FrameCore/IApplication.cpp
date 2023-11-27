#include <FrameCore/IApplication.h>
#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
//#include <FrameEntity/EntityEventProcessor.h>
//#include <FrameInput/InputManager.h>

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
			// TODO 错误消息
			return false;
		}
		glfwMakeContextCurrent(m_pWindow);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			// TODO 错误消息
			return false;
		}

		Shader * _pSpriteShader = new Shader {}, * _pSolidColorShader = new Shader {};
		InitializeRendererShaders(_pSpriteShader, _pSolidColorShader);
		gRenderer->Initialize(windowWidth, windowHeight, _pSpriteShader, _pSolidColorShader);

		glfwSetFramebufferSizeCallback(m_pWindow,
			[](GLFWwindow * pWindow, int width, int height) {
				pWindow;
				glViewport(0, 0, width, height);
				gRenderer->FramebufferResizeCallback(width, height);
			}
		);

		return true;
	}

	void IApplication::Run() {
		while(!glfwWindowShouldClose(m_pWindow)) {
			static std::chrono::steady_clock::time_point prevTimePoint = std::chrono::steady_clock::now(), beforeLoopTimePoint;
			static float frameTime = 0.f;

			beforeLoopTimePoint = std::chrono::steady_clock::now();

			frameTime = std::chrono::duration<float>(beforeLoopTimePoint - prevTimePoint).count();
			prevTimePoint = beforeLoopTimePoint;

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

	void IApplication::InitializeRendererShaders(Shader * _pSpriteShader, Shader * _pSolidColorShader) {
		if(!_pSpriteShader->CompileFiles("./Shaders/Sprite.vert", "./Shaders/Sprite.frag")) {
			// TODO - 警告信息
			_pSpriteShader->Compile(
				"#version 330 core\n"
				"layout (location = 0) in vec3 aPos;"
				"layout (location = 1) in vec4 aColor;"
				"layout (location = 2) in vec2 aTexCoord;"
				"out vec4 vColor;"
				"out vec2 vTexCoord;"
				"void main() {"
				"	gl_Position = vec4(aPos, 1.f);"
				"	vColor = aColor;"
				"	vTexCoord = aTexCoord;"
				"}"
				,
				"#version 330 core\n"
				"in vec4 vColor;"
				"in vec2 vTexCoord;"
				"uniform sampler2D u_BaseTexture;"
				"void main() {"
				"	gl_FragColor = texture(u_BaseTexture, vTexCoord) * vColor;"
				"}"
			);
		}
		_pSpriteShader->SetUniformInt("u_BaseTexture", 0);

		if(!_pSolidColorShader->CompileFiles("./Shaders/SolidColor.vert", "./Shaders/SolidColor.frag")) {
			// TODO - 警告信息
			_pSolidColorShader->Compile(
				"#version 330 core\n"
				"layout (location = 0) in vec3 aPos;"
				"layout (location = 1) in vec4 aColor;"
				"out vec4 vColor;"
				"void main() {"
				"	gl_Position = vec4(aPos, 1.f);"
				"	vColor = aColor;"
				"}"
				,
				"#version 330 core\n"
				"in vec4 vColor;"
				"void main() {"
				"	gl_FragColor = vColor;"
				"}"
			);
		}
	}

	void IApplication::SetVSync(bool bEnable) {
		m_bVSync = bEnable;
		glfwSwapInterval(bEnable);
	}

	void IApplication::Terminate() {
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