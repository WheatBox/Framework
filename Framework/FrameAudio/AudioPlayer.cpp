#include <FrameAudio/AudioPlayer.h>

#include <FrameCore/Log.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <algorithm>

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

		SetListenerPosition(m_vListenerPos);
		SetListenerOrientation(m_listenerOrientation.first, m_listenerOrientation.second);
	}

	void CAudioPlayer::Process() {
		m_audioSources.erase(std::remove_if(m_audioSources.begin(), m_audioSources.end(),
			[](std::shared_ptr<CAudioSource> p) {
				return p->HasStopped();
			}),
			m_audioSources.end()
		);
	}

	void CAudioPlayer::SetMasterGain(float gain) {
		m_masterGain = gain;
		alListenerf(AL_GAIN, gain);
	}

	void CAudioPlayer::SetListenerPosition(const Vec3 & vPos) {
		m_vListenerPos = vPos;
		alListener3f(AL_POSITION, vPos.x, vPos.y, vPos.z);
	}

	void CAudioPlayer::SetListenerOrientation(const Vec3 & vLookTo, const Vec3 & vUp) {
		m_listenerOrientation = { vLookTo, vUp };
		float arr[6] = {
			vLookTo.x, vLookTo.y, vLookTo.z,
			vUp.x, vUp.y, vUp.z
		};
		alListenerfv(AL_ORIENTATION, arr);
	}

	std::shared_ptr<CAudioSource> CAudioPlayer::PlaySound(const CSound * pSound, const SAudioSourceParams & params) {
		std::shared_ptr res = std::make_shared<CAudioSource>();
		res->SetParams(params);
		res->Play(pSound);
		m_audioSources.push_back(res);
		return res;
	}

	void CAudioPlayer::SetFalloffModel(EFalloffModel falloffModel) {
		alDistanceModel(static_cast<ALenum>(falloffModel));
	}

}
