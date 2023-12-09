#include "TestComponent.h"

#include <FrameEntity/Entity.h>

#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
//#include <FrameInput/InputManager.h>

#include <FrameAsset/Sprite.h>
#include <FrameAsset/Font.h>

REGISTER_ENTITY_COMPONENT(, CTestComponent);
REGISTER_ENTITY_COMPONENT(, CTestComponent2);
REGISTER_ENTITY_COMPONENT(, CTestComponent3);

Frame::EntityEvent::Flags CTestComponent::GetEventFlags() const {
	return Frame::EntityEvent::EFlag::Update
		 | Frame::EntityEvent::EFlag::Render
		;
}

void CTestComponent::ProcessEvent(const Frame::EntityEvent::SEvent & event) {
	switch(event.flag) {
	case Frame::EntityEvent::Update:
	{
		m_pEntity->Rotate(1.f);
		
		Frame::Vec2 pos = m_pEntity->GetPosition();

		Frame::gRenderer->SetColor(0x81F377);
		/*Frame::gRenderer->pShapeRenderer->DrawRectangle(
			pos.x - m_size.x / 2,
			pos.y - m_size.y / 2,
			pos.x + m_size.x / 2,
			pos.y + m_size.y / 2,
			true
		);*/
	}
	break;
	case Frame::EntityEvent::Render:
	{
		Frame::Vec2 pos = m_pEntity->GetPosition();

		Frame::gRenderer->SetColor(0x8D6B94);
		/*Frame::gRenderer->pShapeRenderer->DrawRectangle(
			pos.x - m_size.x / 3,
			pos.y - m_size.y / 3,
			pos.x + m_size.x / 3,
			pos.y + m_size.y / 3,
			true
		);*/
	}
	break;
	}
}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
void CTestComponent2::ProcessEvent(const Frame::EntityEvent::SEvent & event) {
	static bool bInited = false;
	static float angle = 0.f;

	static Frame::CStaticSprite * pSprite = nullptr;
	static Frame::CFont * pFont = nullptr;
	static std::vector<Frame::CFont::STextAutoWrapLineFormat> lineFormats {};
	static UnicodeString text = Frame::UTF8Utils::ToUnicode(
		"《出师表》\n"
		"诸葛亮\n"
		"\n"
		"先帝创业未半而中道崩殂，今天下三分，益州疲弊，此诚危急存亡之秋也。\n"
		"然侍卫之臣不懈于内，忠志之士忘身于外者，盖追先帝之殊遇，欲报之于陛下也。\n"
		"诚宜开张圣听，以光先帝遗德，恢弘志士之气，不宜妄自菲薄，引喻失义，以塞忠谏之路也。\n"
		"宫中府中，俱为一体，陟罚臧否，不宜异同。\n"
		"若有作奸犯科及为忠善者，宜付有司论其刑赏，以昭陛下平明之理，不宜偏私，使内外异法也。\n"
		"侍中、侍郎郭攸之、费祎、董允等，此皆良实，志虑忠纯，是以先帝简拔以遗陛下。\n"
		"愚以为宫中之事，事无大小，悉以咨之，然后施行，必能裨补阙漏，有所广益。\n"
		"将军向宠，性行淑均，晓畅军事，试用于昔日，先帝称之曰能，是以众议举宠为督。\n"
		"愚以为营中之事，悉以咨之，必能使行阵和睦，优劣得所。\n"
		"亲贤臣，远小人，此先汉所以兴隆也；\n"
		"亲小人，远贤臣，此后汉所以倾颓也。\n"
		"先帝在时，每与臣论此事，未尝不叹息痛恨于桓、灵也。\n"
		"侍中、尚书、长史、参军，此悉贞良死节之臣，愿陛下亲之信之，则汉室之隆，可计日而待也。\n"
		"臣本布衣，躬耕于南阳，苟全性命于乱世，不求闻达于诸侯。\n"
		"先帝不以臣卑鄙，猥自枉屈，三顾臣于草庐之中，咨臣以当世之事，由是感激，遂许先帝以驱驰。\n"
		"后值倾覆，受任于败军之际，奉命于危难之间，尔来二十有一年矣。\n"
		"先帝知臣谨慎，故临崩寄臣以大事也。\n"
		"受命以来，夙夜忧叹，恐托付不效，以伤先帝之明，故五月渡泸，深入不毛。\n"
		"今南方已定，兵甲已足，当奖率三军，北定中原，庶竭驽钝，攘除奸凶，兴复汉室，还于旧都。\n"
		"此臣所以报先帝而忠陛下之职分也。\n"
		"至于斟酌损益，进尽忠言，则攸之、祎、允之任也。\n"
		"愿陛下托臣以讨贼兴复之效，不效，则治臣之罪，以告先帝之灵。\n"
		"若无兴德之言，则责攸之、祎、允等之慢，以彰其咎；\n"
		"陛下亦宜自谋，以咨诹善道，察纳雅言，深追先帝遗诏，臣不胜受恩感激。\n"
		"今当远离，临表涕零，不知所言。\n"
	);
	
	switch(event.flag) {
	case Frame::EntityEvent::Update:
	{
		float frameTime = event.params[0].f;

		m_strFrameTime = "Test\n测试\nFrame time: " + std::to_string(frameTime) + "\nFps: " + std::to_string(int(1 / frameTime));
		
		//angle += frameTime * 360; // => 360°/s
		angle += frameTime * 360 / 5.f;
	}
	break;
	case Frame::EntityEvent::Render:
	{
		if(!bInited) {
			bInited = true;
			pSprite = new Frame::CStaticSprite { "./Assets/spr_t.bmp" };
			pSprite->SetOffset({ static_cast<float>(pSprite->GetWidth()) / 2.f, static_cast<float>(pSprite->GetHeight()) / 2.f });

			//pFont = new Frame::CFont { "C:/Windows/Fonts/STZHONGS.TTF", 32.f };
			//pFont = new Frame::CFont { "C:/Windows/Fonts/simkai.ttf", 32.f };
			//pFont = new Frame::CFont { "C:/Windows/Fonts/SIMLI.TTF", 32.f };
			//pFont = new Frame::CFont { "C:/Windows/Fonts/STXINGKA.TTF", 32.f };
			pFont = new Frame::CFont { "C:/Windows/Fonts/msyh.ttc", 32.f };
			//pFont = new Frame::CFont { "C:/Users/15599/AppData/Local/Microsoft/Windows/Fonts/onryou.ttf", 32.f };
			//pFont = new Frame::CFont { "C:/Users/15599/AppData/Local/Microsoft/Windows/Fonts/YaoSuiXinShouXieTi-2.ttf", 32.f };
			pFont->SetFontSize(16.f);
			lineFormats = pFont->TextAutoWrapLineFormats(text, 0.f);

			Frame::gRenderer->pTextRenderer->SetFont(pFont);
		}

#if 1
		//Frame::gRenderer->pSpriteShader->Use();
		//Frame::gRenderer->pSpriteShader->SetUniformInt("u_BaseTexture", 0);

		Frame::gRenderer->DrawSprite(pSprite, { 340.f , 400.f }, { 0.7f }, angle);
		Frame::gRenderer->DrawSpriteBlended(pSprite, { 400.f , 300.f },
			0xFF0000, 1.f, 0x00FF00, 1.f,
			0x0000FF, 0.f, 0xFFFF00, 0.f,
			1.2f, -angle
		);

		//Frame::gRenderer->pTextRenderer->SetColorAlpha(0xFFFFFF, .4f);
		//Frame::gRenderer->pTextRenderer->DrawText("Hello, world! 你好，世界！", { 20, 20 });
		//Frame::gRenderer->pTextRenderer->DrawText("The quick brown fox jumps over the lazy dog.", { 20, 60 });
		//Frame::gRenderer->pTextRenderer->DrawText("月落乌啼霜满天，\n江枫渔火对愁眠。", { 20, 100 });
		//Frame::gRenderer->pTextRenderer->GetFont()->SetFontSize(32.5f);
		//Frame::gRenderer->pTextRenderer->SetColorAlpha(0xFFFFFF, .7f);
		//Frame::gRenderer->pTextRenderer->DrawText("月落乌啼霜满天，\n江枫渔火对愁眠。", { 20, 100 });
		//Frame::gRenderer->pTextRenderer->GetFont()->SetFontSize(33.f);
		Frame::gRenderer->pTextRenderer->SetColorAlpha(0xFFFFFF, .5f);
		//Frame::gRenderer->pTextRenderer->DrawText("月落乌啼霜满天，\n江枫渔火对愁眠。", { 20, 100 });
		//constexpr UnicodeChar uni = Frame::UTF8Utils::ToUnicodeCharacter("😀");

		Frame::gRenderer->pTextRenderer->SetColorAlpha(0xFFFFFF, 1.f);

		Frame::gRenderer->pTextRenderer->DrawTextAutoWrapBlended(
			"先帝创 业未半  而中道崩\n殂，今天\n\n下三分，益州疲弊，此诚危急存亡之秋也。然侍卫之臣不懈于内，忠志之士忘身于外者，盖追先帝之殊遇，欲报之于陛下也。诚宜开张圣听，以光先帝遗德，恢弘志士之气，不宜妄自菲薄，引喻失义，以塞忠谏之路也。\n"
			"宫中府中，俱为一体，陟罚臧否，不宜异同。若有作奸犯科及为忠善者，宜付有司论其刑赏，以昭陛下平明之理，不宜偏私，使内外异法也。\n"
			"侍中、侍郎郭攸之、费祎、董允等，此皆良实，志虑忠纯，是以先帝简拔以遗陛下。愚以为宫中之事，事无大小，悉以咨之，然后施行，必能裨补阙漏，有所广益。\n"
			"将军向宠，性行淑均，晓畅军事，试用于昔日，先帝称之曰能，是以众议举宠为督。愚以为营中之事，悉以咨之，必能使行阵和睦，优劣得所。\n"
			"亲贤臣，远小人，此先汉所以兴隆也；亲小人，远贤臣，此后汉所以倾颓也。先帝在时，每与臣论此事，未尝不叹息痛恨于桓、灵也。侍中、尚书、长史、参军，此悉贞良死节之臣，愿陛下亲之信之，则汉室之隆，可计日而待也。\n"
			"臣本布衣，躬耕于南阳，苟全性命于乱世，不求闻达于诸侯。先帝不以臣卑鄙，猥自枉屈，三顾臣于草庐之中，咨臣以当世之事，由是感激，遂许先帝以驱驰。后值倾覆，受任于败军之际，奉命于危难之间，尔来二十有一年矣。\n"
			"先帝知臣谨慎，故临崩寄臣以大事也。受命以来，夙夜忧叹，恐托付不效，以伤先帝之明，故五月渡泸，深入不毛。今南方已定，兵甲已足，当奖率三军，北定中原，庶竭驽钝，攘除奸凶，兴复汉室，还于旧都。此臣所以报先帝而忠陛下之职分也。至于斟酌损益，进尽忠言，则攸之、祎、允之任也。\n"
			"愿陛下托臣以讨贼兴复之效，不效，则治臣之罪，以告先帝之灵。若无兴德之言，则责攸之、祎、允等之慢，以彰其咎；陛下亦宜自谋，以咨诹善道，察纳雅言，深追先帝遗诏，臣不胜受恩感激。\n"
			"今当远离，临表涕零，不知所言。\n"
			"The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog."
			"The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog."
			"The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog."
			,
			{ 0.f }, 500.f, 0xFFFF00, 0.5f
		);
		
		Frame::gRenderer->pTextRenderer->DrawTextAutoWrapLineFormatsAlign(text, { 1200.f, 800.f }, lineFormats, Frame::ETextHAlign::Center, Frame::ETextVAlign::Bottom);

		Frame::Vec2 vOff { 700, 500 };
		Frame::gRenderer->pShapeRenderer->DrawPixelBlended(
			vOff, 0xFFFF00, 1.f, 4.f
		);
		Frame::gRenderer->pTextRenderer->DrawTextAutoWrapAlignColorBlended(
			"先帝\n创业未 半  \n 而中道崩殂。"
			"先帝创业未半而中道崩殂。"
			"The qui\nck\nbrown \nfox\n jumps over the lazy dog."
			"The quick brown fox jumps over the lazy dog."
			,
			vOff, 120.f, Frame::ETextHAlign::Right, Frame::ETextVAlign::Bottom, 0xFF00FF
		);
		//std::cout << pFont->TextWidth("先帝\n创业未 半  \n 而中道崩殂。", 80.f) << std::endl;
		//std::cout << pFont->TextHeight("先帝\n创业未 半  \n 而中道崩殂。", 80.f) << std::endl;
		auto [w, h] = pFont->TextSize("先帝\n创业未 半  \n 而中道崩殂。", 80.f);
		std::cout << w << "x" << h << std::endl;
		//pFont->TextAutoWrapBase("先帝\n创业未 半  \n 而中道崩殂。", 1.f, [](size_t h, size_t t, const Frame::Vec2 &, float n) { std::cout << "1." << h << "~" << t << " : " << n << std::endl; });
		//pFont->TextAutoWrapBase("先帝\n创业未 半  \n 而中道崩殂。", 80.f, [](size_t h, size_t t, const Frame::Vec2 &, float n) { std::cout << "2." << h << "~" << t << " : " << n << std::endl; });
		//pFont->TextAutoWrapBase("The quick brown fox jumps over the lazy dog.", 80.f,
		//	[](size_t h, size_t t, const Frame::Vec2 &, float n) {
		//		std::cout << "2." << std::string("The quick brown fox jumps over the lazy dog.").substr(h, t - h + 1) << " : " << h << "~" << t << " : " << n << std::endl;
		//	}
		//);
		std::cout << "----" << std::endl;

		Frame::gRenderer->pShapeRenderer->DrawPixelColorBlended({ 100.f, 300.f }, 0x00FF00, 32.f);

		Frame::gRenderer->pShapeRenderer->DrawLineBlended({ 200.f, 200.f }, { 700.f, 500.f }, 0x00FF00, 1.f, 0x0000FF, 0.f, 16.f);
		Frame::gRenderer->pShapeRenderer->DrawLineAlphaBlended({ 200.f, 500.f }, { 700.f, 500.f }, 1.f, 0.f, 16.f);
		
		Frame::gRenderer->pShapeRenderer->DrawQuadrilateralBlended(
			{ 100.f, 300.f }, { 170.f, 280.f },
			{ 120.f, 400.f }, { 210.f, 360.f },
			0xFF0000, 1.f, 0x00FF00, .5f,
			0x0000FF, .5f, 0xFFFF00, 0.f,
			0.f
		);
		
		Frame::gRenderer->pShapeRenderer->DrawTriangle({ 100, 200 }, { 400, 300 }, { 200, 250 });
		Frame::gRenderer->pShapeRenderer->DrawTriangle({ 100, 400 }, { 200, 450 }, { 400, 500 });
#else 
		for(int i = 0; i < 100; i++) Frame::gRenderer->DrawSpriteBlended(pSprite, { 400 , 300 }, 0xFFFFFF, 0.5f, { 1.f }, angle);
#endif
		/*
		if(!bInited) {
			bInited = true;
			Frame::CFont * pFont = Frame::gAssetsManager->OpenFont("C:/Windows/Fonts/STZHONGS.TTF", 32);
			Frame::gRenderer->pTextRenderer->SetFont(pFont);
		}

		Frame::gRenderer->SetColor(0xEEEEEE);
		Frame::gRenderer->SetAlpha(128);
		Frame::gRenderer->pShapeRenderer->DrawRectangle(120, 40, 400, 200, true);
		
		Frame::gRenderer->pTextRenderer->SetAutoWrapLength(0);
		Frame::gRenderer->pTextRenderer->GetFont()->SetAlign(Frame::CFont::EHAlign::Left, Frame::CFont::EVAlign::Top);
		Frame::gRenderer->pTextRenderer->DrawText(400, 400, "Hello, world!\n你好，世界，我在这里！");

		Frame::gRenderer->SetAlpha(255);
		Frame::gRenderer->pTextRenderer->GetFont()->SetAlign(Frame::CFont::EHAlign::Right, Frame::CFont::EVAlign::Bottom);
		Frame::gRenderer->pTextRenderer->DrawText(400, 400, "Hello, world!\n你好，世界，我在这里！");

		Frame::gRenderer->pTextRenderer->SetAutoWrapLength(160);
		Frame::gRenderer->pTextRenderer->GetFont()->SetHAlign(Frame::CFont::EHAlign::Center);
		Frame::gRenderer->pTextRenderer->DrawText(400, 300, "Hello, world!\n你好，世界，我在这里！", 0xFFFFFF, 255);

		Frame::gRenderer->pTextRenderer->GetFont()->SetHAlign(Frame::CFont::EHAlign::Left);
		Frame::CStaticSprite * pSprite = Frame::gRenderer->pTextRenderer->DrawTextAsSprite(m_strFrameTime.c_str(), 0xFFFFFF, 255);
		pSprite->SetOffset({ pSprite->GetWidth() / 2.f, static_cast<float>(pSprite->GetHeight()) });
		// pSprite->SetAlphaBlend(128);
		// pSprite->SetColorBlend(0xFF00FF);
		Frame::gRenderer->DrawSpriteBlended({ 400, 300 }, pSprite, { 0.5f }, angle, 0xFF00FF, 128);
		Frame::gAssetsManager->DestroyStaticSprite(pSprite);
		
		if( Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_A) | 
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_S) | 
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_D) | 
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_LShift)
			)
		printf("%d %d %d %d\n",
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_A),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_S),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_D),
			Frame::gInputManager->pKeyboard->GetInputState(Frame::eIKI_LShift)
		);*/
	}
	break;
	}
}