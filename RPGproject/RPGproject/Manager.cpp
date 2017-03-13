#include "Manager.h"

Manager::Manager() {
	// 移動全般
	playerX = 0;		// 絶対座標
	playerY = 0;		// 絶対座標
	playerDamageFlag = false;	// ダメージを受けているかどうか
	enemyDamageFlag = false;	// ダメージを受けているかどうか
	probability = 200;	// エンカウントする確率 : 1/probability
	drop = 200;			// 敵がアイテムを落とす確率 : item/drop

	// 戦闘関連
	turn = true;			// true : プレイヤーのターン
	statusX = 16;			// コマンドが乗ってる板の座標
	statusY = 16;			// コマンドが乗ってる板の座標

	// ログ関係
	logCount = 0;			//(フレーム)カウント
	logTime = 120;			// 表示時間			
	logX = 8;				// ログが乗ってる板の座標
	logY = 320;				// ログが乗ってる板の座標
	logLineNum = 4;			// １ページに何行表示するか
	lineTime = (int)(logTime / 4);		//行の更新時間

	// ゲーム進行関係
	player = new Player();			// プレイヤー本体
	endFlag = false;				// ゲーム終了するフラグ
	NowScene = eScene::S_Title;		// 最初の画面を指定
	title = new Title();			// 最初の画面を生成
}
Manager::~Manager() {
	// 現在のシーンを削除
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

	// プレイヤー削除
	delete player;
}

void Manager::UpDate() {

	// 【画面切り替え】
	switch (NowScene) {
	case eScene::S_Title://タイトル画面
		// エンドフラグが立ったら次のシーンへ移行
		if (title->GetEndFlag()) {
			ChengeScene_Title();
		}
		break;

	case eScene::S_Field:// フィールド画面
		if (field->GetEndFlag()) {
			ChengeScene_Field();
		}
		break;

	case eScene::S_Battle:// 戦闘画面
		if (battle->GetEndFlag()) {
			ChengeScene_Battle();
		}
		break;

	case eScene::S_SafeArea:// 拠点画面
		if (safeArea->GetEndFlag()) {
			ChengeScene_SafeArea();
		}
		break;

	case eScene::S_Dungeon://ダンジョン画面
		if (dungeon->GetEndFlag()) {
			ChengeScene_Dungeon();
		}
		break;
	case eScene::S_GameOver://ゲームオーバー画面
		if (gameOver->GetEndFlag()) {
			ChengeScene_GameOver();
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
	switch (NowScene) {
	case eScene::S_Title://タイトル画面
		title->UpDate();
		break;

	case eScene::S_Field:// フィールド画面
		// フィールドの処理は長いので別の関数へ逃がした
		FieldProcess();
		break;

	case eScene::S_Battle:// 戦闘画面
		// バトルの処理は長いので別の関数へ逃がした
		BattleProcess();
		break;
		
	case eScene::S_SafeArea:// 拠点画面
		SafeAreaProcess();
		break;

	case eScene::S_Dungeon://ダンジョン画面
		DungeonProcess();
		break;

	case eScene::S_GameOver://ゲームオーバー画面
		gameOver->UpDate();
		break;

	case eScene::S_GameClear://ゲームクリア画面
		gameClear->UpDate();
		break;

	default:	//Error
		endFlag = true;
		break;
	}
}

// タイトル画面からのシーン移行
void Manager::ChengeScene_Title() {
	// 次のシーンをタイトルから取得して設定
	NowScene = title->GetNextScene();

	// 次のシーンによって処理を変える
	switch (NowScene) {
	case eScene::S_Field:// フィールド画面
		// フィールド生成
		field = new Field();

		// プレイヤーの初期位置移動
		player->SetX(320 - 16);
		player->SetY(240 - 16);
		break;

	case eScene::S_End://ゲーム終了
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// タイトル削除
	delete title;
}

// フィールド画面からのシーン移行
void Manager::ChengeScene_Field() {
	// 次のシーンをフィールドから取得
	NowScene = field->GetNextScene();

	// 次のシーンによって処理を変える
	switch (NowScene) {
	case eScene::S_Battle:// 戦闘画面
		battle = new Battle();

		// フィールド画面から移行したことを保存
		battle->SetReturnScene(eScene::S_Field);

		// 敵の生成
		enemy = new Enemy((int)GetRand(1));
		break;

	case eScene::S_SafeArea:// 拠点画面
		this->safeArea = new SafeArea();
		// プレイヤーの初期位置移動
		player->SetX(320 - 16);
		player->SetY(480 - 64);
		safeArea->SetMoney(player->GetMoney());
		break;

	case eScene::S_Dungeon://ダンジョン画面
		dungeon = new Dungeon();
		player->SetX(464);
		player->SetY(864);
		break;

	case eScene::S_End://ゲーム終了
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// フィールド画面実体削除
	delete field;
}

// 戦闘画面からのシーン移行
void Manager::ChengeScene_Battle() {
	// バトルから次のシーンを取得
	NowScene = battle->GetNextScene();

	// 次のシーンによって処理を変更
	switch (NowScene) {
	case eScene::S_Field:// フィールド画面
		field = new Field();

		// プレイヤーの初期位置を保存しておいて
		player->SetX(playerX);
		player->SetY(playerY);
		break;

	case eScene::S_SafeArea:// 拠点画面
		safeArea = new SafeArea();
		break;

	case eScene::S_Dungeon://ダンジョン画面
		dungeon = new Dungeon();
		break;

	case eScene::S_GameOver://ゲームオーバー画面
		gameOver = new GameOver();
		break;

	case eScene::S_End://ゲーム終了
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// 敵削除
	delete enemy;

	// 戦闘画面実体削除
	delete battle;
}

// 拠点画面からのシーン移行
void Manager::ChengeScene_SafeArea() {
	// 次のシーンをセーフエリアから取得
	NowScene = safeArea->GetNextScene();

	switch (NowScene) {
	case eScene::S_Field:// フィールド画面
		field = new Field();

		// プレイヤーの初期位置移動
		player->SetX(320 - 16);
		player->SetY(240 - 16);
		break;

	case eScene::S_Battle:// 戦闘画面
		battle = new Battle();

		// 敵生成
		enemy = new Enemy();

		// 拠点画面から移行したことを保存
		battle->SetReturnScene(eScene::S_SafeArea);
		break;

	case eScene::S_End://ゲーム終了
		endFlag = true;
		break;

	default:	//Error
		this->endFlag = true;
		break;
	}

	// 拠点画面実体削除
	delete safeArea;
}

// ダンジョン画面からのシーン移行
void Manager::ChengeScene_Dungeon() {
	// 次のシーンをダンジョンから入手
	NowScene = dungeon->GetNextScene();

	switch (NowScene) {
	case eScene::S_Field:// フィールド画面
		field = new Field();

		// プレイヤーの初期位置移動
		player->SetX(320 - 16);
		player->SetY(240 - 16);
		break;

	case eScene::S_Battle:// 戦闘画面
		battle = new Battle();

		// 敵生成
		enemy = new Enemy();

		// ダンジョン画面から移行したことを保存
		this->battle->SetReturnScene(eScene::S_Dungeon);
		break;

	case eScene::S_GameClear://ゲームクリア画面
		this->gameClear = new GameClear();
		break;

	case eScene::S_End://ゲーム終了
		this->endFlag = true;
		break;

	default:	//Error
		this->endFlag = true;
		break;
	}

	delete dungeon;	// ダンジョン画面実体削除
}

// ゲームオーバー画面からのシーン移行
void Manager::ChengeScene_GameOver() {
	// ゲームオーバーから次のシーンを取得
	NowScene = gameOver->GetNextScene();

	switch (NowScene) {
	case eScene::S_Title://タイトル画面

		// 

		title = new Title();
		break;

	case eScene::S_End://ゲーム終了
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// ゲームオーバー画面実体削除
	delete gameOver;
}

// ゲームクリア画面からのシーン移行
void Manager::ChengeScene_GameClear() {
	// ゲームクリアから次のシーンを取得
	NowScene = gameClear->GetNextScene();

	switch (NowScene) {
	case eScene::S_Title://タイトル画面
		title = new Title();
		break;

	case eScene::S_End://ゲーム終了
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// ゲームクリア画面実体削除
	delete gameClear;
}

void Manager::Draw() {
	// 【各画面描画】
	switch (NowScene) {
	case eScene::S_Title://タイトル画面
		title->Draw();
		break;

	case eScene::S_Field:// フィールド画面
		field->Draw();

		// フィールドのステップがメインならプレイヤーを描写
		if (field->GetStep() == eStep::Main)
		{
			player->aaaDraw(field->GetMapWidth(), field->GetMapHeight());
		}
		break;

	case eScene::S_Battle:// 戦闘画面
		BattleDraw();
		break;

	case eScene::S_SafeArea:// 拠点画面

		this->safeArea->Draw();

		//マップチップの当たり判定
		if (safeArea->GetStep() == eStep::Main) {
			player->aaaDraw(safeArea->GetMapWidth(), safeArea->GetMapHeight());
		}

		safeArea->Draw_UI();
		
		break;

	case eScene::S_Dungeon://ダンジョン画面
		
		this->dungeon->Draw();
		
		//マップチップの当たり判定
		if (dungeon->GetStep() == eStep::Main) {
			player->aaaDraw(dungeon->GetMapWidth(), dungeon->GetMapHeight());
			dungeon->Draw_UI();
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
	switch (battle->GetStep())
	{
	case eStep::Start:
		// プレイヤーが先手
		turn = true;

		// コマンド等の処理
		battle->UpDate();

		// 演出中ではなければ
		if (log.size() == 0)
		{
			// ログ入力
			log.push_back(enemy->GetName() + " が襲いかかってきた！");
		}
		break;

	case eStep::Main:
		// 演出中ではなければ
		if (log.size() == 0)
		{
			// コマンド等の処理
			battle->UpDate();

			// 戦闘勝利
			if (enemy->GetHP() <= 0)
			{
				// ログ入力
				log.push_back(enemy->GetName() + " を倒した！");
				log.push_back(to_string(enemy->GetEXP()) + " の経験値を獲得！");
				log.push_back(to_string(enemy->GetMoney()) + " ゴールドを手に入れた！");

				// 戦闘報酬
				player->SetEXP(player->GetEXP() + enemy->GetEXP());				// 経験値
				player->SetMoney(player->GetMoney() + enemy->GetMoney());		// お金
				
				// レベルアップ
				if (player->GetEXP() > player->GetLV() * 20)
				{
					// 繰越分を与える
					player->SetEXP(player->GetEXP() - player->GetLV() * 20);
					// レベルを上げる
					player->SetLV(player->GetLV() + 1);
					// ステータス上昇
					player->SetMaxHP(player->GetMaxHP() + player->GetLV());
					player->SetMaxMP(player->GetMaxMP() + player->GetLV());
					player->SetPower(player->GetPower() + player->GetLV());

					// ログ入力
					log.push_back("レベルアップ！");
					log.push_back(player->GetName() + " は LV" + to_string(player->GetLV()) + " になった！");
					log.push_back("ステータスが上がった！");
				}

				// バトルのステップ進行
				battle->SetStep(eStep::End);
			}
			// 戦闘敗北
			else if (player->GetHP() <= 0)
			{
				// ログ入力
				log.push_back("あなたは死んでしまった・・・");

				// ゲームオーバー画面へ
				battle->SetNextScene(eScene::S_GameOver);

				// バトルのステップ進行
				battle->SetStep(eStep::End);
			}
			else
			{
				// 自分のターン
				if (turn)
				{
					// battleからダメージを与える指示を受けたら
					if (battle->GetDamageFlag())
					{
						switch (battle->GetCommand())
						{
						case NEUTRAL:			// 何もなし
							break;

						case ATTACK:
							player->SetATKName("攻撃");
							break;

						case MAGIC:
							// MP消費
							if (player->GetMP() > 0)
							{
								player->SetATKName("魔法攻撃");
								player->SetMP(player->GetMP() - 1);
							}
							// MPが足りない場合
							else
							{
								battle->SetDamageFlag(false);			// フラグを折る
								battle->SetCommand(NEUTRAL);			// バトルのコマンドを元に戻す
								return;
							}
							break;

						case RUN_AWAY:
							break;

						default:
							break;
						}

						// 仮置き
						int hp = enemy->GetHP();

						//ダメージ決定
						player->SetATK(battle->GetDamageWidth());			// 選択した行動を反映する
						enemy->SetHP(enemy->GetHP() - player->GetATK());	// ダメージ
						enemyDamageFlag = true;							// ダメージフラグを立てて演出

						// ログ入力
						log.push_back(player->GetName() + " の攻撃！");
						log.push_back(enemy->GetName() + " に" + to_string(hp - enemy->GetHP()) + " のダメージ！");

						battle->SetDamageFlag(false);			// フラグを折る
						battle->SetCommand(NEUTRAL);			// バトルのコマンドを戻す
						turn = false;							// あいてにターンを渡す
					}
				}
				// 相手のターン
				else
				{
					// 仮置き
					int hp = player->GetHP();

					// 攻撃処理とダメージ
					enemy->AttackProcess();
					player->SetHP(player->GetHP() - enemy->GetATK());		// 攻撃力分だけダメージ
					playerDamageFlag = true;		// ダメージフラグを立てて演出

					// ログ入力
					log.push_back(enemy->GetName() + " の攻撃！");
					log.push_back(player->GetName() + " に" + to_string(hp - player->GetHP()) + " のダメージ！");
					turn = true;					// プレイヤーにターンを渡す
				}
			}
		}
		break;

	case eStep::End:
		// 演出中ではなければ
		if (log.size() == 0)
		{
			battle->UpDate();
		}
		break;

	default:
		// エラー
		break;
	}
}
void Manager::BattleDraw()
{
	// 背景
	battle->Draw();

	// ステップによって表示を分ける
	switch (battle->GetStep())
	{
	case eStep::Start:
		// 徐々に画面の表示する処理
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, battle->GetCount() * 3);

		// 敵
		enemy->aaaDraw();

		// ブレンドモードの後処理
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;

	case eStep::Main:
		// 生きていれば
		if (enemy->GetHP() > 0)
		{
			if (enemyDamageFlag)
			{
				// 点滅
				if (logCount % 5 == 0)
				{
					enemy->aaaDraw();
				}
			}
			else
			{
				enemy->aaaDraw();
			}
		}

		// プレイヤーのステータス
		// ステータス背景
		DrawBox(statusX, statusY, statusX + 120, statusY + 120, BLACK, true);
		DrawBox(statusX, statusY, statusX + 120, statusY + 120, WHITE, false);
		// ステータス
		// ダメージを食らっているとき
		if (playerDamageFlag)
		{
			DrawFormatString(statusX + 24 + GetRand(8) - GetRand(8), statusY + 24 + GetRand(8) - GetRand(8), WHITE, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());
		}
		// 通常時
		else
		{
			DrawFormatString(statusX + 24, statusY + 24, WHITE, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());
		}
		
		break;

	case eStep::End:
		// Managerで表示すべきものはない
		break;

	default:
		// エラー
		break;
	}

	// ------------------------------------------------------------------------
	// ログここから
	// コマンド選択中なら表示しない
	if (battle->GetStep() == eStep::Main && turn && log.size() == 0)
	{
		battle->Draw_Command();
	}
	// 演出中なら表示
	else
	{
		// ログ背景
		DrawBox(logX, logY, logX + 600, logY + 150, BLACK, true);
		DrawBox(logX, logY, logX + 600, logY + 150, WHITE, false);
		// ログ出力
		// 一ページを超えていたら
		if (log.size() > (unsigned)logLineNum)
		{
			// 表示
			for (int i = 0, n = logLineNum;i < n;i++)
			{
				DrawFormatString(logX + 32, logY + 32 + (i * 32), WHITE, log[i].c_str());

				// 行ごとのラグ
				if (logCount < (i + 1) * lineTime)
				{
					break;
				}
			}

			// ページ送り
			if (logCount == logTime)
			{
				log.erase(log.begin(), log.begin() + 4);
				logCount = 0;
			}
		}
		else
		{
			// 表示
			for (int i = 0, n = log.size();i < n;i++)
			{
				DrawFormatString(logX + 32, logY + 32 + (i * 32), WHITE, log[i].c_str());

				// 行ごとのラグ
				if (logCount < (i + 1) * lineTime)
				{
					break;
				}
			}

			// 表示終了
			if (logCount == logTime)
			{
				log.clear();
				logCount = 0;
				playerDamageFlag = false;
				enemyDamageFlag = false;
			}
		}

		// 表示時間の計算
		if (logCount < logTime)
		{
			logCount++;
		}
	}

	// ログここまで
	// ------------------------------------------------------------------------
}

void Manager::DungeonProcess() {
	this->dungeon->UpDate(player->GetX(), player->GetY());

	// 宝箱
	for (int i = 0; i < 10; i++) {
		dungeon->SetTreasure(i, player->GetTreasure(i));
	}

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
			case 40:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(0);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 41:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(1);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 42:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(2);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 43:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(3);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 44:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(4);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 45:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(5);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 46:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(6);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 47:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(7);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 48:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(8);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			case 49:
				player->MoveReset();
				dungeon->SetTouch(true);
				dungeon->SetNum(9);
				dungeon->SetTreasure(dungeon->GetNum(), player->GetTreasure(dungeon->GetNum()));
				break;
			default:
				// 基本的に来ない
				break;
			}
		}
	}

	// ボスに触れたら
	if (dungeon->GetBoss() == true) {
		// 動いたらキャンセル
		if (playerY != player->GetY() || playerX != player->GetX()) {
			dungeon->SetBoss(false);
		}
		// メニュー画面を開いたら
		else if (player->GetmenuFlag() == true) {
			dungeon->SetBoss(false);
		}
		// そのままなら戦闘
		else {
			if (KeyData::Get(KEY_INPUT_Z) == 1) {
				dungeon->SetBattle(true);
			}
		}
	}

	// 宝箱に触れたら
	if (dungeon->GetTouch() == true) {
		// 動いたらキャンセル
		if (playerY != player->GetY() || playerX != player->GetX()) {
			dungeon->SetTouch(false);
		}
		// メニュー画面を開いたら
		else if (player->GetmenuFlag() == true) {
			dungeon->SetTouch(false);
		}
		// そのままなら
		else {
			if (KeyData::Get(KEY_INPUT_Z) == 1) {
				if (dungeon->GetTreasure(dungeon->GetNum()) == false) {
					if (player->BuyItem(5) == true) {
						dungeon->SetOpen(true);
						player->SetTreasure(dungeon->GetNum(), true);
					}
					else {
						dungeon->SetOpen(false);
					}
				}
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
	// セーフエリアの処理
	safeArea->UpDate(player->GetX(), player->GetY());

	// プレイヤーのお金の動きを追跡して反映
	player->SetMoney(safeArea->GetMoney());

	// プレイヤーが動いたかどうかを判断するために直前の座標を保存
	playerX = player->GetX();
	playerY = player->GetY();
	
	// 特定条件下でプレイヤー本体のプロセスを停止
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
				if (player->BuyItem(safeArea->GetID()))
				{
					// 購入成功
				}
				else
				{
					// 購入失敗
					safeArea->Refund();
				}
				safeArea->SetBuy(false);
			}
			// 売ったとき
			if (safeArea->GetSell() == true) {
				player->SellItem(safeArea->GetItemPosition());
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