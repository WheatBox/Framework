#include <FrameEntity/IEntity.h>

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>

namespace Frame {

	void IEntity::ComponentAddIntoProcessors(IEntityComponent * pComponent) {
		gEntitySystem->ComponentAddIntoProcessors(pComponent);
	}

	void IEntity::RemoveComponent(IEntityComponent * pComponent) {
		gEntitySystem->ComponentRemoveFromProcessors(pComponent);
		m_components.erase(pComponent);
		delete pComponent;
	}

	void IEntity::InitializeComponent(IEntityComponent * pComponent) {
		pComponent->__Initialize(this);
	}

}
