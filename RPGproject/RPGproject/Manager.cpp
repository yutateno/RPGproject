#include "Manager.h"

Manager::Manager() {

	player = new Player();
	this->endFlag = false;
	this->NowScene = eScene::S_Title;
	this->title = new Title();
}
Manager::~Manager() {
	delete player;
}

void Manager::UpDate() {

	// 【画面切り替え】
	switch (this->NowScene) {
	case eScene::S_Title://タイトル画面
		// エンドフラグが立ったら次のシーンへ移行
		if (this->title->GetEndFlag()) {
			this->ChengeScene_Title();
		}
		break;
	case eScene::S_Field:// フィールド画面
		if (this->field->GetEndFlag()) {
			this->ChengeScene_Field();
		}
		break;
	case eScene::S_Battle:// 戦闘画面
		if (this->battle->GetEndFlag()) {
			this->ChengeScene_Battle();
		}
		break;
	case eScene::S_SafeArea:// 拠点画面
		if (this->safeArea->GetEndFlag()) {
			this->ChengeScene_SafeArea();
		}
		break;
	case eScene::S_Dungeon://ダンジョン画面
		if (this->dungeon->GetEndFlag()) {
			this->ChengeScene_Dungeon();
		}
		break;
	case eScene::S_GameOver://ゲームオーバー画面
		if (this->gameOver->GetEndFlag()) {
			this->ChengeScene_GameOver();
		}
		break;
	case eScene::S_GameClear://ゲームクリア画面
		if (this->gameClear->GetEndFlag()) {
			this->ChengeScene_GameClear();
		}
		break;
	default:	//Error
		this->endFlag = true;
		break;
	}



	// 【各画面アップデート】
	switch (this->NowScene) {
	case eScene::S_Title://タイトル画面
		this->title->UpDate();
		break;
	case eScene::S_Field:// フィールド画面
		this->field->UpDate();
		player->Move();
		break;
	case eScene::S_Battle:// 戦闘画面
		this->battle->UpDate();
		break;
	case eScene::S_SafeArea:// 拠点画面
		this->safeArea->UpDate();
		break;
	case eScene::S_Dungeon://ダンジョン画面
		this->dungeon->UpDate();
		player->Move();
		break;
	case eScene::S_GameOver://ゲームオーバー画面
		this->gameOver->UpDate();
		break;
	case eScene::S_GameClear://ゲームクリア画面
		this->gameClear->UpDate();
		break;
	default:	//Error
		this->endFlag = true;
		break;
	}
}

// タイトル画面からのシーン移行
void Manager::ChengeScene_Title() {
	//InitGraph();	// 全グラフィック削除
	InitSoundMem();	// 曲データ全削除

	this->NowScene = this->title->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Field:// フィールド画面
		this->field = new Field();
		delete this->title;	// タイトル実体削除
		break;
	case eScene::S_End://ゲーム終了
		this->endFlag = true;
		delete this->title;	// タイトル実体削除
		break;
	default:	//Error
		this->endFlag = true;
		delete this->title;	// タイトル実体削除
		break;
	}
}

// フィールド画面からのシーン移行
void Manager::ChengeScene_Field() {
	//InitGraph();	// 全グラフィック削除
	InitSoundMem();	// 曲データ全削除

	this->NowScene = this->field->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Battle:// 戦闘画面
		this->battle = new Battle();
		// フィールド画面から移行したことを保存
		this->battle->SetReturnScene(eScene::S_Field);
		break;
	case eScene::S_SafeArea:// 拠点画面
		this->safeArea = new SafeArea();
		delete this->field;	// フィールド画面実体削除
		break;
	case eScene::S_Dungeon://ダンジョン画面
		this->dungeon = new Dungeon();
		player->SetX(0);
		player->SetY(0);
		delete this->field;
		break;
	case eScene::S_End://ゲーム終了
		this->endFlag = true;
		delete this->field;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->field;
		break;
	}
}

// 戦闘画面からのシーン移行
void Manager::ChengeScene_Battle() {
	InitGraph();	// 全グラフィック削除
	InitSoundMem();	// 曲データ全削除

	this->NowScene = this->battle->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Field:// フィールド画面
		this->field = new Field();
		delete this->battle;	// 戦闘画面実体削除
		break;
	case eScene::S_SafeArea:// 拠点画面
		this->safeArea = new SafeArea();
		delete this->battle;
		break;
	case eScene::S_Dungeon://ダンジョン画面
		this->dungeon = new Dungeon();
		delete this->battle;
		break;
	case eScene::S_GameOver://ゲームオーバー画面
		this->gameOver = new GameOver();
		delete this->battle;
		break;
	case eScene::S_End://ゲーム終了
		this->endFlag = true;
		delete this->battle;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->battle;
		break;
	}
}

// 拠点画面からのシーン移行
void Manager::ChengeScene_SafeArea() {
	InitGraph();	// 全グラフィック削除
	InitSoundMem();	// 曲データ全削除

	this->NowScene = this->safeArea->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Field:// フィールド画面
		this->field = new Field();
		delete this->safeArea;	// 拠点画面実体削除
		break;
	case eScene::S_Battle:// 戦闘画面
		this->battle = new Battle();
		// 拠点画面から移行したことを保存
		this->battle->SetReturnScene(eScene::S_SafeArea);
		delete this->safeArea;
		break;
	case eScene::S_End://ゲーム終了
		this->endFlag = true;
		delete this->safeArea;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->safeArea;
		break;
	}
}

// ダンジョン画面からのシーン移行
void Manager::ChengeScene_Dungeon() {
	InitGraph();	// 全グラフィック削除
	InitSoundMem();	// 曲データ全削除

	this->NowScene = this->dungeon->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Field:// フィールド画面
		this->field = new Field();
		delete this->dungeon;	// ダンジョン画面実体削除
		break;
	case eScene::S_Battle:// 戦闘画面
		this->battle = new Battle();
		// ダンジョン画面から移行したことを保存
		this->battle->SetReturnScene(eScene::S_Dungeon);
		delete this->dungeon;
		break;
	case eScene::S_GameClear://ゲームクリア画面
		this->gameClear = new GameClear();
		delete this->dungeon;
		break;
	case eScene::S_End://ゲーム終了
		this->endFlag = true;
		delete this->dungeon;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->dungeon;
		break;
	}
}

// ゲームオーバー画面からのシーン移行
void Manager::ChengeScene_GameOver() {
	InitGraph();	// 全グラフィック削除
	InitSoundMem();	// 曲データ全削除

	this->NowScene = this->gameOver->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Title://タイトル画面
		this->title = new Title();
		delete this->gameOver;	// ゲームオーバー画面実体削除
		break;
	case eScene::S_End://ゲーム終了
		this->endFlag = true;
		delete this->gameOver;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->gameOver;
		break;
	}
}

// ゲームクリア画面からのシーン移行
void Manager::ChengeScene_GameClear() {
	InitGraph();	// 全グラフィック削除
	InitSoundMem();	// 曲データ全削除

	this->NowScene = this->gameClear->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Title://タイトル画面
		this->title = new Title();
		delete this->gameClear;	// ゲームクリア画面実体削除
		break;
	case eScene::S_End://ゲーム終了
		this->endFlag = true;
		delete this->gameClear;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->gameClear;
		break;
	}
}

void Manager::Draw() {
	// 【各画面描画】
	switch (this->NowScene) {
	case eScene::S_Title://タイトル画面
		this->title->Draw();
		break;
	case eScene::S_Field:// フィールド画面
		this->field->Draw();
		player->aaaDraw();
		break;
	case eScene::S_Battle:// 戦闘画面
		this->battle->Draw();
		break;
	case eScene::S_SafeArea:// 拠点画面
		this->safeArea->Draw();
		break;
	case eScene::S_Dungeon://ダンジョン画面
		this->dungeon->Draw();
		player->aaaDraw();
		break;
	case eScene::S_GameOver://ゲームオーバー画面
		this->gameOver->Draw();
		break;
	case eScene::S_GameClear://ゲームクリア画面
		this->gameClear->Draw();
		break;
	default:	//Error
		this->endFlag = true;
		break;
	}
}