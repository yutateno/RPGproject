#include "Manager.h"
#include "Dungeon.h"

Dungeon::Dungeon() {
	endFlag = false;
	nextScene = eScene::S_End;
	step = eStep::Start;
	startCount = 0;
	endCount = 0;

	Gr_Back = LoadGraph("Dungeon\\Dungeon_Back.png");
	Gr_Wall = LoadGraph("Dungeon\\wall.png");
	Gr_Player = LoadGraph("Dungeon\\player.png");
}

Dungeon::~Dungeon() {

}

void Dungeon::UpDate() {
	switch (step) {
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
void Dungeon::UpDate_Start() {
	startCount++;

	if (startCount < 50) return;	// 50フレームで開始画面終了
	step = eStep::Main;
}

void Dungeon::UpDate_Main() {

	// Zキーで戦闘画面に
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	// Xキーでフィールド画面に
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}
	// Cキーでゲームクリア画面に
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_GameClear;
		this->step = eStep::End;
	}
}
void Dungeon::UpDate_End() {
	endCount++;

	if (endCount < 50) return;	// 50フレームで終了画面終了
	endFlag = true;
}
void Dungeon::Draw() {
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

void Dungeon::Draw_Start() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, startCount * 1);
	DrawRotaGraph(320, 240, 1.0, startCount * 1, Gr_Back, FALSE);	//回転角度 1  遊んでる"だけ"
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawStringToHandle(0, 0, "ダンジョン画面", WHITE, Font::Get(eFont::SELECT));
	//DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "開始画面%d", this->startCount);
}

void Dungeon::Draw_Main() {
	DrawStringToHandle(0, 0, "ダンジョン画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "メイン処理画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Zキーで戦闘画面へ", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "Xキーでフィールド画面へ", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 400, "Cキーでゲームクリア画面へ", WHITE, Font::Get(eFont::SELECT));
}

void Dungeon::Draw_End() {
	DrawStringToHandle(0, 0, "ダンジョン画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面%d", this->endCount);
}