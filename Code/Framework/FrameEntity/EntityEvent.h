#pragma once

#include <FrameCore/BaseTypes.h>

namespace Frame {

	namespace EntityEvent {

		typedef __int32 Flags;
		
		// 1 << pos
		constexpr Flags FlagBit(Uint8 pos) {
			return 1 << pos;
		}

		enum EFlagIndex : Uint8 {
			eEFI_Initialize = 0,
			eEFI_Update,
			eEFI_Render,
			eEFI_Remove,
			eEFI_EnteredView,
			eEFI_LeftView,
			eEFI_WindowResized,
			eEFI__END
		};

		enum EFlag : Flags {
		
			Nothing = 0,

			// 在日记上初始化（日记初始化时，或编辑模式放置实体后调用）
			// Initialize on the diary (called during diary initialization or place the entity in edit mode)
			Initialize = FlagBit(EFlagIndex::eEFI_Initialize),
		
			// 更新（每次游戏循环都会调用）
			// params[0].f = 这一帧的执行耗时
			// Update (Called in everytime the game loop)
			// params[0].f = The execution time of this frame
			Update = FlagBit(EFlagIndex::eEFI_Update),

			// 渲染
			// Render
			// 样例 | Example:
			// CRenderer * pRenderer = reinterpret_cast<Frame::CRenderer *>(params[0].n);
			Render = FlagBit(EFlagIndex::eEFI_Render),

			// 从日记上移除
			// Remove from the diary
			Remove = FlagBit(EFlagIndex::eEFI_Remove),
		
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