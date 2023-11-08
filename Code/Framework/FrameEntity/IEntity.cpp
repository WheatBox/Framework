#include <FrameEntity/IEntity.h>

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>

namespace Frame {

	void IEntity::ComponentAddIntoProcessors(IEntityComponent * pComponent) {
		gEntitySystem->ComponentAddIntoProcessors(pComponent);
	}

	void IEntity::InitializeComponent(IEntityComponent * pComponent) {
		pComponent->Construct(this);
	}

}
