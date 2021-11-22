// サウンドノベル風文字列描画、テキストバッファ使用バージョン
// 参考にしたURL: https://dxlib.xsrv.jp/dxprogram.html#N19
// DXライブラリはそもそも60FPSであるらしい https://dixq.net/g/03_14.html
// その他参考: https://dixq.net/forum/viewtopic.php?t=15856
#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include <math.h>
#include <memory>
#include "Fps.h"
#include "TextLayer.h"

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	DxLib::SetWindowTextA("NovelSample");
	if (DxLib::ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK
		|| DxLib::SetWindowSizeExtendRate(1.0) == -1
		|| DxLib_Init() == -1
		|| DxLib::SetDrawScreen(DX_SCREEN_BACK) == -1
		|| DxLib::SetMouseDispFlag(TRUE) == -1) {
		return -1;
	}
#ifdef _DEBUG
	AllocConsole();
	FILE *fst1 = freopen("CONOUT$", "w", stdout);
	if (fst1 == NULL) {
		perror(NULL);
		return 0;
	}
	FILE *fst2 = freopen("CONIN$", "r", stdin);
	if (fst2 == NULL) {
		perror(NULL);
		return 0;
	}
#endif
	std::unique_ptr<NovelSample::TextLayer> textLayer = std::make_unique<NovelSample::TextLayer>();
	std::unique_ptr<NovelSample::Fps> fps = std::make_unique<NovelSample::Fps>();
	while (DxLib::ProcessMessage() == 0
		&& DxLib::CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		DxLib::ClearDrawScreen();  // 画面のクリア
		textLayer->update();
		textLayer->draw();

		fps->update();
		fps->draw();
		fps->wait();

		DxLib::ScreenFlip();
	}
	DxLib::DxLib_End();
#ifdef _DEBUG
	fclose(fst1);
	fclose(fst2);
	FreeConsole();
#endif
	return 0;
}
