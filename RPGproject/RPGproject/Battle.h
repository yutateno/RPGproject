#pragma once
#include "Manager.h"

// コマンド状態
enum Command { NEUTRAL, ATTACK, MAGIC, RUN_AWAY };

class Battle : public SuperScene {
private:
	// 画像関係
	int Gr_Back;			// 背景

	// 戦闘システム関係
	Command command;		// コマンド状態	
	Command preCommand;		// 直前のコマンド
	bool damageFlag;		// ダメージを与える処理をおこなうかどうかのフラグ
	int damageWidth;		// ダメージのブレ幅

	// カーソル関係
	int cursorX, cursorY;			// カーソルの相対座標

	// ログ関係
	bool textFlag;					// テキストを表示するかどうかのフラグ

	// 演出関係
	int count;				// (フレーム)時間のカウント

public:
	Battle();
	~Battle();

	void UpDate();		// アップデート
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_End();	// 終了画面アップデート

	void Draw();			// 描画
	void Draw(bool flag);	// 基本的にこっちが呼ばれる
	void Draw_Start();		// 開始画面描画
	void Draw_Main();		// メイン画面描画
	void Draw_End();		// 終了画面描画
	
	// どの画面から戦闘画面に移行したか（戦闘終了時にその画面に戻る)
	void SetReturnScene(eScene scene);

	// セッターゲッター
	void SetCommand(Command command);
	Command GetCommand();
	void SetDamageFlag(bool damageFlag);
	bool GetDamageFlag();
	int GetDamageWidth();
	void SetStep(eStep step);
	eStep GetStep();
	void SetNextScene(eScene nextScene);
};
