#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Title.h"
#include "player.h"
#include "Field.h"
#include "Enemy.h"
#include "Battle.h"
#include "Attack.h"
#include "GameOver.h"
#include "SafeArea.h"
#include "GameClear.h"
#include "Dungeon.h"
#include "Item.h"

class Player;
class Enemy;

class Manager :public SuperScene {
private:
	eScene NowScene;

	// 各シーンの実体
	Title* title;
	Player* player;
	Field* field;
	Enemy* enemy;
	Battle* battle;
	SafeArea* safeArea;
	Dungeon* dungeon;
	GameOver* gameOver;
	GameClear* gameClear;

	// 各シーンの移行処理
	void ChengeScene_Title();
	void ChengeScene_Field();
	void ChengeScene_Battle();
	void ChengeScene_SafeArea();
	void ChengeScene_Dungeon();
	void ChengeScene_GameOver();
	void ChengeScene_GameClear();

	int playerX;			// プレイヤーが動いたかどうかを判定する変数
	int playerY;			// プレイヤーが動いたかどうかを判定する変数
	int probability;		// エンカウントする確率 : 1/probability

	// 戦闘関連
	bool turn;				// こちらのターンか相手のターンか
	int count;				// ログを表示する時間
	int preHP;				// 直前のHP。ログ用
	bool lose;				// 先頭で敗北時に立つフラグ
public:
	Manager();
	~Manager();

	void UpDate();		// アップデート
	void UpDate_Start() {}	// 開始画面アップデート
	void UpDate_Main() {}		// メイン画面アップデート
	void UpDate_End() {}		// 終了画面アップデート
	void Draw();		// 描画
	void Draw_Start() {}		// 開始画面描画
	void Draw_Main() {}		// メイン画面描画
	void Draw_End() {}		// 終了画面描画

	// 可読性を考慮して長すぎる記述をUpDateから逃がすため作成
	void FieldProcess();
	void BattleProcess();
	void DungeonProcess();
	void SafeAreaProcess();
};