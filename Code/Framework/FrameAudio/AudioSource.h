#pragma once

// TODO - 距离衰减

#include <FrameMath/Vector3.h>

#include <memory>

namespace Frame {

	class CSound;

	struct SAudioPlaySoundParams {
		Vec3 vPos { 0.f };
		bool bPosRelative = false;
		float gain = 1.f;
		float pitch = 1.f;
	};

	class CAudioSource {
	public:
		CAudioSource()
			: CAudioSource({{}})
		{}
		CAudioSource(const SAudioPlaySoundParams & params);
		virtual ~CAudioSource();

		void Play(const CSound * pSound);
		void Stop();

		const CSound * GetSound() const { return m_soundPlaying; }
		bool IsPlaying() const;

		Vec3 GetPosition() const;
		bool GetPositionRelative() const;
		float GetGain() const;
		float GetPitch() const;

		void SetPosition(const Vec3 & vPos);
		void SetPositionRelative(bool bRelative);
		void SetGain(float gain);
		void SetPitch(float pitch);

	private:
		unsigned int m_sourceId = 0;

		const CSound * m_soundPlaying = nullptr;
		bool m_bFollowListener = false;
	};

}