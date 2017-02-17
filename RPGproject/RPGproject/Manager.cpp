#include "Manager.h"

Manager::Manager() {
	playerX = 0;
	playerY = 0;
	probability = 50000;

	player = new Player();
	this->endFlag = false;
	this->NowScene = eScene::S_Title;
	this->title = new Title();
}
Manager::~Manager() {
	switch (NowScene)
	{
	case eScene::S_Title://タイトル画面
		delete title;
		break;
	case eScene::S_Field:// フィールド画面
		delete field;
		break;
	case eScene::S_Battle:// 戦闘画面
		delete battle;
		break;
	case eScene::S_SafeArea:// 拠点画面
		delete safeArea;
		break;
	case eScene::S_Dungeon://ダンジョン画面
		delete dungeon;
		break;
	case eScene::S_GameOver://ゲームオーバー画面
		delete gameOver;
		break;
	case eScene::S_GameClear://ゲームクリア画面
		delete gameClear;
		break;
	default:	//Error
		break;
	}

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

		// このシーンのプロセス
		this->field->UpDate(player->GetX(), player->GetY());

		// プレイヤーが動いたかどうかを判断するために直前の座標を保存
		playerX = player->GetX();
		playerY = player->GetY();

		// フィールドのメインプロセスが動いてる間プレイヤーのプロセスを呼び出す
		if (field->GetStep() == eStep::Main)
		{
			player->Move();
		}

		// 敵とのエンカウント
		if (player->GetX() != playerX || player->GetY() != playerY)
		{
			if (GetRand(probability) == 0)
			{
				field->SetNextScene(eScene::S_Battle);
				field->SetStep(eStep::End);
			}
		}

		// カメラの位置をプレイヤーの座標から計算して代入
		if (player->GetX() < (320 - 16))		// 左端
		{
			field->SetCameraX(0);
		}
		else if (player->GetX() > ((field->GetMapWidth() - 1) * 32) - (320 - 16))		// 右端
		{
			field->SetCameraX((field->GetMapWidth() * 32) - 640);
		}
		else		// それ以外
		{
			field->SetCameraX(player->GetX() - (320 - 16));
		}

		if (player->GetY() < (240 - 16))		// 上端
		{
			field->SetCameraY(0);
		}
		else if (player->GetY() > ((field->GetMapHeight() - 1) * 32) - (240 - 16))		// 下端
		{
			field->SetCameraY((field->GetMapHeight() * 32) - 480);
		}
		else		// それ以外
		{
			field->SetCameraY(player->GetY() - (240 - 16));
		}

		// マップとの当たり判定
		switch (field->GetMapData(player->GetX(), player->GetY()))
		{
		case 0:			// 無
			break;
		case 1:			// 壁
			player->MoveReset();		// プレイヤーの座標を直前のものに戻す
			break;
		default:
			// 基本的に来ない
			break;
		}
		break;

	case eScene::S_Battle:// 戦闘画面
		this->battle->UpDate();
		switch (battle->GetCommand())
		{
		case NEUTRAL:		// 何でもないとき
			break;
		case ATTACK:		// 何でもないとき
			break;
		case DATTACK:		// 攻撃する時
			enemy->SetHP(enemy->GetHP() - player->GetATK());		// ダメージを与える
			battle->SetCommand(NEUTRAL);
			break;
		case MAGIC:			// 何でもないとき
			break;
		case DMAGIC:		// 魔法攻撃するとき
			enemy->SetHP(enemy->GetHP() - player->GetATK());		// ダメージを与える
			battle->SetCommand(NEUTRAL);
			break;
		case RUN_AWAY:		// 何でもないとき
			break;
		default:
			// 通常来ない
			break;
		}

		// 戦闘終了
		if (enemy->GetHP() < 0 || player->GetHP() < 0)
		{
			battle->SetStep(eStep::End);
		}
		break;

	case eScene::S_SafeArea:// 拠点画面
		this->safeArea->UpDate();
		break;
	case eScene::S_Dungeon://ダンジョン画面
		this->dungeon->UpDate();
		player->Move();
		// 位置修正
		if (dungeon->GetMapData(player->GetX(), player->GetY()) == 10)
		{
			player->MoveReset();
		}
		dungeon->SetX(player->GetX()-320);
		dungeon->SetY(player->GetY()-240);
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

		// プレイヤーの初期位置移動
		player->SetX(320 - 16);
		player->SetY(240 - 16);

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
		enemy = new Enemy();
		// フィールド画面から移行したことを保存
		this->battle->SetReturnScene(eScene::S_Field);
		break;
	case eScene::S_SafeArea:// 拠点画面
		this->safeArea = new SafeArea();
		delete this->field;	// フィールド画面実体削除
		break;
	case eScene::S_Dungeon://ダンジョン画面
		this->dungeon = new Dungeon();
		player->SetX(50);
		player->SetY(50);
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
	//InitGraph();	// 全グラフィック削除
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

	// 敵削除
	delete enemy;
}

// 拠点画面からのシーン移行
void Manager::ChengeScene_SafeArea() {
	//InitGraph();	// 全グラフィック削除
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
	//InitGraph();	// 全グラフィック削除
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
	//InitGraph();	// 全グラフィック削除
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
	//InitGraph();	// 全グラフィック削除
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

		if (field->GetStep() == eStep::Main)
		{
			player->aaaDraw(field->GetMapWidth(), field->GetMapHeight());
		}

		// Debug------------------------------------------------------------
		DrawFormatString(0, 400, (0, 0, 200), "%d", field->GetMapWidth());
		// -----------------------------------------------------------------

		break;
	case eScene::S_Battle:// 戦闘画面
		this->battle->Draw();

		// Debug------------------------------------------------------------
		DrawFormatString(0, 400, (0, 0, 200), "%d", enemy->GetHP());
		// -----------------------------------------------------------------

		break;
	case eScene::S_SafeArea:// 拠点画面
		this->safeArea->Draw();
		break;
	case eScene::S_Dungeon://ダンジョン画面
		this->dungeon->Draw();
		player->aaaDraw();
		dungeon->SetX(player->GetX());
		dungeon->SetY(player->GetY());
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