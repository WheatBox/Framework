#pragma once

#include <FrameEntity/EntityEvent.h>

#include <initializer_list>
#include <stdint.h>
#include <unordered_set>
#include <unordered_map>

namespace Frame {

	struct IEntity;

	class CBaseEntityEventProcessor {
	protected:
		EntityEvent::SEvent m_event;

	public:
		CBaseEntityEventProcessor() = delete;
		CBaseEntityEventProcessor(EntityEvent::EFlag flag) {
			m_event.flag = flag;
		}
		virtual ~CBaseEntityEventProcessor() = default;

		void SetEventParam(Uint8 index, EntityEvent::SEvent::UParam param) {
			m_event.params[index] = param;
		}

		void SetEventParams(std::initializer_list<EntityEvent::SEvent::UParam> params) {
			Uint8 i = 0;
			for(auto & param : params) {
				m_event.params[i++] = param;
			}
		}

		virtual void Process() = 0;
		virtual void Join(IEntity * pEntity) = 0;
		virtual void Remove(IEntity * pEntity) = 0;

	};
	
	// 没有排序
	// No sorting
	class CEntityEventProcessor final : public CBaseEntityEventProcessor {
	private:
		std::unordered_set<IEntity *> m_set;

	public:
		CEntityEventProcessor(EntityEvent::EFlag flag)
			: CBaseEntityEventProcessor(flag)
		{}

		virtual void Process() override;
		virtual void Join(IEntity * pEntity) override;
		virtual void Remove(IEntity * pEntity) override;
	};

	// 根据 IEntity::z 进行排序
	// Sort according to IEntity::z
	class CEntityEventProcessorZSort final : public CBaseEntityEventProcessor {
	private:
		std::unordered_map<int, IEntity *> m_map;

	public:
		CEntityEventProcessorZSort(EntityEvent::EFlag flag)
			: CBaseEntityEventProcessor(flag)
		{}

		virtual void Process() override;
		virtual void Join(IEntity * pEntity) override;
		virtual void Remove(IEntity * pEntity) override;
	};

}