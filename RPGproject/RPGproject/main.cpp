#include "Manager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);
	//SetGraphMode(1920, 1080, 32);
	SetGraphMode(640, 480, 32);
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;        // エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	Font::SetFontData();
	PadData::SetPadNum();
	Manager *manager = new Manager();

	while (ProcessMessage() != -1 && !manager->GetEndFlag() &&
			KeyData::CheckEnd() && PadData::CheckEnd()) {//画面更新 & メッセージ処理 & 画面消去
		ClearDrawScreen();

		KeyData::UpDate();

		manager->UpDate();
		manager->Draw();
		ScreenFlip();
	}
	delete manager;

	InitGraph();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}