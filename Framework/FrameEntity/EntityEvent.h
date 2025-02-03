#pragma once

#include <FrameUtility/BitOperation.h>

namespace Frame {

	namespace EntityEvent {

		typedef uint32 Flags;

		enum EFlagIndex : uint8 {
			eEFI_BeforeUpdate = 0,
			eEFI_Update,
			eEFI_AfterUpdate,
			eEFI_Render,
			eEFI_EnteredView,
			eEFI_LeftView,
			eEFI_WindowResized,
			eEFI__END
		};

		enum EFlag : Flags {
		
			Nothing = 0,
		
			// 更新（每次游戏循环都会调用）
			// params[0].f = 这一帧的执行耗时
			// Update (Called in everytime the game loop)
			// params[0].f = The execution time of this frame
			Update = FlagBit(EFlagIndex::eEFI_Update),
			BeforeUpdate = FlagBit(EFlagIndex::eEFI_BeforeUpdate),
			AfterUpdate = FlagBit(EFlagIndex::eEFI_AfterUpdate),

			// 渲染
			// 该事件下每个实体对象会按照 m_zDepth 进行排序后再执行
			// 关于 m_zDepth，详情请见 CEntity，位于 <FrameEntity/CEntity.h>
			// Render
			// Under this event, each entity object will be sorted by m_zDepth before execution
			// About m_zDepth, please refer to CEntity for details, located at <FrameEntity/CEntity.h>
			Render = FlagBit(EFlagIndex::eEFI_Render),

			// ---------------- TODO ---------------- //
		
			// 进入视图
			// Entered the view
			EnteredView = FlagBit(EFlagIndex::eEFI_EnteredView),
		
			// 离开视图
			// Left the view
			LeftView = FlagBit(EFlagIndex::eEFI_LeftView),

			// 窗口大小改变
			// params[0].n = 新的窗口宽度
			// params[1].n = 新的窗口高度
			// Window resized
			// params[0].n = New window width
			// params[1].n = New window height
			WindowResized = FlagBit(EFlagIndex::eEFI_WindowResized),
			
		};

		struct SEvent {
			union UParam {
				int n;
				float f;

				UParam() { n = 0; }
				UParam(int _n) { n = _n; }
				UParam(float _f) { f = _f; }
			};

			EFlag flag = EFlag::Nothing;
			UParam params[2];
		};

	};
	
}