#include "Manager.h"

Manager::Manager() {
	playerX = 0;
	playerY = 0;
	probability = 200;

	// 戦闘関連
	turn = true;		// true : プレイヤーのターン
	count = 0;
	preHP = 0;
	lose = false;

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
		FieldProcess();
		break;

	case eScene::S_Battle:// 戦闘画面
		// 直前のHPを保存
		if (count == 0)
		{
			if (turn)
			{
				preHP = enemy->GetHP();
			}
			else
			{
				preHP = player->GetHP();
			}
		}

		BattleProcess();
		break;
		
	case eScene::S_SafeArea:// 拠点画面
		SafeAreaProcess();
		break;

	case eScene::S_Dungeon://ダンジョン画面
		DungeonProcess();
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
		count = 0;
		enemy = new Enemy((int)GetRand(1));
		// フィールド画面から移行したことを保存
		this->battle->SetReturnScene(eScene::S_Field);
		break;
	case eScene::S_SafeArea:// 拠点画面
		this->safeArea = new SafeArea();
		// プレイヤーの初期位置移動
		player->SetX(320 - 16);
		player->SetY(480 - 64);
		delete this->field;	// フィールド画面実体削除
		break;
	case eScene::S_Dungeon://ダンジョン画面
		this->dungeon = new Dungeon();
		player->SetX(464);
		player->SetY(864);
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

	if (lose)
	{
		NowScene = eScene::S_GameOver;
	}
	else
	{
		// 経験値の処理の処理
		player->SetEXP(player->GetEXP() + enemy->GetEXP());


		// レベルアップの処理
		if (player->GetLV() * 20 < player->GetEXP())
		{
			player->SetEXP(0);
			player->SetLV(player->GetLV() + 1);
			// 最大HPMP上昇
			player->SetMaxHP(player->GetMaxHP() + player->GetLV());
			player->SetMaxMP(player->GetMaxMP() + player->GetLV());
		}
		this->NowScene = this->battle->GetNextScene();
	}

	switch (this->NowScene) {
	case eScene::S_Field:// フィールド画面
		this->field = new Field();

		// プレイヤーの初期位置移動
		player->SetX(playerX);
		player->SetY(playerY);

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

		// プレイヤーの初期位置移動
		player->SetX(320 - 16);
		player->SetY(240 - 16);

		delete this->safeArea;	// 拠点画面実体削除
		break;
	case eScene::S_Battle:// 戦闘画面
		this->battle = new Battle();
		count = 0;
		enemy = new Enemy();
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
		// プレイヤーの初期位置移動
		player->SetX(320 - 16);
		player->SetY(240 - 16);
		delete this->dungeon;	// ダンジョン画面実体削除
		break;
	case eScene::S_Battle:// 戦闘画面
		this->battle = new Battle();
		count = 0;
		enemy = new Enemy();
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

		break;
	case eScene::S_Battle:// 戦闘画面
		// コマンドの表示
		if (turn&&count == 0)
		{
			battle->Draw(true);
		}
		else
		{
			battle->Draw(false);
		}

		// ログの表示
		if (count != 0)
		{
			// 勝利時
			if (enemy->GetHP() <= 0)
			{
				DrawFormatString(0, 384, WHITE, "勝利\n %d の経験値を獲得！", enemy->GetEXP());
			}
			// 敗北時
			else if (player->GetHP() <= 0)
			{
				DrawFormatString(0, 384, WHITE, "敗北");
			}
			else
			{
				if (turn)
				{
					DrawFormatString(0, 384, WHITE, " %s の攻撃！\n %s に %d ダメージ！", player->GetName().c_str(), enemy->GetName().c_str(), preHP - enemy->GetHP());
				}
				else
				{
					DrawFormatString(0, 384, WHITE, " %s の攻撃！\n %s に %d ダメージ！", enemy->GetName().c_str(), player->GetName().c_str(), preHP - player->GetHP());
				}
			}
		}

		// メイン画面のみの描写
		if (battle->GetStep() == eStep::Main)
		{
			// 敵の描写
			if (turn)
			{
				if (battle->GetDamageFlag())
				{
					if (count % 5 != 0)
					{
						enemy->aaaDraw();
					}
				}
				else
				{
					enemy->aaaDraw();
				}
			}
			else
			{
				enemy->aaaDraw();
			}

			// プレイヤーのステータス
			DrawFormatString(0, 0, WHITE, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());

			// debug-------------------------------------------------------------------------------------
			// 敵のステータス
			DrawFormatString(300, 0, WHITE, "%s\nHP:%d\nMP:%d", enemy->GetName().c_str(), enemy->GetHP(), enemy->GetMP());
			// -----------------------------------------------------------------------------------------
		}
		break;

	case eScene::S_SafeArea:// 拠点画面

		this->safeArea->Draw();

		//マップチップの当たり判定
		if (safeArea->GetStep() == eStep::Main) {
			player->aaaDraw(safeArea->GetMapWidth(), safeArea->GetMapHeight());
		}
		break;

	case eScene::S_Dungeon://ダンジョン画面
		
		this->dungeon->Draw();
		
		//マップチップの当たり判定
		if (dungeon->GetStep() == eStep::Main) {
			player->aaaDraw(dungeon->GetMapWidth(), dungeon->GetMapHeight());
		}
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

void Manager::FieldProcess()
{
	// このシーンのプロセス
	this->field->UpDate(player->GetX(), player->GetY());

	// プレイヤーが動いたかどうかを判断するために直前の座標を保存
	playerX = player->GetX();
	playerY = player->GetY();

	// フィールドのメインプロセスが動いてる間プレイヤーのプロセスを呼び出す
	if (field->GetStep() == eStep::Main)
	{
		player->Process();
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

	// マップとの当たり判定----------------------------------
	for (int i = 0;i < 2;i++)
	{
		for (int j = 0;j < 2;j++)
		{
			switch (field->GetMapData(player->GetX() + (i * (32 - 1)), player->GetY() + (j * (32 - 1))))
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
		}
	}
	// --------------------------------------------------
}

void Manager::BattleProcess()
{
	// ログの表示中は入力を受け付けない
	if (count == 0 || battle->GetStep() == eStep::End)
	{
		this->battle->UpDate();
	}
	else
	{
		// アニメーションとかしたければここかな
	}

	// 戦闘勝利
	if (enemy->GetHP() <= 0)
	{
		if (count < 100)			// ログをXフレーム表示する
		{
			count++;
		}
		else
		{
			battle->SetStep(eStep::End);
		}
	}
	// 戦闘敗北
	else if (player->GetHP() <= 0)
	{
		if (count < 100)			// ログをXフレーム表示する
		{
			count++;
		}
		else
		{
			lose = true;
			battle->SetStep(eStep::End);
		}
	}
	else
	{
		// 自分のターン
		if (turn)
		{
			if (battle->GetDamageFlag())		// battleからダメージを与える支持を受けたら
			{
				if (count == 0)
				{
					switch (battle->GetCommand())
					{
					case NEUTRAL:			// 何もなし
						break;

					case ATTACK:
						break;

					case MAGIC:
						// MP消費
						if (player->GetMP() > 0)
						{
							player->SetMP(player->GetMP() - 1);
						}
						else
						{
							battle->SetDamageFlag(false);			// フラグを折る
							battle->SetCommand(NEUTRAL);
							count = 0;			// カウントを戻す
							return;
						}
						break;

					case RUN_AWAY:
						break;

					default:
						break;
					}
					player->SetATK(battle->GetDamageWidth());			// 選択した行動を反映する
					enemy->SetHP(enemy->GetHP() - player->GetATK());		// ダメージ
				}
				if (count < 50)			// ログをXフレーム表示する
				{
					count++;
				}
				else
				{
					battle->SetDamageFlag(false);			// フラグを折る
					battle->SetCommand(NEUTRAL);
					count = 0;			// カウントを戻す
					turn = false;			// あいてにターンを渡す
				}
			}
		}
		// 相手のターン
		else
		{
			if (count == 0)
			{
				player->SetHP(player->GetHP() - enemy->GetATK());		// 攻撃力分だけダメージ
			}
			if (count < 50)			// ログをXフレーム表示する
			{
				count++;
			}
			else
			{
				count = 0;			// カウントを戻す
				turn = true;			// プレイヤーにターンを渡す
			}
		}
	}
}

void Manager::DungeonProcess() {
	this->dungeon->UpDate(player->GetX(), player->GetY());

	// プレイヤーが動いたかどうかを判断するために直前の座標を保存
	playerX = player->GetX();
	playerY = player->GetY();

	// ダンジョンのメインプロセスが動いてる間プレイヤーのプロセスを呼び出す
	if (dungeon->GetStep() == eStep::Main)
	{
		player->Process();
	}

	// 位置修正
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			switch (dungeon->GetMapData(player->GetX() + (i * (32 - 1)), player->GetY() + (j * (32 - 1))))
			{
			case 10:
				player->MoveReset();		// プレイヤーの座標を直前のものに戻す
				break;
			case 20:
				dungeon->SetField(true);
				break;
			case 30:
				player->MoveReset();
				dungeon->SetBoss(true);
				break;
			default:
				// 基本的に来ない
				break;
			}
		}
	}

	// ボスに触れたら
	if (dungeon->GetBoss() == true && player->GetmenuFlag() == false) {
		// 動いたらキャンセル
		if (playerY != player->GetY() || playerX != player->GetX()) {
			dungeon->SetBoss(false);
		}
		// そのままなら戦闘
		else {
			if (KeyData::Get(KEY_INPUT_Z) == 1) {
				dungeon->SetBattle(true);
			}
		}
	}
	// 敵とのエンカウント
	if ((player->GetX() != playerX || player->GetY() != playerY) && player->GetmenuFlag() == false)
	{
		if (GetRand(probability) == 0)
		{
			dungeon->SetBattle(true);
		}
	}
	// カメラの位置をプレイヤーの座標から計算して代入
	if (player->GetX() < (320 - 16))		// 左端
	{
		dungeon->SetX(-32);
	}
	else if (player->GetX() > (dungeon->GetMapWidth() * 32 - 32) - (320 - 16))		// 右端
	{
		dungeon->SetX((dungeon->GetMapWidth() * 32) - 640 - 32);
	}
	else		// それ以外
	{
		dungeon->SetX(player->GetX() - (320 - 16) - 32);
	}

	if (player->GetY() < (240 - 16))		// 上端
	{
		dungeon->SetY(-32);
	}
	else if (player->GetY() > (dungeon->GetMapHeight() * 32 - 32) - (240 - 16))		// 下端
	{
		dungeon->SetY((dungeon->GetMapHeight() * 32) - 480 - 32);
	}
	else		// それ以外
	{
		dungeon->SetY(player->GetY() - (240 - 16) - 32);
	}
}

void Manager::SafeAreaProcess() {
	this->safeArea->UpDate(player->GetX(), player->GetY());

	// プレイヤーが動いたかどうかを判断するために直前の座標を保存
	playerX = player->GetX();
	playerY = player->GetY();
	
	if (safeArea->GetStep() == eStep::Main && safeArea->GetTalk() == false && safeArea->GetShop() == false)
	{
		player->Process();
	}

	// カメラの位置をプレイヤーの座標から計算して代入
	if (player->GetX() < (320 - 16))		// 左端
	{
		safeArea->SetX(0);
	}
	else if (player->GetX() > (safeArea->GetMapWidth() * 32 - 32) - (320 - 16))		// 右端
	{
		safeArea->SetX((safeArea->GetMapWidth() * 32) - 640);
	}
	else		// それ以外
	{
		safeArea->SetX(player->GetX() - (320 - 16));
	}

	if (player->GetY() < (240 - 16))		// 上端
	{
		safeArea->SetY(0);
	}
	else if (player->GetY() > (safeArea->GetMapHeight() * 32 - 32) - (240 - 16))		// 下端
	{
		safeArea->SetY((safeArea->GetMapHeight() * 32) - 480);
	}
	else		// それ以外
	{
		safeArea->SetY(player->GetY() - (240 - 16));
	}

	// 位置修正
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			switch (safeArea->GetMapData(player->GetX() + (i * (32 - 1)), player->GetY() + (j * (32 - 1))))
			{
			case 10:	// 壁
				player->MoveReset();
				break;

			case 11:	// 出口
				safeArea->SetField(true);
				break;

			case 12:	// 案内人
				player->MoveReset();
				safeArea->SetPeople(true);
				break;

			case 13:	//道具
				player->MoveReset();
				safeArea->SetItem(true);
				break;

			case 14:	// 癒し
				player->MoveReset();
				safeArea->SetInn(true);
				break;

			default:
				break;

			}
		}
	}

	// 一般人に触れたら
	if (safeArea->GetPeople() == true) {
		// 動いたらキャンセル
		if (playerY != player->GetY() || playerX != player->GetX()) {
			safeArea->SetPeople(false);
		}
		// メニューを開いたら
		else if (player->GetmenuFlag() == true) {
			safeArea->SetPeople(false);
		}
		// そのままなら会話
		else {
			// safearea にて動作させてる
		}
	}

	// 噴水に触れたら
	if (safeArea->GetInn() == true) {
		// 動いたらキャンセル
		if (playerY != player->GetY() || playerX != player->GetX()) {
			safeArea->SetInn(false);
		}
		// メニューを開いたら
		else if (player->GetmenuFlag() == true) {
			safeArea->SetInn(false);
		}
		// そのままなら回復
		else {
			if (safeArea->GetHeal() == true) {
				player->SetHP(player->GetMaxHP());
				player->SetMP(player->GetMaxMP());
				safeArea->SetHeal(false);
			}
		}
	}

	// 道具屋に触れたら
	if (safeArea->GetItem() == true) {
		// 動いたらキャンセル
		if (playerY != player->GetY() || playerX != player->GetX()) {
			safeArea->SetItem(false);
		}
		// メニューを開いたら
		else if (player->GetmenuFlag() == true) {
			safeArea->SetItem(false);
		}
		// そのままならショップ画面
		else {
			// 買ったとき
			if (safeArea->GetBuy() == true) {
				player->BuyItem(safeArea->GetID());
				safeArea->SetBuy(false);
			}
			// 売ったとき
			if (safeArea->GetSell() == true) {
				player->SellItem(safeArea->GetNum(), safeArea->GetID());
				safeArea->SetSell(false);
			}
			// 持ち物欄の写し
			for (int i = 0; i < 9; i++) {
				safeArea->SetnumID(i, player->GetID(i));
			}
			// safearea にて動作
		}
	}
}