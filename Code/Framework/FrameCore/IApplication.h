#pragma once

#include <chrono> // for m_maxFrameDelay

struct SDL_Window;
union SDL_Event;

namespace Frame {

	struct IApplication {
	protected:
		SDL_Window * m_sdlWindow = nullptr;

	public:
		virtual int EntryPoint(int argc, char ** argv) {
			argc, argv;
			InitializeWindow("Framework", 800, 600);
			Run();
			return 0;
		}

	protected:

		bool InitializeWindow(const char * title, int windowWidth, int windowHeight);
		void Run();

		virtual void Initialize() {}

		virtual void ProcessSdlEvent(SDL_Event & sdlEvent);

		virtual void MainLoopPriority() {}
		virtual void MainLoopLast() {}

		int GetMaxFPS() const { return m_maxFPS; }
		// 0 = 无限大 | Infinite
		void SetMaxFPS(int fps) {
			m_maxFPS = fps > 0 ? fps : 0;

			if(m_maxFPS != 0) {
				m_maxFrameDelay = std::chrono::microseconds(1000000 / fps);
			}
		}

		int m_maxFPS = 0;

		bool m_quit = false;

	private:
		std::chrono::microseconds m_maxFrameDelay { 0 };

	};

}