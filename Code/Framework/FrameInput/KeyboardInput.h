#pragma once

#include <FrameInput/InputEnums.h>

#include <unordered_map>
#include <list>

namespace Frame {

	class CKeyboardInput {

		typedef std::unordered_map<EInputKeyId, InputStateT> StateMap;

		StateMap m_stateMap;
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

		void ProcessChanges();

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