#include "Manager.h"

Title::Title() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

}
Title::~Title() {

}

void Title::UpDate() {
	switch (this->step){
	case eStep::Start:	// 開始画面
		this->UpDate_Start();
		break;
	case eStep::Main:	// メイン処理画面
		this->UpDate_Main();
		break;
	case eStep::End:	// 終了画面
		this->UpDate_End();
		break;
	default:
		this->endFlag = true;	// エラー終了
		break;
	}
}
void Title::UpDate_Start() {
	this->startCount++;
	
	if (this->startCount < 50) return;	// 50フレームで開始画面終了
	this->step = eStep::Main;
}
void Title::UpDate_Main() {

	// Zキーでフィールド画面に
	if (KeyData::Get(KEY_INPUT_Z) >= 1) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}
	// Xキーでゲーム終了
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_End;
		this->step = eStep::End;
	}

}
void Title::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50フレームで終了画面終了
	this->endFlag = true;
}
void Title::Draw() {
	switch (this->step) {
	case eStep::Start:	// 開始画面
		this->Draw_Start();
		break;
	case eStep::Main:	// メイン処理画面
		this->Draw_Main();
		break;
	case eStep::End:	// 終了画面
		this->Draw_End();
		break;
	default:
		this->endFlag = true;	// エラー終了
		break;
	}
}
void Title::Draw_Start() {
	DrawStringToHandle(0, 0, "タイトル画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "開始画面%d", this->startCount);
}
void Title::Draw_Main() {
	DrawStringToHandle(0, 0, "タイトル画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "メイン処理画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Zキーでフィールド", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "Xキーでゲーム終了", WHITE, Font::Get(eFont::SELECT));
}
void Title::Draw_End() {
	DrawStringToHandle(0, 0, "タイトル画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面%d", this->endCount);

}