#include <FrameEntity/Entity.h>

#include <FrameCore/Globals.h>
#include <FrameEntity/EntitySystem.h>

namespace Frame {

	void CEntity::ComponentAddIntoProcessors(IEntityComponent * pComponent) {
		gEntitySystem->ComponentAddIntoProcessors(pComponent);
	}

	void CEntity::InitializeComponent(IEntityComponent * pComponent) {
		pComponent->Construct(this);
	}

}
