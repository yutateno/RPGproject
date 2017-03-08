#include "Manager.h"

Manager::Manager() {
	// 移動全般
	playerX = 0;		// 絶対座標
	playerY = 0;		// 絶対座標
	probability = 200;	// 敵とのエンカウント率

	// 戦闘関連
	turn = true;		// true : プレイヤーのターン
	logCount = 160;		// 演出時間
	count = 0;			// 演出用の(フレーム)時間カウント
	preHP = 0;			// 直前のＨＰ
	lose = false;		// 戦闘に敗北したか。false:してない
	statusX = 8;		// コマンドが乗ってる板の座標
	statusY = 8;		// コマンドが乗ってる板の座標
	logX = 8;			// ログが乗ってる板の座標
	logY = 320;			// ログが乗ってる板の座標

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

		// 演出用の変数初期化
		count = 0;

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
	// 戦闘で敗北したかどうかで次のシーンを変更
	// 敗北した場合
	if (lose)
	{
		NowScene = eScene::S_GameOver;
	}
	// 勝利した場合
	else
	{
		// バトルから次のシーンを取得
		NowScene = battle->GetNextScene();
	}

	// 次のシーンによって処理を変更
	switch (this->NowScene) {
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

		// 演出用の変数の初期化
		count = 0;

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

		// 演出用変数を初期化
		count = 0;

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

	// 敗北フラグを折る
	lose = false;

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
				// バトルがメインステップの時のみログを表示
				if (battle->GetStep() == eStep::Main)
				{
					// １ページ目
					if (count <= 160)
					{
						// 一段階目のログ
						DrawFormatString(logX + 32, logY + 32, BLACK, " %s をsatsugaiした", enemy->GetName().c_str());
						// 二段階目
						if (count > 80)
						{
							DrawFormatString(logX + 32, logY + 64, BLACK, " %d の経験値を獲得！", enemy->GetEXP());
						}
					}
					// ２ページ目
					else{
						// 一段階目のログ
						DrawFormatString(logX + 32, logY + 32, BLACK, "レベルアップ！", enemy->GetEXP());
						// 二段階目
						if (count > 240)
						{
							DrawFormatString(logX + 32, logY + 64, BLACK, " %s は LV %d になった！", player->GetName().c_str(), player->GetLV());
						}
					}
				}
			}
			// 敗北時
			else if (player->GetHP() <= 0)
			{
				// バトルがメインステップの時のみログを表示
				if (battle->GetStep() == eStep::Main)
				{
					DrawFormatString(logX + 32, logY + 32, BLACK, "敗北");
				}
			}
			else
			{
				if (turn)
				{
					// 一段階目のログ
					DrawFormatString(logX + 32, logY + 32, BLACK, " %s の攻撃！", player->GetName().c_str());
					// 二段階目
					if (count > 80)
					{
						DrawFormatString(logX + 32, logY + 64, BLACK, " %s に %d ダメージ！", enemy->GetName().c_str(), preHP - enemy->GetHP());
					}
				}
				else
				{
					// 一段階目のログ
					DrawFormatString(logX + 32, logY + 32, BLACK, " %s の攻撃！", enemy->GetName().c_str());
					// 二段階目
					if (count > 80)
					{
						DrawFormatString(logX + 32, logY + 64, BLACK, " %s に %d ダメージ！", player->GetName().c_str(), preHP - player->GetHP());
					}
				}
			}
		}

		// メイン画面のみの描写
		if (battle->GetStep() == eStep::Main)
		{
			// 生きていれば
			if (enemy->GetHP() > 0)
			{
				if (turn)
				{
					// ダメージ食らったとき
					if (count < 80 || count % 5 == 0)
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
			if (turn)
			{
				DrawFormatString(statusX + 32, statusY + 32, BLACK, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());
			}
			else
			{
				// ダメージ食らったとき
				if (count > 80)
				{
					DrawFormatString(statusX + 32 + GetRand(8), statusY + 32 + GetRand(8), RED, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());
				}
				// 食らってないとき
				else
				{
					DrawFormatString(statusX + 32, statusY + 32, BLACK, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());
				}
			}

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
		if (count < logCount)			// ログをXフレーム表示する
		{
			// カウントアップ
			count++;
		}
		else
		{
			// 経験値の処理
			player->SetEXP(player->GetEXP() + enemy->GetEXP());

			// レベルアップの処理
			if (player->GetLV() * 20 < player->GetEXP())
			{
				// 表示時間延長
				logCount = 320;

				player->SetEXP(player->GetEXP() - (player->GetLV() * 20));	// 経験値を0にする
				player->SetLV(player->GetLV() + 1);							// レベルを１上げる
				player->SetMaxHP(player->GetMaxHP() + player->GetLV());		// HP上昇
				player->SetMaxMP(player->GetMaxMP() + player->GetLV());		// MP上昇
				return;
			}

			// カウントリセット
			count = 0;
			// 表示時間リセット
			logCount = 160;
			// バトルのステップ進行
			battle->SetStep(eStep::End);
		}
	}
	// 戦闘敗北
	else if (player->GetHP() <= 0)
	{
		if (count < logCount)			// ログをXフレーム表示する
		{
			// カウントアップ
			count++;
		}
		else
		{
			// カウントリセット
			count = 0;
			// 敗北フラグを立てる
			lose = true;
			// バトルのステップ進行
			battle->SetStep(eStep::End);
		}
	}
	else
	{
		// 自分のターン
		if (turn)
		{
			// battleからダメージを与える指示を受けたら
			if (battle->GetDamageFlag())
			{
				// 演出中ではないとき
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
						// MPが足りない場合
						else
						{
							battle->SetDamageFlag(false);			// フラグを折る
							battle->SetCommand(NEUTRAL);			// バトルのコマンドを元に戻す
							count = 0;								// カウントを戻す
							return;
						}
						break;

					case RUN_AWAY:
						break;

					default:
						break;
					}
				}

				// 演出中
				if (count < logCount)			// ログをXフレーム表示する
				{
					// カウントアップ
					count++;

					// 演出と同期してダメージ
					if (count == 80)
					{
						//ダメージ決定
						player->SetATK(battle->GetDamageWidth());			// 選択した行動を反映する
						enemy->SetHP(enemy->GetHP() - player->GetATK());	// ダメージ
					}
				}
				else
				{
					// カウントリセット
					count = 0;

					battle->SetDamageFlag(false);			// フラグを折る
					battle->SetCommand(NEUTRAL);			// バトルのコマンドを戻す
					count = 0;								// カウントを戻す
					turn = false;							// あいてにターンを渡す
				}
			}
		}
		// 相手のターン
		else
		{
			// 演出中
			if (count < logCount)			// ログをXフレーム表示する
			{
				// カウントアップ
				count++;

				// 演出と同期してダメージ
				if (count == 80)
				{
					enemy->AttackProcess();
					player->SetHP(player->GetHP() - enemy->GetATK());		// 攻撃力分だけダメージ
				}
			}
			else
			{
				// カウントリセット
				count = 0;

				count = 0;			// カウントを戻す
				turn = true;		// プレイヤーにターンを渡す
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

	player->SetMoney(safeArea->GetMoney());

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