#pragma once

#include <FrameInput/InputEnums.h>

#include <unordered_map>
#include <list>

namespace Frame {

	template<typename EButtonInputIdType>
	class CButtonInputBase {
	private:
		typedef std::unordered_map<EButtonInputIdType, InputStateT> StateMap;

		StateMap m_stateMap;
		/* TODO or not - 在 eIS_Nothing 时，从表中删除该键
		 *               但我感觉应该不差这点内存，所以就没做
		 *               以后要不要做，不知道
		 *               Remove the key from the table when it is eIS_Nothing
		 *               But I think that don't lack such a little memory, so I didn't work on it
		 *               Whether or not to do it in the future. I don't know.
		 */

		struct SInputStateChange {
			EButtonInputIdType inputId;
			EInputState state;
			bool bIsRemoveMode = false;
		};

		std::list<SInputStateChange> m_changes;

	public:

		void __ButtonCallback(int button, int action) {
			switch(action) {
			case 0: // GLFW_RELEASE
				SetInputState(static_cast<EButtonInputIdType>(button), EInputState::eIS_Release);
				break;
			case 1: // GLFW_PRESS
				SetInputState(static_cast<EButtonInputIdType>(button), EInputState::eIS_Press);
				break;
			}
		}

		void __ProcessChanges() {
			bool bPressedInCurrentFrame = false;

			for(size_t siz = m_changes.size(); siz > 0; siz--) {

				SInputStateChange & change = m_changes.front();

				auto it = m_stateMap.find(change.inputId);
				if(it == m_stateMap.end()) {
					m_stateMap.insert({ change.inputId, EInputState::eIS_Nothing });
					it = m_stateMap.find(change.inputId);
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
						m_changes.push_back({ change.inputId, EInputState::eIS_Press, true });
						break;

					case EInputState::eIS_Release:

						// Press 和 Release 是否发生在同一帧里
						// Does Press and Release occur in the same frame
						if(bPressedInCurrentFrame) {
							it->second |= EInputState::eIS_Release;
							m_changes.push_back({ change.inputId, EInputState::eIS_Press, true });
							m_changes.push_back({ change.inputId, EInputState::eIS_Hold, true });
						} else {
							it->second = EInputState::eIS_Release;
						}

						m_changes.push_back({ change.inputId, EInputState::eIS_Release, true });
						break;
					}

				}

				m_changes.pop_front();
			}
		}

		void SetInputState(EButtonInputIdType inputId, EInputState state) {
			m_changes.push_back({ inputId, state });
		}

		InputStateT GetInputState(EButtonInputIdType inputId) const {
			auto it = m_stateMap.find(inputId);
			if(it != m_stateMap.end()) {
				return it->second;
			}
			return EInputState::eIS_Nothing;
		}

		bool CheckInputState(EButtonInputIdType inputId, InputStateT states) const {
			return GetInputState(inputId) & states;
		}

		bool GetPressed(EButtonInputIdType inputId) const {
			return CheckInputState(inputId, EInputState::eIS_Press);
		}
		bool GetHolding(EButtonInputIdType inputId) const {
			return CheckInputState(inputId, EInputState::eIS_Hold);
		}
		bool GetReleased(EButtonInputIdType inputId) const {
			return CheckInputState(inputId, EInputState::eIS_Release);
		}

	};
}