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

		void SetMasterGain(float gain);
		float GetMasterGain() const {
			return m_masterGain;
		}

		void SetListenerPosition(const Vec3 & vPos);
		const Vec3 & GetListenerPosition() const {
			return m_vListenerPos;
		}

		// TODO - 暂时没有足够好的3D音频设备来进行测试正确性
		//        There are currently not enough good 3D audio devices to test for correctness
		void SetListenerOrientation(const Vec3 & vLookTo, const Vec3 & vUp);
		const std::pair<Vec3, Vec3> & GetListenerOrientation() const {
			return m_listenerOrientation;
		}

		std::shared_ptr<CAudioSource> PlaySound(const CSound * pSound, const SAudioSourceParams & params);

	public:
		enum class EFalloffModel {
			None = 0,                         // AL_NONE
			InverseDistance = 0xD001,         // AL_INVERSE_DISTANCE
			InverseDistanceClamped = 0xD002,  // AL_INVERSE_DISTANCE_CLAMPED
			LinearDistance = 0xD003,          // AL_LINEAR_DISTANCE
			LinearDistanceClamped = 0xD004,   // AL_LINEAR_DISTANCE_CLAMPED
			ExponentDistance = 0xD005,        // AL_EXPONENT_DISTANCE
			ExponentDistanceClamped = 0xD006, // AL_EXPONENT_DISTANCE_CLAMPED
		};

		void SetFalloffModel(EFalloffModel falloffModel);

	private:
		float m_masterGain = 1.f;
		Vec3 m_vListenerPos { 0.f };
		std::pair<Vec3, Vec3> m_listenerOrientation {
			{ 0.f, -1.f, 0.f }, // Look to
			{ 0.f, 0.f, -1.f } // Up
		};

		std::list<std::shared_ptr<CAudioSource>> m_audioSources;
	};

}