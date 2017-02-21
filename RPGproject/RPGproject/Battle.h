#pragma once
#include "Manager.h"

enum Command { NEUTRAL, ATTACK, MAGIC, RUN_AWAY,
						DATTACK,DMAGIC};	// コマンド状態

// 戦闘画面
class Battle : public SuperScene {
private:
	int Gr_Back;		// 背景

	Command command;	// コマンド状態	

	int cursorX, cursorY;			// カーソルの座標

	bool textFlag;					// テキストを表示するかどうかのフラグ

public:
	Battle();
	~Battle();

	void UpDate();		// アップデート
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_End();	// 終了画面アップデート

	void Draw();		// 描画
	void Draw(bool flag);		// 基本的にこっちが呼ばれる
	void Draw_Start();	// 開始画面描画
	void Draw_Main();	// メイン画面描画
	void Draw_End();	// 終了画面描画
	
	// どの画面から戦闘画面に移行したか（戦闘終了時にその画面に戻る)
	void SetReturnScene(eScene scene);

	// セッターゲッター
	void SetCommand(Command command);
	Command GetCommand();
	void SetStep(eStep step);
	void SetNextScene(eScene nextScene);
};
