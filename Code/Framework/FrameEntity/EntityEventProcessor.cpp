#include <FrameEntity/EntityEventProcessor.h>

#include <FrameEntity/IEntity.h>

#include <vector>
#include <algorithm>

namespace Frame {

	void CEntityEventProcessor::Process() {
		for(auto pEntity : m_set) {
			pEntity->ProcessEvent(m_event);
		}
	}
	
	void CEntityEventProcessor::Join(IEntity * pEntity) {
		m_set.insert(pEntity);
	}

	void CEntityEventProcessor::Remove(IEntity * pEntity) {
		auto it = m_set.find(pEntity);
		if(it != m_set.end()) {
			m_set.erase(it);
		}
	}

	void CEntityEventProcessorImmediately::Join(IEntity * pEntity) {
		pEntity->ProcessEvent(m_event);
	}

	void CEntityEventProcessorZSort::Process() {
		std::vector<IEntity *> sortedVector { m_set.begin(), m_set.end() };
		std::sort(sortedVector.begin(), sortedVector.end(),
			[](IEntity * a, IEntity * b) {
				return a->m_zDepth - b->m_zDepth;
			}
		);
		for(IEntity * pEntity : sortedVector) {
			pEntity->ProcessEvent(m_event);
		}
	}

	void CEntityEventProcessorZSort::Join(IEntity * pEntity) {
		m_set.insert(pEntity);
	}

	void CEntityEventProcessorZSort::Remove(IEntity * pEntity) {
		auto it = m_set.find(pEntity);
		if(it != m_set.end()) {
			m_set.erase(it);
		}
	}

}