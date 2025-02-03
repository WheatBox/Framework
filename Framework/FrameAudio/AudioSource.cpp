#include <FrameAudio/AudioSource.h>

#include <FrameAsset/Sound.h>

#include <AL/al.h>

static inline bool _AlCompareSourceState(ALuint source, int compareTo) {
	int state;
	alGetSourcei(source, AL_SOURCE_STATE, & state);
	return state == compareTo;
}

static inline float _ALGetSourceF(ALuint source, ALenum param) {
	float val;
	alGetSourcef(source, param, & val);
	return val;
}

static inline bool _AlGetSourceBool(ALuint source, ALenum param) {
	int _alBool;
	alGetSourcei(source, param, & _alBool);
	return _alBool == AL_FALSE ? false : true;
}

static inline void _AlSourceBool(ALuint source, ALenum param, bool b) {
	alSourcei(source, param, b ? AL_TRUE : AL_FALSE);
}

namespace Frame {

	CAudioSource::CAudioSource() {
		alGenSources(1, & m_sourceId);
	}

	CAudioSource::~CAudioSource() {
		alDeleteSources(1, & m_sourceId);
	}

	void CAudioSource::Play(const CSound * pSound) {
		m_sound = pSound;
		alSourcei(m_sourceId, AL_BUFFER, pSound->GetBufferId());
		alSourcePlay(m_sourceId);
	}

	void CAudioSource::Stop() {
		m_sound = nullptr;
		alSourceStop(m_sourceId);
	}

	void CAudioSource::Pause() {
		alSourcePause(m_sourceId);
	}

	void CAudioSource::Resume() {
		alSourcePlay(m_sourceId);
	}

	bool CAudioSource::IsPlaying() const {
		return _AlCompareSourceState(m_sourceId, AL_PLAYING);
	}

	bool CAudioSource::HasPaused() const {
		return _AlCompareSourceState(m_sourceId, AL_PAUSED);
	}

	bool CAudioSource::HasStopped() const {
		return _AlCompareSourceState(m_sourceId, AL_STOPPED);
	}

	void CAudioSource::SetParams(const SAudioSourceParams & params) {
		SetPosition(params.vPos);
		SetPositionRelative(params.bPosRelative);
		SetGain(params.gain);
		SetPitch(params.pitch);
		SetLooping(params.loop);
	}

	Vec3 CAudioSource::GetPosition() const {
		Vec3 vPos;
		alGetSource3f(m_sourceId, AL_POSITION, & vPos.x, & vPos.y, & vPos.z);
		return vPos;
	}

	bool CAudioSource::GetPositionRelative() const {
		return _AlGetSourceBool(m_sourceId, AL_SOURCE_RELATIVE);
	}

	float CAudioSource::GetGain() const {
		return _ALGetSourceF(m_sourceId, AL_GAIN);
	}

	float CAudioSource::GetPitch() const {
		return _ALGetSourceF(m_sourceId, AL_PITCH);
	}

	bool CAudioSource::GetLooping() const {
		return _AlGetSourceBool(m_sourceId, AL_LOOPING);
	}

	float CAudioSource::GetMaxDistance() const {
		return _ALGetSourceF(m_sourceId, AL_MAX_DISTANCE);
	}

	float CAudioSource::GetRolloffFactor() const {
		return _ALGetSourceF(m_sourceId, AL_ROLLOFF_FACTOR);
	}

	float CAudioSource::GetReferenceDistance() const {
		return _ALGetSourceF(m_sourceId, AL_REFERENCE_DISTANCE);
	}

	void CAudioSource::SetPosition(const Vec3 & vPos) {
		alSource3f(m_sourceId, AL_POSITION, vPos.x, vPos.y, vPos.z);
	}

	void CAudioSource::SetPositionRelative(bool bRelative) {
		_AlSourceBool(m_sourceId, AL_SOURCE_RELATIVE, bRelative);
	}

	void CAudioSource::SetGain(float gain) {
		alSourcef(m_sourceId, AL_GAIN, gain);
	}

	void CAudioSource::SetPitch(float pitch) {
		alSourcef(m_sourceId, AL_PITCH, pitch);
	}

	void CAudioSource::SetLooping(bool bLooping) {
		_AlSourceBool(m_sourceId, AL_LOOPING, bLooping);
	}

	void CAudioSource::SetMaxDistance(float dis) {
		alSourcef(m_sourceId, AL_MAX_DISTANCE, dis);
	}

	void CAudioSource::SetRolloffFactor(float factor) {
		alSourcef(m_sourceId, AL_ROLLOFF_FACTOR, factor);
	}

	void CAudioSource::SetReferenceDistance(float dis) {
		alSourcef(m_sourceId, AL_REFERENCE_DISTANCE, dis);
	}

}