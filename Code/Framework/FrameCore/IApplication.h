#pragma once

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

		virtual void ProcessSdlEvent(SDL_Event & sdlEvent);

		virtual void MainLoopPriority() {}
		virtual void MainLoopLast() {}

		bool m_quit = false;

	};

}