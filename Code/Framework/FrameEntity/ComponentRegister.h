#pragma once

#include <FrameUtility/GUID.h>

namespace Frame {

	template<typename ComponentType>
	struct SComponentType {
		static GUID s_guid;

		static void SetGUID(const char * sz) {
			s_guid.Set(sz);
		}

		static const GUID & GetGUID() {
			return s_guid;
		}
	};

	template<typename ComponentType>
	class CComponentRegister {
	public:
		CComponentRegister() {
			ComponentType::Register(SComponentType<ComponentType> {});
		}
		virtual ~CComponentRegister() = default;
	};

}

#define REGISTER_ENTITY_COMPONENT(ComponentType) \
	Frame::GUID Frame::SComponentType<ComponentType>::s_guid {}; \
	Frame::CComponentRegister<ComponentType> ___##ComponentType##Register {};
