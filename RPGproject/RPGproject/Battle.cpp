#include "Manager.h"

Battle::Battle() {
	// 動作関係
	this->endFlag = false;				// このシーンの終了するフラグ
	this->nextScene = eScene::S_End;	// 次のシーンの設定する

	// 演出関係
	this->step = eStep::Start;			// 演出関係
	this->startCount = 80;				// シーン開始時の演出時間
	this->endCount = 50;					// シーン終了時の演出時間
	count = 0;							// (フレーム)時間のカウント

	// 画像
	Gr_Back = LoadGraph("img\\battle_background.png");		// 背景

	// 戦闘システム関係
	command = NEUTRAL;				// 現在のコマンド
	preCommand = command;			// 直前のコマンドを保存する
	damageFlag = false;				// ダメージを与えたかどうか
	damageWidth = 0;				//ダメージの振れ幅

	// コマンドが乗ってる板
	commandX = 8;
	commandY = 320;

	// カーソル座標
	cursorX = 0;		// 相対座標
	cursorY = 0;		// 相対座標
}
Battle::~Battle() {
	// 画像削除
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
	// カウントアップ
	count++;

	// startCountだけ演出する
	if (count < startCount) return;
	// カウントリセットして次のステップへ
	count = 0;
	this->step = eStep::Main;
}
void Battle::UpDate_Main() {
	// 直前のコマンドを保存
	preCommand = command;

	// カーソル移動
	if (KeyData::Get(KEY_INPUT_UP) == 1 && cursorY>0)
	{
		cursorY--;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) == 1 && cursorY<2)
	{
		cursorY++;
	}

	// Zキーで決定
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// コマンドの状態から処理を選択
		switch (command)
		{
		case NEUTRAL:	// 初期
			if (cursorY == 0)		// 攻撃選択時
			{
				// ここに攻撃力などを代入する式を追加する
				damageWidth = 0;		// 振れ幅
				damageFlag = true;		// Managerに、enemyにダメージを与えるよう指示する
				command = ATTACK;		// コマンド状態を変更
			}
			else if (cursorY == 1)// 魔法選択時
			{
				// ここに攻撃力などを代入する式を追加する
				damageWidth = 3;		// 振れ幅
				damageFlag = true;		// Managerに、enemyにダメージを与えるよう指示する
				command = MAGIC;		// コマンド状態を変更
			}
			else{					// 逃げる選択時
				command = RUN_AWAY;
			}
			break;

		case ATTACK:	// 攻撃メニュー
			// ここで記入することはなし。NEUTRALにはManagerが戻してくれる
			break;

		case MAGIC:		// 魔法メニュー
			// ここで記入することはなし。NEUTRALにはManagerが戻してくれる
			break;

		case RUN_AWAY:	// 逃げる
			// ここで記入することはなし。NEUTRALにはManagerが戻してくれる
			break;

		default:		// 在り得ない。エラー
			break;
		}
	}

	// コマンドの変化からカーソルを補正
	if (preCommand != command)
	{
		cursorY = 0;		// カーソルをもとの位置に戻す
	}

	// 逃げたら
	if (command == RUN_AWAY)
	{
		step = eStep::End;	// 戦闘終了
	}
}
void Battle::UpDate_End() {
	// カウントアップ
	count++;

	// endCountだけ演出する
	if (count < endCount) return;
	// カウントをリセットしてこのシーンを終了する
	count = 0;
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
	// 徐々に画面の表示する処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count * 3);
	// 背景
	DrawGraph(0, 0, Gr_Back, FALSE);
	// ブレンドモードの後処理
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void Battle::Draw_Main() {
	// 背景
	DrawGraph(0, 0, Gr_Back, true);
}
void Battle::Draw_Command()
{
	// コマンド背景
	DrawBox(commandX, commandY, commandX + 150, commandY + 150, BLACK, true);
	DrawBox(commandX, commandY, commandX + 150, commandY + 150, WHITE, false);

	// コマンド状態に応じて表示を変化
	switch (command)
	{
	case NEUTRAL:	// 初期
		DrawFormatString(commandX + 32, commandY + 32, WHITE, "  攻撃");
		DrawFormatString(commandX + 32, commandY + 64, WHITE, "  魔法");
		DrawFormatString(commandX + 32, commandY + 96, WHITE, "  逃げる");
		break;

	case ATTACK:	// 攻撃メニュー
		break;

	case MAGIC:		// 魔法メニュー
		break;

	case RUN_AWAY:	// 逃げる
		break;

	default:		// 在り得ない。エラー
		break;
	}

	// カーソル
	DrawFormatString(commandX + 32 + cursorX, commandY + 32 + (cursorY * 32), WHITE, "▲");
}
void Battle::Draw_End() {
	// 徐々に画面を暗くする処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (count * 5));
	// 背景
	DrawGraph(0, 0, Gr_Back, FALSE);
	// ブレンドモードの後処理
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
void Battle::SetDamageFlag(bool damageFlag)
{
	this->damageFlag = damageFlag;
}
bool Battle::GetDamageFlag()
{
	return damageFlag;
}
int Battle::GetDamageWidth()
{
	return damageWidth;
}
void Battle::SetStep(eStep step)
{
	this->step = step;
}
eStep Battle::GetStep()
{
	return step;
}
void Battle::SetNextScene(eScene nextScene)
{
	this->nextScene = nextScene;
}
int Battle::GetCount()
{
	return count;
}