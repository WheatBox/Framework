#pragma once

#include <FrameUtility/GUID.h>

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

#define REGISTER_ENTITY_COMPONENT(ComponentType) \
	template<> Frame::SComponentTypeConfig Frame::SComponentType<ComponentType>::config {}; \
	Frame::__ComponentRegister<ComponentType> ___Register##ComponentType##__COUNTER__ {};