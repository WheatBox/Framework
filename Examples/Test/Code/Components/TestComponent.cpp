#include "TestComponent.h"

#include <FrameEntity/Entity.h>

#include <FrameCore/Log.h>
#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameInput/Input.h>
#include <FrameAudio/AudioPlayer.h>
#include <FrameCore/Camera.h>
#include <FrameMath/Matrix33.h>
#include <FrameMath/Matrix22.h>

REGISTER_ENTITY_COMPONENT(CTestComponent);
REGISTER_ENTITY_COMPONENT(CTestComponent2);
REGISTER_ENTITY_COMPONENT(CTestComponent3);

Frame::EntityEvent::Flags CTestComponent::GetEventFlags() const {
	return Frame::EntityEvent::EFlag::Update
		 | Frame::EntityEvent::EFlag::Render
		;
}

void CTestComponent::ProcessEvent(const Frame::EntityEvent::SEvent & event) {
	switch(event.flag) {
	case Frame::EntityEvent::Update:
	{
		m_pEntity->Rotate(Frame::DegToRad(1.f));
		
		//Frame::Vec2 pos = m_pEntity->GetPosition();

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
		//Frame::Vec2 pos = m_pEntity->GetPosition();

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
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

void CTestComponent2::Initialize() {
	Frame::gInput->pMouse->SetScrollCallback([](double x, double y) {
		printf("%lf %lf\n", x, y);
	});

	m_pSprite = new Frame::CStaticSprite { "./Assets/spr_t.bmp" };
	m_pSprite->SetOrigin({ static_cast<float>(m_pSprite->GetWidth()) / 2.f, static_cast<float>(m_pSprite->GetHeight()) / 2.f });

	m_pAnimSprite = new Frame::CAnimatedSprite { "Assets/StripTest.png", 4 };

#ifdef _WIN32
	//m_pFont = new Frame::CFont { "C:/Windows/Fonts/STZHONGS.TTF", 32.f };
	//m_pFont = new Frame::CFont { "C:/Windows/Fonts/simkai.ttf", 32.f };
	//m_pFont = new Frame::CFont { "C:/Windows/Fonts/SIMLI.TTF", 32.f };
	//m_pFont = new Frame::CFont { "C:/Windows/Fonts/STXINGKA.TTF", 32.f };
	m_pFont = new Frame::CFont { "C:/Windows/Fonts/msyh.ttc", 32.f };
	//m_pFont = new Frame::CFont { "C:/Users/15599/AppData/Local/Microsoft/Windows/Fonts/onryou.ttf", 32.f };
	//m_pFont = new Frame::CFont { "C:/Users/15599/AppData/Local/Microsoft/Windows/Fonts/YaoSuiXinShouXieTi-2.ttf", 32.f };
#else
	//m_pFont = new Frame::CFont { "/usr/share/fonts/truetype/hack/Hack-Regular.ttf", 32.f };
	m_pFont = new Frame::CFont { "/usr/share/fonts/opentype/noto/NotoSerifCJK-Regular.ttc", 32.f };
#endif
	m_pFont->SetFontSize(16.f);
	m_lineFormats = m_pFont->TextAutoWrapLineFormats(m_text, 0.f);

	Frame::gRenderer->pTextRenderer->SetFont(m_pFont);

#ifdef _WIN32
	m_pSound = new Frame::CSound { "C:/Users/wheat_box/Downloads/mp3test.mp3", true };
	//m_pSound = new Frame::CSound { "D:/RickAstley.mp3", true };
	//m_pSound = new Frame::CSound { "F:/GameMakerProjects/2022CGJ/Audios/stone_door_open.wav", true };
	//m_pSound = new Frame::CSound { "D:/Downloads/bounce.wav" };
	//m_pSound = new Frame::CSound { "F:/C_CPP/_download/openal-impl-vid4/res/soundeffects/sci-fidrone.ogg" };
#else
	m_pSound = new Frame::CSound { "/home/wheat_box/mp3test.mp3", true };
#endif

	//Frame::gAudioPlayer->SetFalloffModel(Frame::CAudioPlayer::EFalloffModel::None);
	Frame::gAudioPlayer->SetFalloffModel(Frame::CAudioPlayer::EFalloffModel::ExponentDistanceClamped);

	m_pTextureAtlas = new Frame::CTextureAtlas { "Assets/AtlasTest.png",
		{
			{ "image (6).png", { { 0.000000f, 1.000000f }, { 0.976563f, 0.951172f } } },
			{ "image (4).png", { { 0.000000f, 0.951172f }, { 0.585938f, 0.755859f } } },
			{ "image (10).png", { { 0.000000f, 0.755859f }, { 0.500000f, 0.255859f } } },
			{ "image (7).png", { { 0.000000f, 0.255859f }, { 0.500000f, 0.005859f } } },
			{ "image (1).png", { { 0.500000f, 0.755859f }, { 0.792969f, 0.505859f } } },
			{ "image (11).png", { { 0.500000f, 0.505859f }, { 0.750000f, 0.005859f } } },
			{ "image (2).png", { { 0.750000f, 0.505859f }, { 1.000000f, 0.255859f } } },
			{ "image (12).png", { { 0.750000f, 0.255859f }, { 1.000000f, 0.005859f } } },
			{ "image (3).png", { { 0.792969f, 0.951172f }, { 0.988281f, 0.638672f } } },
			{ "image (9).png", { { 0.585938f, 0.951172f }, { 0.679688f, 0.857422f } } },
			{ "image (8).png", { { 0.585938f, 0.857422f }, { 0.679688f, 0.826172f } } },
			{ "image (5).png", { { 0.585938f, 0.826172f }, { 0.664063f, 0.763672f } } },
			{ "full", { { 0.f, 1.f }, { 1.f, 0.f } } }
		}
	};
	m_pTextureAtlasTestSprite = new Frame::CStaticSprite { m_pTextureAtlas, "image (3).png" };

	printf("\n");

	{
		Frame::Matrix_tpl<int, 4, 3> mat1{ {
				5, 2, 4,
				3, 8, 2,
				6, 0, 4,
				0, 1, 6
			} };
		Frame::Matrix_tpl<int, 3, 2> mat2{ {
				2, 4,
				1, 3,
				3, 2
			} };
		Frame::Matrix_tpl mat = mat1 * mat2;
		mat.ForEachIn([](int * data, int i) {
			printf("%d ", data[i]);
			if (i % 2 && i != 0) {
				printf("\n");
			}
			});
	}
	
	printf("\n");

	{
		Frame::Matrix_tpl<int, 2, 3> mat1 = {{
				1, 0, 3,
				2, -1, 0
			}};
		Frame::Matrix_tpl<int, 3, 2> mat2 = {{
				1, -1,
				2, 3,
				4, 0
			}};
		Frame::Matrix_tpl mat = mat1 * mat2;
		mat.ForEachIn([](int * data, int i) {
			printf("%d ", data[i]);
			if(i % 2 == 1) {
				printf("\n");
			}
			});
	}

	printf("\n");

	{
		Frame::Matrix33 m { { 1, 2, 3, 4, 5 } };
		m = m + Frame::Matrix33 { { 10, 10, 10 } };
		m.ForEachIn([](float * data, int i) {
			printf("%.2f ", data[i]);
			if(i % 3 == 2) {
				printf("\n");
			}
			});
	}

	printf("\n");
}

void CTestComponent2::OnShutDown() {
	delete m_pSprite;
	delete m_pFont;
}

void CTestComponent2::ProcessEvent(const Frame::EntityEvent::SEvent & event) {

	switch(event.flag) {
	case Frame::EntityEvent::Update:
	{
		float frameTime = event.params[0].f;

		//printf("fps: %f\n", 1.f / frameTime);

		m_seconds += frameTime;

		m_strFrameTime = "Test\n测试\nFrame time: " + std::to_string(frameTime) + "\nFps: " + std::to_string(int(1 / frameTime));
		
		//Frame::Log::Log(Frame::Log::ELevel::Info, "Hello, world! 你好，世界！ %f %f", 1 / frameTime, m_seconds); // 当前游戏帧数 和 当前经过的游戏时间

		//m_angle += frameTime * 360; // => 360°/s
		m_angle += Frame::DegToRad(frameTime * 360 / 5.f);

		m_camAngle += frameTime * 60.f * float(-int(Frame::gInput->pKeyboard->GetHolding(Frame::eKI_1)) + int(Frame::gInput->pKeyboard->GetHolding(Frame::eKI_2)));
		Frame::gCamera->SetRotationDegree(m_camAngle);

		Frame::Vec2 camPos = Frame::gCamera->GetPos();
		camPos.y += frameTime * 100.f * float(-int(Frame::gInput->pKeyboard->GetHolding(Frame::eKI_W)) + int(Frame::gInput->pKeyboard->GetHolding(Frame::eKI_S)));
		camPos.x += frameTime * 100.f * float(-int(Frame::gInput->pKeyboard->GetHolding(Frame::eKI_A)) + int(Frame::gInput->pKeyboard->GetHolding(Frame::eKI_D)));
		Frame::gCamera->SetPos(camPos);

		if( Frame::gInput->pKeyboard->GetInputState(Frame::eKI_A) | 
			Frame::gInput->pKeyboard->GetInputState(Frame::eKI_S) | 
			Frame::gInput->pKeyboard->GetInputState(Frame::eKI_D) | 
			Frame::gInput->pKeyboard->GetInputState(Frame::eKI_LShift) |
			Frame::gInput->pMouse->GetInputState(Frame::eMBI_Left) |
			Frame::gInput->pMouse->GetInputState(Frame::eMBI_Middle) |
			Frame::gInput->pMouse->GetInputState(Frame::eMBI_Right)
		)
		printf("%d %d %d %d %d %d %d\n",
			Frame::gInput->pKeyboard->GetInputState(Frame::eKI_A),
			Frame::gInput->pKeyboard->GetInputState(Frame::eKI_S),
			Frame::gInput->pKeyboard->GetInputState(Frame::eKI_D),
			Frame::gInput->pKeyboard->GetInputState(Frame::eKI_LShift) ,
			Frame::gInput->pMouse->GetInputState(Frame::eMBI_Left) ,
			Frame::gInput->pMouse->GetInputState(Frame::eMBI_Middle) ,
			Frame::gInput->pMouse->GetInputState(Frame::eMBI_Right)
		);

		/*if(m_vMousePos != Frame::gInput->pMouse->GetPosition()) {
			m_vMousePos = Frame::gInput->pMouse->GetPosition();
			printf("%f %f\n", m_vMousePos.x, m_vMousePos.y);
		}*/

		if(Frame::gInput->pKeyboard->GetHolding(Frame::eKI_Q)) {
			Frame::gInput->pMouse->SetPosition({ 100, 100 });
		}

		if(Frame::gInput->pKeyboard->GetPressed(Frame::eKI_P)) {
			Frame::SAudioSourceParams audioSourceParams {};
			//audioSourceParams.bPosRelative = true;
			m_pAudioSource = Frame::gAudioPlayer->PlaySound(m_pSound, audioSourceParams);
			printf("Sound Play %p\n", m_pAudioSource.get());
		}
		if(m_pAudioSource != nullptr) {
			//Frame::gAudioPlayer->SetListenerPosition({ 1 * sin(m_angle), 0, 0 });
			m_pAudioSource->SetPosition({ 10 * std::cos(m_angle), 10 * std::sin(m_angle), 0 });
		}
	}
	break;
	case Frame::EntityEvent::Render:
	{
#if 1
		Frame::Vec2 vPos { 400.f, 300.f };
		//Frame::Vec2 vPos { 0.f, 0.f };
		//Frame::gCamera->SetPos(vPos + Frame::Vec2 { 10 * cos(m_angle), 10 * sin(Frame::m_angle) } * 10);
		//Frame::gCamera->SetPos(vPos);
		Frame::gCamera->SetZoom(.5f);
		Frame::gCamera->SetZoom(1.f);
		//Frame::gCamera->SetViewSize({ 200, 600 });

		//Frame::gRenderer->pShapeRenderer->DrawPoint(Frame::gCamera->WindowToScene(Frame::gInput->pMouse->GetPosition()), 12.f);
		Frame::gRenderer->pShapeRenderer->DrawPoint(Frame::gInput->pMouse->GetPositionInScene(), 12.f);

		Frame::gRenderer->pShapeRenderer->DrawPoint(vPos, 12.f);
		Frame::gRenderer->pShapeRenderer->DrawPoint(vPos + Frame::Vec2 { Frame::gAudioPlayer->GetListenerOrientation().first.x, Frame::gAudioPlayer->GetListenerOrientation().first.y } * 10, 4.f);
		Frame::gRenderer->pShapeRenderer->DrawPointColorBlended(vPos + Frame::Vec2 { 10 * std::cos(m_angle), 10 * std::sin(m_angle) } * 10, 0xFFFF00, 12.f);
#endif
#if 1
		//Frame::gRenderer->pSpriteShader->Use();
		//Frame::gRenderer->pSpriteShader->SetUniformInt("u_BaseTexture", 0);
		
		Frame::gRenderer->DrawSprite(m_pSprite->GetImage(), { 340.f , 400.f }, 0.7f, m_angle);
		Frame::gRenderer->DrawSpriteBlended(m_pSprite->GetImage(), { 400.f , 300.f },
			0xFF0000, 1.f, 0x00FF00, 1.f,
			0x0000FF, 0.f, 0xFFFF00, 0.f,
			{ 1.f, -1.f }, -m_angle
		);

		Frame::gRenderer->DrawSprite(m_pAnimSprite->GetFrame(static_cast<int>(m_seconds)), { 100, 100 });
#endif
#if 1

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
			{ 0.f }, 500.f, 0xFFFF00, 0.3f
		);
		
		Frame::gRenderer->pTextRenderer->DrawTextAutoWrapLineFormatsAlign(m_text, { 1200.f, 800.f }, m_lineFormats, Frame::ETextHAlign::Center, Frame::ETextVAlign::Bottom);

		Frame::Vec2 vOff { 700, 500 };
		Frame::gRenderer->pShapeRenderer->DrawPointBlended(
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
		//auto [w, h] = m_pFont->TextSize("先帝\n创业未 半  \n 而中道崩殂。", 80.f);
		//std::cout << w << "x" << h << std::endl;
		//pFont->TextAutoWrapBase("先帝\n创业未 半  \n 而中道崩殂。", 1.f, [](size_t h, size_t t, const Frame::Vec2 &, float n) { std::cout << "1." << h << "~" << t << " : " << n << std::endl; });
		//pFont->TextAutoWrapBase("先帝\n创业未 半  \n 而中道崩殂。", 80.f, [](size_t h, size_t t, const Frame::Vec2 &, float n) { std::cout << "2." << h << "~" << t << " : " << n << std::endl; });
		//pFont->TextAutoWrapBase("The quick brown fox jumps over the lazy dog.", 80.f,
		//	[](size_t h, size_t t, const Frame::Vec2 &, float n) {
		//		std::cout << "2." << std::string("The quick brown fox jumps over the lazy dog.").substr(h, t - h + 1) << " : " << h << "~" << t << " : " << n << std::endl;
		//	}
		//);

		Frame::gRenderer->pShapeRenderer->DrawPointColorBlended({ 100.f, 300.f }, 0x00FF00, 32.f);

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
#endif
#if 0
		for(int i = 0; i < 100; i++) Frame::gRenderer->DrawSpriteBlended(pSprite, { 400 , 300 }, 0xFFFFFF, 0.5f, { 1.f }, angle);
#endif
#if 0
		Frame::gRenderer->pShapeRenderer->SetColorAlpha(0xFFFFFF, .5f);
		Frame::gRenderer->pShapeRenderer->DrawRectangle({ 120, 40 }, { 400, 200 }, 1.f);

		Frame::gRenderer->pTextRenderer->DrawTextAutoWrapAlignBlended("Hello, world!\n你好，世界，我在这里！", { 400, 400 }, 160, Frame::ETextHAlign::Left, Frame::ETextVAlign::Top, 0xFFFFFF, .7f);
		Frame::gRenderer->pTextRenderer->DrawTextAutoWrapAlignBlended("Hello, world!\n你好，世界，我在这里！", { 400, 400 }, 160, Frame::ETextHAlign::Right, Frame::ETextVAlign::Bottom, 0xFFFFFF, 1.f);
		Frame::gRenderer->pTextRenderer->DrawTextAutoWrapAlignBlended("Hello, world!\n你好，世界，我在这里！", { 400, 300 }, 160, Frame::ETextHAlign::Center, Frame::ETextVAlign::Bottom, 0xFFFFFF, 1.f);
#endif
#if 1
		Frame::gRenderer->DrawSpriteBlended(m_pTextureAtlasTestSprite->GetImage(), 0.f, 0xFFFFFF, 1.f);
#endif
#if 1
		if(!m_pFramebuffer) {
			m_pFramebuffer = new Frame::CFramebuffer { 200 };
		}
		if(!m_pFramebuffer2) {
			m_pFramebuffer2 = new Frame::CFramebuffer { 100 };
		}

		m_pFramebuffer->Bind();
		Frame::gRenderer->pShapeRenderer->DrawRectangleBlended(50, 150, 0xCCCC00, 1.f);
		m_pFramebuffer2->Bind();
		Frame::gRenderer->DrawSprite(m_pSprite->GetImage(), Frame::Vec2Cast(m_pFramebuffer2->GetSize()) * .5f, 1.f, m_angle);
		m_pFramebuffer2->Unbind();
		Frame::gRenderer->DrawSprite(m_pFramebuffer2->GetImage(), Frame::Vec2 { 50.f }.GetRotated(m_angle) + 100.f, 1.f, -m_angle);
		Frame::gRenderer->pShapeRenderer->DrawRectangleBlended(50, 150, 0xCC0000, 1.f, 4.f);
		m_pFramebuffer->Unbind();
		Frame::gRenderer->DrawSprite(m_pFramebuffer->GetImage(), -100.f, 1.f, 0.f);
#endif

		if(Frame::gInput->pKeyboard->GetPressed(Frame::EKeyId::eKI_Space))
			Frame::Log::Log(Frame::Log::ELevel::Debug, "Test");

		//Frame::gRenderer->DrawSprite(m_pTextureAtlasTestSprite->GetImage(), { -200.f, 0.f });
		
		auto pSpriteImage = m_pTextureAtlasTestSprite->GetImage();
		Frame::gRenderer->DrawSpritesInstancedBlended(pSpriteImage, {
			{},
			{ Frame::Matrix33::CreateTranslation({ -100.f }) },
			{ Frame::Matrix33::CreateTranslation({ -200.f, -100.f }), { 1.f, 1.f, 1.f, 1.f }, 1.f, -.5f },
			{ Frame::Matrix33::CreateRotationZ(Frame::DegToRad(30.f)), { 1.f, 0.f, 0.f, 1.f } },
			{ Frame::Matrix33::CreateTranslation({ -50.f, 50.f }) * Frame::Matrix33::CreateRotationZ(Frame::DegToRad(30.f)) },
			{ Frame::Matrix33::CreateTranslation({ -50.f, 50.f }), { 0.f, 0.f, 1.f, 1.f } },
			{ Frame::Matrix33::CreateTranslation({ 80.f, 20.f }) * Frame::Matrix33::CreateScale({ 2.f, .5f }) * Frame::Matrix33::CreateTranslation({ -100.f }) },
			{ Frame::Matrix33::CreateScale({ 2.f, .5f }) * Frame::Matrix33::CreateTranslation({ 80.f, 20.f }) * Frame::Matrix33::CreateTranslation({ -100.f }) }
			}, 0xFFFFFF, .5f);

		{
			Frame::Vec2 vecpos { 100.f, 0.f };

			Frame::gRenderer->pShapeRenderer->DrawLine(0.f, vecpos);
			Frame::gRenderer->pTextRenderer->DrawText("1", vecpos);

			vecpos = Frame::Matrix33::CreateTranslation({ 20.f, -30.f }) * vecpos;
			
			Frame::gRenderer->pShapeRenderer->DrawLine(0.f, vecpos);
			Frame::gRenderer->pTextRenderer->DrawText("2", vecpos);
			
			vecpos = Frame::Matrix33::CreateScale({ -.5f, 2.f }) * vecpos;
			
			Frame::gRenderer->pShapeRenderer->DrawLine(0.f, vecpos);
			Frame::gRenderer->pTextRenderer->DrawText("3", vecpos);
			
			vecpos = Frame::Matrix33::CreateRotationZ(Frame::DegToRad(60.f)) * vecpos;
			
			Frame::gRenderer->pShapeRenderer->DrawLine(0.f, vecpos);
			Frame::gRenderer->pTextRenderer->DrawText("4", vecpos);
		}

		{
			Frame::Vec2 vecpos
				= Frame::Matrix33::CreateRotationZ(Frame::DegToRad(60.f))
				* Frame::Matrix33::CreateScale({ -.5f, 2.f })
				* Frame::Matrix33::CreateTranslation({ 20.f, -30.f })
				* Frame::Vec2 { 100.f, 0.f };

			Frame::gRenderer->pShapeRenderer->DrawLine(0.f, vecpos);
			Frame::gRenderer->pTextRenderer->DrawText("  5", vecpos);
		}

		{
			Frame::Vec2 vecpos { 100.f, 0.f };
			vecpos += Frame::Vec2 { 20.f, -30.f };
			vecpos *= Frame::Vec2 { -.5f, 2.f };
			vecpos = vecpos.GetRotatedDegree(60.f);

			Frame::gRenderer->pShapeRenderer->DrawLine(0.f, vecpos);
			Frame::gRenderer->pTextRenderer->DrawText("    6", vecpos);
		}

		{
			Frame::Vec2 vecpos
				= Frame::Matrix22::CreateRotation(Frame::DegToRad(60.f))
				* Frame::Matrix22::CreateScale({ -.5f, 2.f })
				* (Frame::Vec2 { 100.f, 0.f } + Frame::Vec2 { 20.f, -30.f });

			Frame::gRenderer->pShapeRenderer->DrawLine(0.f, vecpos);
			Frame::gRenderer->pTextRenderer->DrawText("      7", vecpos);
		}
	}
	break;
	}
}
