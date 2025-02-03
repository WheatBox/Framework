#pragma once

// TODO - 距离衰减

#include <FrameMath/Vector3.h>

#include <memory>

namespace Frame {

	class CSound;

	struct SAudioSourceParams {
		Vec3 vPos { 0.f };
		bool bPosRelative = false;
		
		float gain = 1.f;
		float pitch = 1.f;
		
		bool loop = false;

		float maxDistance = 10000.f;
		float rolloffFactor = 1.f;
		float referenceDistance = 1.f;
	};

	class CAudioSource {
	public:
		CAudioSource();
		virtual ~CAudioSource();

		// 如果是想从暂停中恢复，使用 Resume()
		// If you want to resume from the pause, use Resume()
		void Play(const CSound * pSound);
		// 如果是想暂停而不是终止，使用 Pause()
		// If you want to pause instead of stop, use Pause()
		void Stop();
		void Pause();
		void Resume();

		const CSound * GetSound() const { return m_sound; }

		bool IsPlaying() const;
		bool HasPaused() const;
		bool HasStopped() const;

		void SetParams(const SAudioSourceParams & params);

		Vec3 GetPosition() const;
		bool GetPositionRelative() const;
		float GetGain() const;
		float GetPitch() const;
		bool GetLooping() const;
		float GetMaxDistance() const;
		float GetRolloffFactor() const;
		float GetReferenceDistance() const;

		void SetPosition(const Vec3 & vPos);
		void SetPositionRelative(bool bRelative);
		void SetGain(float gain);
		void SetPitch(float pitch);
		void SetLooping(bool bLooping);
		void SetMaxDistance(float dis);
		void SetRolloffFactor(float factor);
		void SetReferenceDistance(float dis);

	private:
		unsigned int m_sourceId = 0;

		const CSound * m_sound = nullptr;
	};

}