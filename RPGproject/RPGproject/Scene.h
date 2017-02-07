#pragma once
#include "Manager.h"

// シーンの列挙
enum class eScene : __int8 {
	S_Title,	// タイトル
	S_Field,	// フィールド
	S_Battle,	// 戦闘
	S_SafeArea,	// 町とかの拠点
	S_Dungeon,	// ダンジョン
	S_GameClear,// ゲームクリア
	S_GameOver,	// ゲームオーバー
	S_End		// ゲーム終了
};

// シーン内の段階
enum class eStep : __int8 { Start, Main, End};

class SuperScene {
protected:
	bool endFlag;	// シーン終了フラグ trueで終了

	eScene nextScene;	// 次のシーン【受け渡す用】

	eStep step;		// 0:開始	1:メイン	2:終了
	int startCount;	// 開始画面のカウント
	int endCount;	// 終了画面のカウント
	
public:
	SuperScene();
	~SuperScene();

	virtual void UpDate() = 0;	// アップデート
	void UpDate_Start() {};	// 開始画面アップデート
	void UpDate_Main() {};	// メイン画面アップデート
	void UpDate_End() {};	// 終了画面アップデート

	virtual void Draw() = 0;// 描画
	void Draw_Start() {};	// 開始画面描画
	void Draw_Main() {};	// メイン画面描画
	void Draw_End() {};		// 終了画面描画

	bool GetEndFlag();
	eScene GetNextScene();
};