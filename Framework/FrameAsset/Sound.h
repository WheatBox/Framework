#pragma once

namespace Frame {

	class CSound {
	public:
		CSound() = delete;

		// 如果你的音效是要在游戏中作为实时的立体音存在的（根据各个角色的位置实时改变声音在空间中的位置），
		// 那么请将立体声转单声道，也就是将第二个参数填写 true
		// If your sound effects are to exist as real-time stereo sound in the game
		// (changing the position of the sound in space in real time according to the position of each character),
		// then please convert the stereo sound to mono, that is, fill in the second parameter with true
		CSound(const char * filename, bool stereoToMono_ifItIsStereo = false);
		virtual ~CSound();

		unsigned int GetBufferId() const {
			return m_bufferId;
		}

	private:
		unsigned int m_bufferId = 0;
	};

}
