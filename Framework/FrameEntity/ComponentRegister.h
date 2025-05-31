#pragma once

#include "../FrameUtility/GUID.h"

namespace Frame {

	struct SComponentTypeConfig {
	private:
		GUID guid;

	public:
		void SetGUID(const char * sz) { guid.Set(sz); }
		const GUID & GetGUID() const { return guid; }
	};

	template<typename ComponentType>
	struct SComponentType {
		static SComponentTypeConfig config;
	};

	template<typename ComponentType>
	class __ComponentRegister {
	public:
		__ComponentRegister() {
			ComponentType::Register(SComponentType<ComponentType>::config);
		}
		virtual ~__ComponentRegister() = default;
	};

}

#define __REGISTER_ENTITY_COMPONENT__MAKE_NAME_(n) ___RegisterEntityComponent_##n
#define __REGISTER_ENTITY_COMPONENT__MAKE_NAME(n) __REGISTER_ENTITY_COMPONENT__MAKE_NAME_(n)

#define REGISTER_ENTITY_COMPONENT(ComponentType) \
namespace Frame { \
	template<> SComponentTypeConfig SComponentType<ComponentType>::config {}; \
	__ComponentRegister<ComponentType> __REGISTER_ENTITY_COMPONENT__MAKE_NAME(__COUNTER__) {}; \
}
