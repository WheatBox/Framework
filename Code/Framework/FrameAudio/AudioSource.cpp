#include <FrameAudio/AudioSource.h>

#include <FrameAsset/Sound.h>

#include <AL/al.h>

namespace Frame {

	CAudioSource::CAudioSource(const SAudioPlaySoundParams & params) {
		alGenSources(1, & m_sourceId);
		SetPosition(params.vPos);
		SetPositionRelative(params.bPosRelative);
		SetGain(params.gain);
		SetPitch(params.pitch);
	}

	CAudioSource::~CAudioSource() {
		alDeleteSources(1, & m_sourceId);
	}

	void CAudioSource::Play(const CSound * pSound) {
		m_soundPlaying = pSound;
		alSourcei(m_sourceId, AL_BUFFER, pSound->GetBufferId());
		alSourcePlay(m_sourceId);
	}

	void CAudioSource::Stop() {
		m_soundPlaying = nullptr;
		alSourceStop(m_sourceId);
	}

	bool CAudioSource::IsPlaying() const {
		int state;
		alGetSourcei(m_sourceId, AL_SOURCE_STATE, & state);
		return state == AL_PLAYING;
	}

	Vec3 CAudioSource::GetPosition() const {
		Vec3 vPos;
		alGetSource3f(m_sourceId, AL_POSITION, & vPos.x, & vPos.y, & vPos.z);
		return vPos;
	}

	bool CAudioSource::GetPositionRelative() const {
		int relative_alBool;
		alGetSourcei(m_sourceId, AL_SOURCE_RELATIVE, & relative_alBool);
		return relative_alBool == AL_FALSE ? false : true;
	}

	float CAudioSource::GetGain() const {
		float gain;
		alGetSourcef(m_sourceId, AL_GAIN, & gain);
		return gain;
	}

	float CAudioSource::GetPitch() const {
		float pitch;
		alGetSourcef(m_sourceId, AL_PITCH, & pitch);
		return pitch;
	}

	void CAudioSource::SetPosition(const Vec3 & vPos) {
		alSource3f(m_sourceId, AL_POSITION, vPos.x, vPos.y, vPos.z);
	}

	void CAudioSource::SetPositionRelative(bool bRelative) {
		alSourcei(m_sourceId, AL_SOURCE_RELATIVE, bRelative ? AL_TRUE : AL_FALSE);
	}

	void CAudioSource::SetGain(float gain) {
		alSourcef(m_sourceId, AL_GAIN, gain);
	}

	void CAudioSource::SetPitch(float pitch) {
		alSourcef(m_sourceId, AL_PITCH, pitch);
	}

}