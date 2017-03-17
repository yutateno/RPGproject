#include "Manager.h"

Manager::Manager() {
	// 移動全般
	playerX = 0;		// 絶対座標
	playerY = 0;		// 絶対座標
	playerDamageFlag = false;	// ダメージを受けているかどうか
	enemyDamageFlag = false;	// ダメージを受けているかどうか
	probability = 200;	// エンカウントする確率 : 1/probability

	// 戦闘関連
	turn = true;			// true : プレイヤーのターン
	statusX = 16;			// コマンドが乗ってる板の座標
	statusY = 16;			// コマンドが乗ってる板の座標
	preHP = 0;				// 直前のHP
	damage = 0;				// 表示用

	// ログ関係
	logCount = 0;			//(フレーム)カウント
	logTime = 0;			// 表示時間			
	logX = 8;				// ログが乗ってる板の座標
	logY = 320;				// ログが乗ってる板の座標

	// ゲーム進行関係
	player = new Player();			// プレイヤー本体
	endFlag = false;				// ゲーム終了するフラグ
	NowScene = eScene::S_Title;		// 最初の画面を指定
	title = new Title();			// 最初の画面を生成

	// テキストボックス
	// ステータス
	statusWidth = 112;		// ステータスの幅
	statusHeight = 96;		// ステータスの高さ
	statusX = 0;			// ステータスの座標
	statusY = 0;			// ステータスの座標
	// ログ
	logX = 112;				// 座標
	logWidth = 640 - logX;	// 幅
	logHeight = 96;			// 高さ
	logY = 480 - logHeight;	// 座標
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
		player->SetX(64);
		player->SetY(64);
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
		safeArea->SetMoney(player->GetMoney());
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

	logCount = 0;
	logTime = 0;
	turn = true;

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
		player->SetX(8 * 32);
		player->SetY(5 * 32);
		break;

	case eScene::S_Battle:// 戦闘画面
		battle = new Battle();

		// 敵生成
		enemy = new Enemy(2);

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
		player->SetX(7 * 32);
		player->SetY(9 * 32);
		break;

	case eScene::S_Battle:// 戦闘画面
		battle = new Battle();

		// 敵生成
		// ボス
		if (dungeon->GetBattle() == true) {
			enemy = new Enemy(3);
		}
		else {
			enemy = new Enemy((int)GetRand(1));
		}

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
		// 背景とマップチップ
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
			safeArea->Draw_UI();
		}
		
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
	// ログ表示中かどうか
	// 表示中
	if (field->GetTreasureFlag())
	{
		if (KeyData::Get(KEY_INPUT_Z) == 1)
		{
			field->SetTreasureFlag(false);
		}
	}
	// 表示してないとき
	else
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

		// --------------------------------------------------
		// マップとの当たり判定------------------------------
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
		// --------------------------------------------------


		// --------------------------------------------------
		// 宝箱との当たり判定
		for (int i = 0;i < 2;i++)
		{
			for (int j = 0;j < 2;j++)
			{
				for (int n = 0, m = field->GetTreasureNum();n < m;n++)
				{
					// 位置がかぶっていれば
					if (field->GetTreasureX(n) < (player->GetSpeed() + 1) + player->GetX() + (i * (32 - ((player->GetSpeed() + 1) * 2)))
						&& (player->GetSpeed() + 1) + player->GetX() + (i * (32 - ((player->GetSpeed() + 1) * 2))) < field->GetTreasureX(n) + 32
						&& field->GetTreasureY(n) < (player->GetSpeed() + 1) + player->GetY() + (j * (32 - ((player->GetSpeed() + 1) * 2)))
						&& (player->GetSpeed() + 1) + player->GetY() + (j * (32 - ((player->GetSpeed() + 1) * 2))) < field->GetTreasureY(n) + 32)
					{
						// 通り抜け禁止
						player->MoveReset();
					}
					// 位置がかぶっていれば
					if (field->GetTreasureX(n) < player->GetX() + (i * 32)
						&& player->GetX() + (i * 32) < field->GetTreasureX(n) + 32
						&& field->GetTreasureY(n) < player->GetY() + (j * 32)
						&& player->GetY() + (j * 32) < field->GetTreasureY(n) + 32)
					{
						// アイテムに空きがあれば
						if (KeyData::Get(KEY_INPUT_Z) == 1 && player->BuyItem(0))
						{
							player->BuyItem(field->OpenTreasure(n));
						}
					}
				}
			}
		}
		// --------------------------------------------------
		// --------------------------------------------------
	}
}

void Manager::BattleProcess()
{
	switch (battle->GetStep())
	{
	case eStep::Start:
		// コマンド等の処理
		battle->UpDate();
		break;

	case eStep::Main:
		// 戦闘勝利
		if (enemy->GetHP() <= 0)
		{
			if (logCount < logTime)
			{
				// カウント
				logCount++;
			}
			else
			{
				// 初期化
				logCount = 0;
				logTime = 0;
				// フラグを折る
				battle->SetDamageFlag(false);

				// 戦闘報酬
				player->SetEXP(player->GetEXP() + enemy->GetEXP());				// 経験値
				player->SetMoney(player->GetMoney() + enemy->GetMoney());		// お金

				// 表示時間
				logTime = 180;

				// レベルアップ
				if (player->GetEXP() > player->GetLV() * 20)
				{
					logTime += 180;
					// 繰越分を与える
					player->SetEXP(player->GetEXP() - player->GetLV() * 20);
					// レベルを上げる
					player->SetLV(player->GetLV() + 1);
					// ステータス上昇
					player->SetMaxHP(player->GetMaxHP() + player->GetLV());
					player->SetMaxMP(player->GetMaxMP() + player->GetLV());
					player->SetPower(player->GetPower() + player->GetLV());
				}

				// バトルのステップ進行
				battle->SetStep(eStep::End);
			}
		}
		// 戦闘敗北
		else if (player->GetHP() <= 0)
		{
			// ログ出力
			if (logCount > 0)
			{
				if (logCount < logTime)
				{
					// カウント
					logCount++;
				}
				else
				{
					// 初期化
					logCount = 0;
					logTime = 0;
					// フラグを折る
					battle->SetDamageFlag(false);

					// ゲームオーバー画面へ
					battle->SetNextScene(eScene::S_GameOver);

					// バトルのステップ進行
					battle->SetStep(eStep::End);
				}
			}
		}
		else
		{
			// 自分のターン
			if (turn)
			{
				// ログ出力
				if (logCount > 0)
				{
					if (logCount < logTime)
					{
						// カウント
						logCount++;
					}
					else
					{
						// 初期化
						logCount = 0;
						logTime = 0;

						// フラグを折る
						battle->SetDamageFlag(false);
						// あいてにターンを渡す
						turn = false;
					}
				}
				else
				{
					// コマンド等の処理
					battle->UpDate();

					// battleからダメージを与える指示を受けたら
					if (battle->GetDamageFlag())
					{
						// カウントアップ
						logCount++;
						// 表示時間
						logTime = 120;
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

						//ダメージ決定
						player->SetATK(battle->GetDamageWidth());		// 選択した行動を反映する
						preHP = enemy->GetHP();							// 直前のHP
						damage = enemy->GetHP() - player->GetATK();		// ダメージを受けたあとのHP
						enemy->SetHP(damage);							// ダメージ
						enemyDamageFlag = true;							// ダメージフラグを立てて演出
					}
				}
			}
			// 相手のターン
			else
			{
				// ログ出力
				if (logCount > 0)
				{
					if (logCount < logTime)
					{
						// カウント
						logCount++;
					}
					else
					{
						// 初期化
						logCount = 0;
						logTime = 0;

						// バトルのコマンドを戻す
						battle->SetCommand(NEUTRAL);
						// プレイヤーにターンを渡す
						turn = true;
					}
				}
				else
				{
					// カウントアップ
					logCount++;
					// 表示時間
					logTime = 120;

					// 攻撃処理とダメージ
					enemy->AttackProcess();			// 攻撃の処理
					preHP = player->GetHP();		// 直前のHP
					damage = player->GetHP() - enemy->GetATK();	// ダメージ保存
					player->SetHP(damage);			// 攻撃力分だけダメージ
					playerDamageFlag = true;		// ダメージフラグを立てて演出
				}
			}
		}
		break;

	case eStep::End:
		// 演出中ではなければ
		if (logCount < logTime)
		{
			// カウントアップ
			logCount++;
		}
		else
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
	// ステップによって表示を分ける
	switch (battle->GetStep())
	{
	case eStep::Start:
		// 徐々に画面の表示する処理
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, battle->GetCount() * 3);
		// 背景
		battle->Draw();
		// 敵
		enemy->aaaDraw();
		// ブレンドモードの後処理
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// ステータス
		Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
			player->GetName() + "\n" +
			"HP:" + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()) + "\n" +
			"MP:" + std::to_string(player->GetMP()) + " / " + std::to_string(player->GetMaxMP()) + "\n" +
			"LV:" + std::to_string(player->GetLV()));
		// コマンド
		battle->Draw_Command();
		// ログ
		Textbox::Draw(logX, logY, logWidth, logHeight, "");

		// ログ
		Textbox::Draw(logX, logY, enemy->GetName() + " があらわれた！");
		break;

	case eStep::Main:
		// 背景
		battle->Draw();
		// ステータス
		Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
			player->GetName() + "\n" +
			"HP:" + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()) + "\n" +
			"MP:" + std::to_string(player->GetMP()) + " / " + std::to_string(player->GetMaxMP()) + "\n" +
			"LV:" + std::to_string(player->GetLV()));
		// コマンド
		battle->Draw_Command();
		// ログ
		Textbox::Draw(logX, logY, logWidth, logHeight, "");

		// ダメージ演出
		if (logCount > 60 && turn)
		{
			if (logCount % 5 == 0)
			{
				// 敵
				enemy->aaaDraw();
			}
		}
		else
		{
			// 敵
			enemy->aaaDraw();
		}

		// ダメージ表示
		if (battle->GetDamageFlag())
		{
			// ログ
			Textbox::Draw(logX, logY, player->GetName() + " の " + player->GetATKName() + " !");
			if (logCount > 60)
			{
				Textbox::Draw(logX, logY + 16, enemy->GetName() + " に " + to_string(preHP - damage) + " のダメージ！");
			}
		}
		if (!turn)
		{
			// ログ
			Textbox::Draw(logX, logY, enemy->GetName() + " の " + enemy->GetATKName() + " !");
			if (logCount > 60)
			{
				Textbox::Draw(logX, logY + 16, player->GetName() + " に" + to_string(preHP - damage) + " のダメージ！");
			}
		}
		break;

	case eStep::End:
		// 勝利
		if (enemy->GetHP() <= 0)
		{
			// 背景
			battle->Draw();

			// 徐々に画面の表示する処理
			if (logCount < 60)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - logCount * ((int)255 / 60));
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
			}
			// 敵
			enemy->aaaDraw();
			// ブレンドモードの後処理
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// ステータス
			Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
				player->GetName() + "\n" +
				"HP:" + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()) + "\n" +
				"MP:" + std::to_string(player->GetMP()) + " / " + std::to_string(player->GetMaxMP()) + "\n" +
				"LV:" + std::to_string(player->GetLV()));
			// コマンド
			battle->Draw_Command();
			// ログ
			Textbox::Draw(logX, logY, logWidth, logHeight, "");

			// ログ
			Textbox::Draw(logX, logY,enemy->GetName() + " を倒した！");
			if (logCount > 60)
			{
				Textbox::Draw(logX, logY + 16, to_string(enemy->GetEXP()) + " の経験値を獲得！");
			}
			if (logCount > 120)
			{
				Textbox::Draw(logX, logY + 32, to_string(enemy->GetMoney()) + " ゴールドを手に入れた！");
			}
			// レベルアップ
			if (logCount > 180)
			{
				Textbox::Draw(logX, logY, logWidth, logHeight, "レベルアップ！");
			}
			if (logCount > 240)
			{
				Textbox::Draw(logX, logY + 16, player->GetName() + " は LV" + to_string(player->GetLV()) + " になった！");
			}
			if (logCount > 300)
			{
				Textbox::Draw(logX, logY + 32, "ステータスが上がった！");
			}
		}
		// 敗北
		else if (player->GetHP() <= 0)
		{
			// 徐々に画面の表示する処理
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - battle->GetCount() * 3);
			// 背景
			battle->Draw();
			// 敵
			enemy->aaaDraw();
			// ブレンドモードの後処理
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// ステータス
			Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
				player->GetName() + "\n" +
				"HP:" + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()) + "\n" +
				"MP:" + std::to_string(player->GetMP()) + " / " + std::to_string(player->GetMaxMP()) + "\n" +
				"LV:" + std::to_string(player->GetLV()));
			// コマンド
			battle->Draw_Command();
			// ログ
			Textbox::Draw(logX, logY, logWidth, logHeight, "");

			// ログ
			Textbox::Draw(logX, logY, "あなたは死んでしまった・・・");
		}
		break;

	default:
		// エラー
		break;
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
			switch (dungeon->GetMapData(player->GetX() + (i * 31), player->GetY() + (j * 31)))
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

	// 宝箱との当たり判定
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0, m = dungeon->GetTreasureNum(); k < m; k++)
			{
				// ぶつかっていたら
				if (dungeon->GetTreasureX(k) < player->GetX() + (i * 32)			// 左
					&& player->GetX() + (i * 32) < dungeon->GetTreasureX(k) + 32	// 右
					&& dungeon->GetTreasureY(k) < player->GetY() + (j * 32)			// 上
					&& player->GetY() + (j * 32) < dungeon->GetTreasureY(k) + 32) {	// 下
					// 貫通させない
					player->MoveReset();
					// Zを押したら
					if (KeyData::Get(KEY_INPUT_Z) == 1) {
						// 宝箱に反応したら
						dungeon->SetTreasure(true);
						// 0が買えたらちゃんと買わせる
						if (player->BuyItem(0)) {
							player->BuyItem(dungeon->OpenTreasure(k));
							dungeon->SetOpen(true);
						}
						// お金が得れたら
						else if (dungeon->GetTreasureMoney() != 0) {
							dungeon->OpenTreasure(k);
							dungeon->SetOpen(true);
						}
						// 0が買えないうえにお金が得れなかったら
						else {
							dungeon->SetOpen(false);
						}
						// お金を入れる
						player->SetMoney(player->GetMoney() + dungeon->GetTreasureMoney());
					}
				}
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
	
	/*// 敵とのエンカウント
	if ((player->GetX() != playerX || player->GetY() != playerY) && player->GetmenuFlag() == false)
	{
		if (GetRand(probability) == 0)
		{
			dungeon->SetBattle(true);
		}
	}*/

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

	// ショップの売る画面でもソートさせたいので
	player->ItemSort();

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
				// 購入成功
				if (player->BuyItem(0)) {
					safeArea->SetSuccess(true);
					player->BuyItem(safeArea->GetID());
				}
				// 購入失敗
				else {
					safeArea->SetSuccess(false);
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