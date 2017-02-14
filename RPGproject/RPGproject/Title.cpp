#include "Manager.h"

Title::Title() {
	endFlag = false;
	nextScene = eScene::S_End;
	step = eStep::Start;
	startCount = 0;
	endCount = 0;
	Icon_x = 140;
	Icon_y = 300;
	Icon_area = 0;
	Gr_Back = LoadGraph("Title.png");
}
Title::~Title() {
	DeleteGraph(Gr_Back);
}

void Title::UpDate() {
	switch (step){
	case eStep::Start:	// 開始画面
		UpDate_Start();
		break;
	case eStep::Main:	// メイン処理画面
		UpDate_Main();
		break;
	case eStep::End:	// 終了画面
		UpDate_End();
		break;
	default:
		endFlag = true;	// エラー終了
		break;
	}
}
void Title::UpDate_Start() {
	startCount++;
	
	if (startCount < 50) return;	// 50フレームで開始画面終了
	step = eStep::Main;
}
void Title::UpDate_Main() {
	if (KeyData::Get(KEY_INPUT_UP) >= 1) {
		Icon_area = 0;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) >= 1) {
		Icon_area = 1;
	}
	if (KeyData::Get(KEY_INPUT_Z) >= 1) {
		if (Icon_area == 0) {
			nextScene = eScene::S_Field;
			step = eStep::End;
		}
		else {
			nextScene = eScene::S_End;
			step = eStep::End;
		}
	}
}
void Title::UpDate_End() {
	endCount++;

	if (endCount < 50) return;	// 50フレームで終了画面終了
	endFlag = true;
}
void Title::Draw() {
	switch (step) {
	case eStep::Start:	// 開始画面
		Draw_Start();
		break;
	case eStep::Main:	// メイン処理画面
		Draw_Main();
		break;
	case eStep::End:	// 終了画面
		Draw_End();
		break;
	default:
		endFlag = true;	// エラー終了
		break;
	}
}
void Title::Draw_Start() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, startCount * 5);
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void Title::Draw_Main() {
	DrawGraph(0, 0, Gr_Back, FALSE);

	DrawBox(Icon_x, Icon_y + (Icon_area * 70), Icon_x + 50, Icon_y + 50 + (Icon_area * 70), BLUE, TRUE);

	DrawString(0, 450, "上下で移動、Zで決定",WHITE);
}
void Title::Draw_End() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (endCount * 5));
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}