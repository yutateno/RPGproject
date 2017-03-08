#include "Manager.h"

Title::Title() {
	// 画像関係
	Gr_Back = LoadGraph("Title.png");

	// 動作関係
	endFlag = false;			// シーンの終了のフラグ
	nextScene = eScene::S_End;	// 仮にゲーム終了処理を次のシーンとして初期化

	// 演出関係
	step = eStep::Start;		// このシーンの開始処理
	startCount = 0;				// このカウント数だけ演出時間が続く
	endCount = 0;				// このカウント数だけ終了演出が続く
	count = 0;					// (フレーム)時間を計る

	// アイコン関係
	Icon_x = 140;				// アイコンの絶対座標
	Icon_y = 300;				// アイコンの絶対座標
	Icon_area = 0;				// 相対的なアイコンの座標
}
Title::~Title() {
	// 画像削除
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
	// カウントアップ
	count++;
	
	// startCountだけ演出する
	if (count < startCount) return;
	// カウントをリセットしてステップを進行
	count = 0;
	step = eStep::Main;
}
void Title::UpDate_Main() {
	// アイコンの移動
	if (KeyData::Get(KEY_INPUT_UP) == 1) {
		Icon_area = 0;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
		Icon_area = 1;
	}

	// 決定
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// 相対座標から次に行くシーンを設定
		if (Icon_area == 0) {
			// フィールドへ
			nextScene = eScene::S_Field;
			// ステップ進行
			step = eStep::End;
		}
		else {
			// ゲーム終了画面へ
			nextScene = eScene::S_End;
			// ステップ進行
			step = eStep::End;
		}
	}
}
void Title::UpDate_End() {
	// カウントアップ
	count++;

	// endCountだけ演出する
	if (count < endCount) return;
	// カウントをリセットしてこのシーンを終了する
	count = 0;
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
	// 徐々に画面の表示する処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count * 5);
	// 背景
	DrawGraph(0, 0, Gr_Back, FALSE);
	// ブレンドモードの後処理
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void Title::Draw_Main() {
	// 背景
	DrawGraph(0, 0, Gr_Back, FALSE);

	// 選択アイコン
	DrawBox(Icon_x, Icon_y + (Icon_area * 70), Icon_x + 50, Icon_y + 50 + (Icon_area * 70), BLUE, TRUE);

	// TIPS
	DrawString(0, 450, "上下で移動、Zで決定", BLUE);
}
void Title::Draw_End() {
	// 徐々に画面を暗くする処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (count * 5));
	// 背景
	DrawGraph(0, 0, Gr_Back, FALSE);
	// ブレンドモードの後処理
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}