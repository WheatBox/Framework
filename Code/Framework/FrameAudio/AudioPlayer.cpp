#include <FrameAudio/AudioPlayer.h>

#include <FrameCore/Log.h>

#include <AL/al.h>
#include <AL/alc.h>

namespace Frame {

	CAudioPlayer::~CAudioPlayer() {
		alcDestroyContext(m_pContext);
		alcCloseDevice(m_pDevice);
	}

	void CAudioPlayer::Initialize() {
		m_pDevice = alcOpenDevice(nullptr);

		if(m_pDevice) {
			m_pContext = alcCreateContext(m_pDevice, nullptr);
			alcMakeContextCurrent(m_pContext);
		} else {
			m_pContext = nullptr;
			Log::Log(Log::ELevel::Error, "Failed to open audio device. Error message: %s", alGetError());
			return;
		}

		SetListenerPosition({});
	}

	void CAudioPlayer::Process() {
		m_audioSources.erase(std::remove_if(m_audioSources.begin(), m_audioSources.end(),
			[](std::shared_ptr<CAudioSource> p) {
				return !p->IsPlaying();
			}),
			m_audioSources.end()
		);
	}

	void CAudioPlayer::SetListenerPosition(const Vec3 & vPos) {
		m_vListenerPos = vPos;
		alListener3f(AL_POSITION, vPos.x, vPos.y, vPos.z);
	}

	std::shared_ptr<CAudioSource> CAudioPlayer::PlaySound(const CSound * pSound, const SAudioPlaySoundParams & params) {
		std::shared_ptr res = std::make_shared<CAudioSource>(params);
		res->Play(pSound);
		m_audioSources.push_back(res);
		return res;
	}

	void CAudioPlayer::StopSound(std::shared_ptr<CAudioSource> pAudioSourceWhichIsPlayingSound) {
		pAudioSourceWhichIsPlayingSound->Stop();
	}

}