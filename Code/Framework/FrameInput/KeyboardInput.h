#pragma once

#include <FrameInput/InputEnums.h>

#include <unordered_map>
#include <list>

namespace Frame {

	class CKeyboardInput {

		typedef std::unordered_map<EInputKeyId, InputStateT> StateMapT;

		StateMapT m_stateMap;
		/* TODO or not - 在 eIS_Nothing 时，从表中删除该键
		 *               但我感觉应该不差这点内存，所以就没做
		 *               以后要不要做，不知道
		 *               Remove the key from the table when it is eIS_Nothing
		 *               But I think that don't lack such a little memory, so I didn't work on it
		 *               Whether or not to do it in the future. I don't know.
		 */

		struct SInputStateChange {
			EInputKeyId keyId;
			EInputState state;
			bool bIsRemoveMode = false;
		};

		std::list<SInputStateChange> m_changes;

	public:

		void ProcessChanges() {

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

		void SetInputState(EInputKeyId keyId, EInputState state) {
			m_changes.push_back({ keyId, state });
		}

		InputStateT GetInputState(EInputKeyId keyId) const {
			auto it = m_stateMap.find(keyId);
			if(it != m_stateMap.end()) {
				return it->second;
			}
			return EInputState::eIS_Nothing;
		}

		bool CheckInputState(EInputKeyId keyid, InputStateT states) const {
			return GetInputState(keyid) & states;
		}

		bool GetPressed(EInputKeyId keyId) const {
			return CheckInputState(keyId, EInputState::eIS_Press);
		}
		bool GetHolding(EInputKeyId keyId) const {
			return CheckInputState(keyId, EInputState::eIS_Hold);
		}
		bool GetReleased(EInputKeyId keyId) const {
			return CheckInputState(keyId, EInputState::eIS_Release);
		}

	};

}