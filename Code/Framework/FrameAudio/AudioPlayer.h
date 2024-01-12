#pragma once

#include <FrameMath/Vector3.h>

#include <FrameAudio/AudioSource.h>

#include <memory>
#include <list>

struct ALCdevice;
struct ALCcontext;

namespace Frame {

	class CSound;

	class CAudioPlayer {
	private:
		ALCdevice * m_pDevice;
		ALCcontext * m_pContext;

	public:
		CAudioPlayer() = default;
		virtual ~CAudioPlayer();

		void Initialize();
		void Process();

		void SetListenerPosition(const Vec3 & vPos);
		const Vec3 & GetListenerPosition() const {
			return m_vListenerPos;
		}

		std::shared_ptr<CAudioSource> PlaySound(const CSound * pSound, const SAudioPlaySoundParams & params);

		void StopSound(std::shared_ptr<CAudioSource> pAudioSourceWhichIsPlayingSound);

	private:
		Vec3 m_vListenerPos {};
		std::list<std::shared_ptr<CAudioSource>> m_audioSources;
	};

}