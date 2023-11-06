#pragma once

#include <FrameCore/IApplication.h>

class CDiaryApplication final : public Frame::IApplication {

protected:
	virtual void ProcessSdlEvent(SDL_Event & sdlEvent) override;

	virtual void MainLoopPriority() override;
	virtual void MainLoopLast() override {};
};