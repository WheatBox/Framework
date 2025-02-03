#include <FrameEntity/Entity.h>

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>

namespace Frame {

	void CEntity::RemoveAllComponents() {
		for(auto & i : m_components) {
			RemoveComponent_And_RemoveFromProcessors(i.second);
			delete i.second;
		}
		m_components.clear();
	}

	void CEntity::InitializeComponent_And_AddIntoProcessors(IEntityComponent * pComponent) {
		pComponent->Construct(this);
		pComponent->Initialize();
		gEntitySystem->ComponentAddIntoProcessors(pComponent);
	}

	void CEntity::RemoveComponent_And_RemoveFromProcessors(IEntityComponent * pComponent) {
		pComponent->OnShutDown();
		gEntitySystem->ComponentRemoveFromProcessors(pComponent);
	}

}
