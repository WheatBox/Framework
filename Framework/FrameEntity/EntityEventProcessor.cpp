#include "EntityEventProcessor.h"

#include "../FrameEntity/Entity.h"
#include "../FrameEntity/IEntityComponent.h"

#include <vector>
#include <algorithm>

namespace Frame {

	void CEntityEventProcessor::Process() {
		for(auto pComponent : m_set) {
			pComponent->ProcessEvent(m_event);
		}
	}
	
	void CEntityEventProcessor::Add(IEntityComponent * pComponent) {
		m_set.insert(pComponent);
	}

	void CEntityEventProcessor::Remove(IEntityComponent * pComponent) {
		auto it = m_set.find(pComponent);
		if(it != m_set.end()) {
			m_set.erase(it);
		}
	}

	void CEntityEventProcessorZSort::Process() {
		std::vector<IEntityComponent *> sortedVector { m_set.begin(), m_set.end() };
		std::sort(sortedVector.begin(), sortedVector.end(),
			[](IEntityComponent * a, IEntityComponent * b) {
				return a->GetEntity()->GetZDepth() > b->GetEntity()->GetZDepth();
			}
		);
		for(IEntityComponent * pComponent : sortedVector) {
			pComponent->ProcessEvent(m_event);
		}
	}

	void CEntityEventProcessorZSort::Add(IEntityComponent * pComponent) {
		m_set.insert(pComponent);
	}

	void CEntityEventProcessorZSort::Remove(IEntityComponent * pComponent) {
		auto it = m_set.find(pComponent);
		if(it != m_set.end()) {
			m_set.erase(it);
		}
	}

}