#include "Manager.h"

Battle::Battle() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

	// 画像
	Gr_Back = LoadGraph("img\\battle_background.png");		// 背景

	// コマンド状態
	command = NEUTRAL;

	// カーソル座標
	cursorX = 0;
	cursorY = 0;
}
Battle::~Battle() {
	DeleteGraph(Gr_Back);
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

	// カーソル移動
	if (KeyData::Get(KEY_INPUT_UP) == 1 && cursorY>0)
	{
		cursorY -= 100;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) == 1 && cursorY<200)
	{
		cursorY += 100;
	}

	// Zキーで決定
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		switch (command)
		{
		case NEUTRAL:	// 初期
			if (cursorY == 0)		// 攻撃選択時
			{
				command = ATTACK;
			}
			else if (cursorY == 100)// 魔法選択時
			{
				command = MAGIC;
			}
			else{					// 逃げる選択時
				command = RUN_AWAY;
			}
			break;

		case ATTACK:	// 攻撃メニュー
			if (cursorY == 0)		// 弱攻撃選択時
			{
				// ここに戦闘処理を書く
				command = DATTACK;
			}
			else if (cursorY == 100)// 強攻撃選択時
			{
				// ここに戦闘処理を書く
				command = DATTACK;
			}
			else {					// 戻る選択時
				cursorY = 0;		// カーソルをもとの位置に戻す
				command = NEUTRAL;
			}
			break;

		case DATTACK:	// Managerに処理させてる
			break;

		case MAGIC:		// 魔法メニュー
			if (cursorY == 0)		// 弱魔法選択時
			{
				// ここに戦闘処理を書く
				command = DMAGIC;
			}
			else if (cursorY == 100)// 強魔法選択時
			{
				// ここに戦闘処理を書く
				command = DMAGIC;
			}
			else {					// 戻る選択時
				cursorY = 0;		// カーソルをもとの位置に戻す
				command = NEUTRAL;
			}
			break;

		case DMAGIC:	// Managerに処理させてる
			break;

		case RUN_AWAY:	// 逃げる
			break;

		default:		// 在り得ない。エラー
			endFlag = true;
			break;
		}
	}

	// 逃げたら
	if (command == RUN_AWAY)
	{
		step = eStep::End;	// 戦闘終了
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
	// 背景
	DrawGraph(0, 0, Gr_Back, true);

	// コマンド状態に応じて表示を変化
	switch (command)
	{
	case NEUTRAL:	// 初期
		DrawStringToHandle(0, 0, "  攻撃", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 100, "  魔法", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 200, "  逃げる", WHITE, Font::Get(eFont::SELECT));
		break;

	case ATTACK:	// 攻撃メニュー
		DrawStringToHandle(0, 0, "  弱攻撃", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 100, "  強攻撃", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 200, "  戻る", WHITE, Font::Get(eFont::SELECT));
		break;

	case MAGIC:		// 魔法メニュー
		DrawStringToHandle(0, 0, "  弱魔法", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 100, "  強魔法", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 200, "  戻る", WHITE, Font::Get(eFont::SELECT));
		break;

	case RUN_AWAY:	// 逃げる
		//DrawStringToHandle(0, 0, "  あなたは逃げ出した・・・", WHITE, Font::Get(eFont::SELECT));
		break;

	default:		// 在り得ない。エラー
		endFlag = true;
		break;
	}
	
	// カーソル
	DrawStringToHandle(cursorX, cursorY, "▲", WHITE, Font::Get(eFont::SELECT));
}
void Battle::Draw_End() {
	DrawStringToHandle(0, 0, "戦闘画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面%d", this->endCount);
}

// どの画面から戦闘画面に移行したか（戦闘終了時にその画面に戻る)
void Battle::SetReturnScene(eScene scene) {
	this->nextScene = scene;
}

void Battle::SetCommand(Command command)
{
	this->command = command;
}
Command Battle::GetCommand()
{
	return command;
}
void Battle::SetStep(eStep step)
{
	this->step = step;
}