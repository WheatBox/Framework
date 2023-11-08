#pragma once

#include <FrameEntity/EntityEvent.h>

#include <stdint.h>
#include <initializer_list>
#include <unordered_set>

namespace Frame {

	struct IEntityComponent;

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
		virtual void Add(IEntityComponent * pComponent) = 0;
		virtual void Remove(IEntityComponent * pComponent) = 0;

	};

	// 没有排序
	// No sorting
	class CEntityEventProcessor final : public CBaseEntityEventProcessor {
	private:
		std::unordered_set<IEntityComponent *> m_set;

	public:
		CEntityEventProcessor(EntityEvent::EFlag flag)
			: CBaseEntityEventProcessor(flag)
		{}

		virtual void Process() override;
		virtual void Add(IEntityComponent * pComponent) override;
		virtual void Remove(IEntityComponent * pComponent) override;
	};

	// 在 Join() 时，立刻生效
	// Effective immediately, when Join().
	class CEntityEventProcessorImmediately final : public CBaseEntityEventProcessor {
	public:
		CEntityEventProcessorImmediately(EntityEvent::EFlag flag)
			: CBaseEntityEventProcessor(flag)
		{}

		virtual void Add(IEntityComponent * pComponent) override;

	private:
		virtual void Process() override {}
		virtual void Remove(IEntityComponent * pComponent) override { pComponent; }
	};

	// 根据 IEntity::m_zDepth 进行排序
	// Sort according to IEntity::m_zDepth
	class CEntityEventProcessorZSort final : public CBaseEntityEventProcessor {
	private:
		std::unordered_set<IEntityComponent *> m_set;

	public:
		CEntityEventProcessorZSort(EntityEvent::EFlag flag)
			: CBaseEntityEventProcessor(flag)
		{}

		virtual void Process() override;
		virtual void Add(IEntityComponent * pComponent) override;
		virtual void Remove(IEntityComponent * pComponent) override;
	};

}