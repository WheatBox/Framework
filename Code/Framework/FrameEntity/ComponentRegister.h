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
	template<> Frame::GUID Frame::SComponentType<ComponentType>::s_guid {}; \
	Frame::CComponentRegister<ComponentType> ___Register##ComponentType##__COUNTER__ {};
/*
#define REGISTER_ENTITY_COMPONENT(Namespace, ComponentType) \
	Frame::GUID Frame::SComponentType<Namespace::ComponentType>::s_guid {}; \
	Frame::CComponentRegister<Namespace::ComponentType> ___##ComponentType##Register {};
*/
