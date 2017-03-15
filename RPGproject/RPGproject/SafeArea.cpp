#include "Manager.h"
#include "SafeArea.h"

SafeArea::SafeArea() {
	// 動作関係
	endFlag = false;
	nextScene = eScene::S_End;

	// 画像関係
	Gr_Wall = LoadGraph("Dungeon\\wall.png");
	Gr_Back = LoadGraph("img\\safearea_background.png");
	Gr_Exit = LoadGraph("img\\exit.png");
	Gr_Murabito = LoadGraph("img\\murabito.png");
	Gr_Shop = LoadGraph("img\\shop.png");
	Gr_Yado = LoadGraph("img\\yado.png");
	graph = 0;

	// 演出関係
	step = eStep::Start;
	startCount = 30;
	endCount = 30;
	count = 0;
	lines = "";

	// マップデータ読み込み
	MapData();

	// カメラ
	x = 0;
	y = 0;

	// 各種フラグ
	fieldflag = false;
	peopleflag = false;
	itemflag = false;
	healflag = false;
	healY = false;
	talkflag = false;
	shopflag = false;
	buyflag = false;
	sellflag = false;
	innflag = false;

	// カウント系
	healcount = 0;
	shopcount = 0;

	// UI管理関係
	shopmenu = START;
	shopmY = 0;

	// 擬似プレイヤー要素
	money = 0;
	ID = 0;
	for (int i = 0; i < 9; i++) {
		item[i] = 0;
	}

	// 参照用アイテムと常に変動する値段
	price = 0;
	itemPosition = 0;
	itemMax = 9;

	// UI
	playerUI_x = 420;
	playerUI_y = 420;
	anotherUI_x = 55;
	anotherUI_y = 50;
	conUI_x = 140;
	conUI_y = 140;
}
SafeArea::~SafeArea() {
	// 画像削除
	DeleteGraph(Gr_Wall);
	DeleteGraph(Gr_Back);
	DeleteGraph(Gr_Exit);
	DeleteGraph(Gr_Murabito);
	DeleteGraph(Gr_Shop);
	DeleteGraph(Gr_Yado);
}

void SafeArea::UpDate() {
	switch (this->step) {
	case eStep::Start:	// 開始画面
		this->UpDate_Start();
		break;
	case eStep::Main:	// メイン処理画面
		this->UpDate_Main();
		break;
	case eStep::End:	// 終了画面
		this->UpDate_End();
		break;
	default:
		this->endFlag = true;	// エラー終了
		break;
	}
}

void SafeArea::UpDate(int playerX, int playerY) {
	switch (this->step) {
	case eStep::Start:	// 開始画面
		this->UpDate_Start();
		break;
	case eStep::Main:	// メイン処理画面
		this->UpDate_Main();
		break;
	case eStep::End:	// 終了画面
		this->UpDate_End();
		break;
	default:
		this->endFlag = true;	// エラー終了
		break;
	}
}

void SafeArea::UpDate_Start() {
	// カウントアップ
	count++;

	// startCountだけ演出
	if (count < startCount) return;
	// カウントリセットとステップ進行
	count = 0;
	step = eStep::Main;
}

void SafeArea::UpDate_Main() {
	// 特定の場所行ったらフィールド画面へ
	if (fieldflag == true) {
		nextScene = eScene::S_Field;
		step = eStep::End;
	}

	// 宿屋に話しかけられる状態であれば
	if (innflag)
	{
		HealProcess();		// 回復ポイント(宿屋)の処理
	}
	// 表示時間のカウントダウンカウントダウン
	if (healcount > 0) {
		healcount--;
	}

	// 村人に話しかけられる状態であれば
	if (peopleflag)
	{
		PeopleProcess();	// 村人(会話要素)
	}

	if (itemflag)
	{
		ShopProcess();		// 店
	}
	// ショップの売買後の会話表示のカウントダウン
	if (shopcount >= 0) {
		shopcount--;
	}
}

void SafeArea::UpDate_End() {
	// カウントアップ
	count++;

	// endCountだけ演出
	if (count < endCount) return;
	// カウントリセットとシーン終了
	count = 0;
	endFlag = true;
}

void SafeArea::Draw() {
	switch (this->step) {
	case eStep::Start:	// 開始画面
		this->Draw_Start();
		break;
	case eStep::Main:	// メイン処理画面
		this->Draw_Main();
		break;
	case eStep::End:	// 終了画面
		this->Draw_End();
		break;
	default:
		this->endFlag = true;	// エラー終了
		break;
	}
}

void SafeArea::Draw_Start() {
	DrawStringToHandle(0, 0, "拠点画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "開始画面 %d / %d", count, startCount);
}

void SafeArea::Draw_Main() {
	// 背景
	DrawGraph(0, 0, Gr_Back, false);

	// マップチップ描写
	for (int i = 0, n = (int)map.size(); i < n; i++) {
		for (int j = 0, m = (int)map[i].size(); j < m; j++) {
			//stoi で文字を数値に変換
			switch ((int)(stoi(map[i][j]) * 0.1)) {
			case 0:	//00
				graph = 0;
				break;

			case 1:	//壁
				switch (stoi(map[i][j]) % 10) {
				case 0:	//10
					graph = Gr_Wall;
					break;

				case 1:
					graph = Gr_Exit;	// 出口
					break;

				case 2:
					graph = Gr_Murabito;	// 案内人
					break;

				case 3:
					graph = Gr_Shop;	// 道具屋
					break;

				case 4:
					graph = Gr_Yado;	// 癒し
					break;

				default:
					// エラー
					break;
				}
				break;

			default:
				// エラー
				break;
			}

			// 描写
			DrawGraph(j * 32, i * 32, graph, true);
		}
	}
}

void SafeArea::Draw_End() {
	DrawStringToHandle(0, 0, "拠点画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面 %d / %d", count, endCount);
}

void SafeArea::Draw_UI() {
	// 回復店主
	if (innflag == true && talkflag == true) {
		// コマンドボックス
		Textbox::Draw(anotherUI_x - 8, anotherUI_y - 8, 180, (cursor * 3) + 10, "泊まりますか？");
		
		// 選択肢
		Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 1), "休み　　100円");
		Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 2), "やめる");

		// カーソル
		DrawString(anotherUI_x + 5, anotherUI_y + (healY + 1) * cursor, "▼", RED);
	}
	// 回復表示
	if (healcount > 0) {
		if (money > price) {
			lines = "回復しました。";
		}
		else {
			lines = "出直して";
		}
	}

	// 村人のセリフ
	if (peopleflag == true && talkflag == true) {
		Textbox::Draw(conUI_x, conUI_y, 210, 35, "ここはミントスの町です。");
	}

	//買い物関連----------------------------------------------------
	if (itemflag == true && shopflag == true) {
		// 最初のメニュー
		if (shopmenu == START || shopmenu == BUY || shopmenu == SELL) {
			// コマンドボックス
			Textbox::Draw(anotherUI_x - 16, anotherUI_y - 16, 140, (cursor * 5) - 10, "いらっしゃーい");
			
			// 選択肢
			Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 1) - 8, "買う");
			Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 2) - 8, "売る");
			Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 3) - 8, "やめる");

			// カーソル
			if (shopmenu == START) {
				DrawString(anotherUI_x + 5, anotherUI_y + ((shopmY + 1) * cursor), "▼", RED);
			}
		}
		// 買うときのメニュー
		if (shopmenu == BUY) {
			// コマンドボックス
			Textbox::Draw(anotherUI_x + 34, anotherUI_y + 34, 320, (cursor * 5) + 40, "何を買う？");
			
			// もの
			for (int i = 2; i <= 5; i++) {
				Textbox::Draw(anotherUI_x + 72, anotherUI_y + (cursor * (i - 1)) + 42, Item::SearchName(i));
				DrawFormatString(anotherUI_x + 300, anotherUI_y + (cursor * (i - 1)) + 50, WHITE, "%d", Item::SearchPrice(i));
			}

			// 戻る
			Textbox::Draw(anotherUI_x + 72, anotherUI_y + (cursor * 5) + 42, "戻る");

			// カーソル
			DrawString(anotherUI_x + 55, anotherUI_y + ((shopmY + 1) * cursor) + 50, "▼", RED);
		}
		// 売るときのメニュー
		if (shopmenu == SELL) {
			// ボックス
			Textbox::Draw(anotherUI_x + 34, anotherUI_y + 34, 310, (cursor * 10) + 40, "何を売る？");
			
			// 所持アイテム一覧
			for (int i = 0; i < itemMax; i++) {
				Textbox::Draw(anotherUI_x + 72, anotherUI_y + (cursor * (i + 1)) + 42, Item::SearchName(item[i]));
				DrawFormatString(anotherUI_x + 300, anotherUI_y + (cursor * (i + 1)) + 50, WHITE, "%d", Item::SearchPrice(item[i]));
			}
			
			// 戻る
			Textbox::Draw(anotherUI_x + 72, anotherUI_y + (cursor * 10) + 42, "戻る");
			
			// カーソル
			DrawString(anotherUI_x + 55, anotherUI_y + ((shopmY + 1) * cursor) + 50, "▼", RED);
		}
	}
	// 店主のセリフ
	// 買ったとき
	if (shopmenu == BUY && shopcount > 0) {
		if (money > price) {
			lines = "まいど～";
		}
		else {
			lines = "出直して";
		}
	}
	// 売ったとき
	if (shopmenu == SELL && shopcount > 0) {
		// 無以外を売ったとき
		// shopmY=9:配列外参照
		if (shopmY != 9)
		{
			if (price != 0) {
				lines = "まいど～";
			}
			// 無を売るとき
			else {
				lines = "はい";
			}
		}
	}
	//--------------------------------------------------------------

	// 話してるとき共通の処理
	if ((talkflag || shopflag) && !peopleflag)
	{
		// 所持金
		Textbox::Draw(playerUI_x, playerUI_y, 135, 35, "");
		DrawFormatString(playerUI_x + 8, playerUI_y + 8, WHITE, "所持金：%d円", money);
	}
	// 話してる相手のセリフ
	if (((shopmenu == BUY || shopmenu == SELL) && shopcount > 0) || healcount > 0) {
		Textbox::Draw(conUI_x, conUI_y, 125, 35, lines);
	}
}

void SafeArea::MapData() {
	read_file.open("SafeAreaMap.txt");
	read_count = 0;
	while (getline(read_file, read_line)) {	// 一行ずつ読み込み
		map.resize(read_count + 1);
		for (int i = 0, n = (int)read_line.length(); i < n; i += 2) {
			map[read_count].push_back(read_line.substr(i, 2));
		}
		read_count++;	// 次の行に
	}
	read_file.close();
}

void SafeArea::HealProcess() {
	// 宿の値段
	price = 100;

	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// 既に話している場合
		if (talkflag == true) {
			// 回復頼んだら
			if (healY == 0) {
				// お金あれば
				if (money >= price) {
					money -= price;
					healflag = true;
				}
				// お金なければ
				else {
					// 泊まれない
				}

				// セリフ表示と選択アイコン座標初期化
				healcount = heal;
				healY = 0;
			}
			// 回復を断る
			else {
				healY = 0;
			}

			// 会話終了
			talkflag = false;
		}
		// 話しかけた場合
		else
		{
			// 泊まるかの選択に映る
			talkflag = true;
		}
	}

	// 選択肢
	// 話しかけてい間だけ
	if (talkflag == true) {
		if (KeyData::Get(KEY_INPUT_UP) == 1) {
			healY = 0;
		}
		if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
			healY = 1;
		}
	}
}

void SafeArea::PeopleProcess() {
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// セリフが出ていたら
		if (talkflag == false) {
			talkflag = true;
		}
		// セリフが出ていなかったら
		else {
			talkflag = false;
		}
	}
}

void SafeArea::ShopProcess() {
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// 既に話しかけている場合
		if (shopflag == true) {
			switch (shopmenu)
			{
			case START:
				// 購入画面へ
				if (shopmY == 0) {
					shopmenu = BUY;
				}
				// 売却画面へ
				else if (shopmY == 1) {
					shopmenu = SELL;
				}
				// やめるを押したとき
				else {
					// 買い物終了
					shopflag = false;
				}

				// カーソル初期化
				shopmY = 0;
				break;

			case BUY:
				switch (shopmY)
				{
				case 0:		// やく(にたちそうな)くさ
					price = Item::SearchPrice(2);
					ID = 2;
					break;
				case 1:		// 清らかな水
					price = Item::SearchPrice(3);
					ID = 3;
					break;
				case 2:		// けむりダマ
					price = Item::SearchPrice(4);
					ID = 4;
					break;
				case 3:		// 世界樹のハ
					price = Item::SearchPrice(5);
					ID = 5;
					break;

				case 4:		// 戻るボタン
					price = 0;
					ID = 0;

					// 初期化
					shopmenu = START;
					shopmY = 0;
					break;

				default:	// エラー
					price = 0;
					ID = 0;
					break;
				}

				// お金が足りていれば
				if (money >= price) {
					// Managerに処理させるフラグを立てる
					buyflag = true;
					// 所持金をマイナスする
					money -= price;
				}
				else {
					// 所持金不足
				}

				// セリフ表示時間更新
				shopcount = shop;
				break;

			case SELL:
				// shopmY=9:配列外参照
				if (shopmY != 9)
				{
					// 値段とそのアイテムの保管場所を保存
					price = Item::SearchPrice(item[shopmY]);
					itemPosition = shopmY;

					// Managerに処理させるフラグを立てる
					sellflag = true;

					// アイテムを消す
					item[shopmY] = 0;

					// 所持金をプラスする
					money += price;
				}
				// 戻る選択時
				else
				{
					// 値段とそのアイテムの保管場所を保存
					price = 0;
					itemPosition = 0;

					// 初期化
					shopmenu = START;
					shopmY = 0;
				}

				// セリフ表示時間更新
				shopcount = shop;
				break;

			case END:
				break;

			default:
				// エラー
				break;
			}
		}
		// まだ話しかけていないとき
		else {
			shopflag = true;
		}
	}

	// ショップ画面でのカーソル移動
	if (shopflag == true) {
		// 上を押した
		if (KeyData::Get(KEY_INPUT_UP) == 1 && shopmY > 0) {
			shopmY--;
		}
		// 下を押した
		if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
			switch (shopmenu)
			{
			case START:
				if (shopmY < 2) {
					shopmY++;
				}
				break;

			case BUY:
				if (shopmY < 4) {
					shopmY++;
				}
				break;

			case SELL:
				if (shopmY < 9) {
					shopmY++;
				}
				break;

			case END:
				break;

			default:
				// エラー
				break;
			}
		}
	}
}

void SafeArea::Refund()
{
	money += Item::SearchPrice(ID);
}

int SafeArea::GetMapData(int x, int y) {
	return stoi(map[(int)(y / 32)][(int)(x / 32)]);
}

int SafeArea::GetMapWidth() {
	return (int)map[0].size();
}
int SafeArea::GetMapHeight() {
	return (int)map.size();
}

void SafeArea::SetX(int x) {
	this->x = x;
}

int SafeArea::GetX() {
	return this->x;
}

void SafeArea::SetY(int y) {
	this->y = y;
}

int SafeArea::GetY() {
	return this->y;
}

void SafeArea::SetField(bool flag) {
	fieldflag = flag;
}

bool SafeArea::GetField() {
	return fieldflag;
}

void SafeArea::SetPeople(bool flag) {
	peopleflag = flag;
}

bool SafeArea::GetPeople() {
	return peopleflag;
}

void SafeArea::SetItem(bool flag) {
	itemflag = flag;
}

bool SafeArea::GetItem() {
	return itemflag;
}

void SafeArea::SetShop(bool flag) {
	shopflag = flag;
}

bool SafeArea::GetShop(){
	return shopflag;
}

void SafeArea::SetHeal(bool flag) {
	healflag = flag;
}

bool SafeArea::GetHeal() {
	return healflag;
}

void SafeArea::SetTalk(bool flag) {
	talkflag = flag;
}

bool SafeArea::GetTalk() {
	return talkflag;
}

void SafeArea::SetBuy(bool flag) {
	buyflag = flag;
}

bool SafeArea::GetBuy() {
	return buyflag;
}

void SafeArea::SetSell(bool flag) {
	sellflag = flag;
}

bool SafeArea::GetSell() {
	return sellflag;
}

void SafeArea::SetInn(bool flag) {
	innflag = flag;
}

bool SafeArea::GetInn() {
	return innflag;
}

void SafeArea::SetID(int ID) {
	this->ID = ID;
}

int SafeArea::GetID() {
	return ID;
}

void SafeArea::SetItemPosition(int itemPosition) {
	this->itemPosition = itemPosition;
}

int SafeArea::GetItemPosition() {
	return itemPosition;
}

void SafeArea::SetnumID(int num, int ID) {
	item[num] = ID;
}

void SafeArea::SetMoney(int money) {
	this->money = money;
}

int SafeArea::GetMoney() {
	return money;
}

eStep SafeArea::GetStep() {
	return step;
}