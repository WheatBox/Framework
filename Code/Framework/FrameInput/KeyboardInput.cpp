#include <FrameInput/KeyboardInput.h>

namespace Frame {

	void CKeyboardInput::ProcessChanges() {

		bool bPressedInCurrentFrame = false;

		for(size_t siz = m_changes.size(); siz > 0; siz--) {

			SInputStateChange & change = m_changes.front();

			auto it = m_stateMap.find(change.keyId);
			if(it == m_stateMap.end()) {
				m_stateMap.insert({ change.keyId, EInputState::eIS_Nothing });
				it = m_stateMap.find(change.keyId);
			}

			if(change.bIsRemoveMode) {
				it->second &= ~change.state;
			} else {

				switch(change.state) {
				case EInputState::eIS_Press:

					it->second = EInputState::eIS_Press | EInputState::eIS_Hold;
					bPressedInCurrentFrame = true;

					// 这个 push_back 意味着下一帧时执行
					// This push_back means to execute on the next frame
					m_changes.push_back({ change.keyId, EInputState::eIS_Press, true });
					break;

				case EInputState::eIS_Release:

					// Press 和 Release 是否发生在同一帧里
					// Does Press and Release occur in the same frame
					if(bPressedInCurrentFrame) {
						it->second |= EInputState::eIS_Release;
						m_changes.push_back({ change.keyId, EInputState::eIS_Press, true });
						m_changes.push_back({ change.keyId, EInputState::eIS_Hold, true });
					} else {
						it->second = EInputState::eIS_Release;
					}

					m_changes.push_back({ change.keyId, EInputState::eIS_Release, true });
					break;
				}

			}

			m_changes.pop_front();
		}
	}

}