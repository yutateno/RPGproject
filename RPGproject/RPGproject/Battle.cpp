#include "Manager.h"

Battle::Battle() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

}
Battle::~Battle() {

}

void Battle::UpDate() {
	switch (this->step) {
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
void Battle::UpDate_Start() {
	this->startCount++;

	if (this->startCount < 50) return;	// 50フレームで開始画面終了
	this->step = eStep::Main;
}
void Battle::UpDate_Main() {

	// Zキーで戦闘終了　一つ前の画面へ
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->step = eStep::End;
	}
	// Xキーで死亡画面に
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_GameOver;
		this->step = eStep::End;
	}

}
void Battle::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50フレームで終了画面終了
	this->endFlag = true;
}
void Battle::Draw() {
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
void Battle::Draw_Start() {
	DrawStringToHandle(0, 0, "戦闘画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "開始画面%d", this->startCount);
}
void Battle::Draw_Main() {
	DrawStringToHandle(0, 0, "戦闘画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "メイン処理画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Zキーで戦闘終了　一つ前の画面へ", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "Xキーでゲームオーバー画面へ", WHITE, Font::Get(eFont::SELECT));
}
void Battle::Draw_End() {
	DrawStringToHandle(0, 0, "戦闘画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面%d", this->endCount);
}


// どの画面から戦闘画面に移行したか（戦闘終了時にその画面に戻る)
void Battle::SetReturnScene(eScene scene) {
	this->nextScene = scene;
}