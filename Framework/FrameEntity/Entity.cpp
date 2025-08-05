#include "Entity.h"

#include "../FrameCore/Globals.h"
#include "../FrameEntity/EntitySystem.h"

namespace Frame {

	void CEntity::RemoveAllComponents() {
		for(auto & i : m_components) {
			RemoveComponent_And_RemoveFromProcessors(i.second);
		}
		m_components.clear();
	}

	void CEntity::InitializeComponent_And_AddIntoProcessors(IEntityComponent * pComponent) {
		pComponent->Construct(this);
		pComponent->Initialize();
		gEntitySystem->__ComponentAddIntoProcessors(pComponent);
	}

	void CEntity::RemoveComponent_And_RemoveFromProcessors(IEntityComponent * pComponent) {
		pComponent->OnRemove();
		gEntitySystem->__ComponentRemoveFromProcessors(pComponent);
	}

}
