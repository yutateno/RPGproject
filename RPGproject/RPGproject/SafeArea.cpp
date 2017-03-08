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
	startCount = 50;
	endCount = 50;
	count = 0;
	lines = "";

	// マップデータ読み込み
	MapData();

	// これなに？
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
	itemm = new Item();
	price = 0;

	// 初期化し忘れよくない
	itemPosition = 0;
	innflag = false;
}
SafeArea::~SafeArea() {
	// 画像削除
	DeleteGraph(Gr_Wall);
	DeleteGraph(Gr_Back);
	DeleteGraph(Gr_Exit);
	DeleteGraph(Gr_Murabito);
	DeleteGraph(Gr_Shop);
	DeleteGraph(Gr_Yado);

	// 参照用アイテム削除
	delete 	itemm;
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
		this->Draw_Main(x, y);
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

void SafeArea::Draw_Main(int x, int y) {
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
			DrawGraph(j * 32 - x, i * 32 - y, graph, true);
		}
	}

	// 回復店主
	if (innflag == true && talkflag == true) {
		DrawFormatString(320, 150, BLACK, "所持金：%d円", money);
		DrawFormatString(320, 118, BLACK, "100円");
		DrawFormatString(0, cursor * 0, BLACK, "泊まりますか？");
		DrawFormatString(35, cursor * 1, BLACK, "休みます");
		DrawFormatString(35, cursor * 2, BLACK, "やめときます");
		DrawBox(0, (healY + 1) * cursor, 32, 32 + ((healY + 1) * cursor), BLUE, true);
	}
	// 回復表示
	if (healcount > 0) {
		if (money > price) {
			DrawFormatString(320, 240, BLACK, "回復しました。");
		}
		else {
			DrawFormatString(320, 240, BLACK, "出直して");
		}
	}

	// 村人のセリフ
	if (peopleflag == true) {
		lines = "ここは町です。";
	}

	//買い物関連----------------------------------------------------
	if (itemflag == true && shopflag == true) {
		// 最初のメニュー
		if (shopmenu == START) {
			// 選択肢
			DrawFormatString(35, cursor * 0, BLACK, "買う");
			DrawFormatString(35, cursor * 1, BLACK, "売る");
			DrawFormatString(35, cursor * 2, BLACK, "やめる");

			// カーソル
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);

			// セリフ
			lines = "いらっしゃーい";
		}
		// 買うときのメニュー
		else if(shopmenu == BUY) {
			// やく(にたちそうな)くさ
			DrawFormatString(35, cursor * 0, BLACK, " %s ", itemm->SearchName(2).c_str());
			DrawFormatString(250, cursor * 0, BLACK, " %d ", itemm->SearchPrice(2));
			// 清らかな水
			DrawFormatString(35, cursor * 1, BLACK, " %s ", itemm->SearchName(3).c_str());
			DrawFormatString(250, cursor * 1, BLACK, " %d ", itemm->SearchPrice(3));
			// けむりダマ
			DrawFormatString(35, cursor * 2, BLACK, " %s ", itemm->SearchName(4).c_str());
			DrawFormatString(250, cursor * 2, BLACK, " %d ", itemm->SearchPrice(4));
			// 世界樹のハ
			DrawFormatString(35, cursor * 3, BLACK, " %s ", itemm->SearchName(5).c_str());
			DrawFormatString(250, cursor * 3, BLACK, " %d ", itemm->SearchPrice(5));
			// 戻る
			DrawFormatString(35, cursor * 4, BLACK, "戻る");

			// カーソル
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);

			// セリフ
			lines = "何を買う？";
		}
		// 売るときのメニュー
		else if (shopmenu == SELL) {
			// 所持アイテム一覧
			for (int i = 0; i < 9; i++)
			{
				DrawFormatString(35, cursor * i, BLACK, " %s ", itemm->SearchName(item[i]).c_str());
				DrawFormatString(250, cursor * i, BLACK, " %d ", itemm->SearchPrice(item[i]));
			}
			// 戻る
			DrawFormatString(35, cursor * 9, BLACK, "戻る");

			// カーソル
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);

			// セリフ
			lines = "何を売る？";
		}
	}
	// 店主のセリフ
	// 買ったとき
	if (shopmenu == BUY && shopcount >= 0) {
		if (money > price) {
			lines = "まいど～";
		}
		else {
			lines = "出直して";
		}
	}
	// 売ったとき
	if (shopmenu == SELL && shopcount == (shop - 1)) {
		// 無以外を売ったとき
		// shopmY=9:配列外参照
		if (shopmY != 9)
		{
			if (item[shopmY] != 0) {
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
	if (talkflag || shopflag)
	{
		// 所持金
		DrawFormatString(320, 150, BLACK, "所持金：%d円", money);

		// 話してる相手のセリフ
		DrawFormatString(320, 240, BLACK, " %s ", lines.c_str(), money);
	}

	// debug-------------------------------------------------
	DrawFormatString(600, 450, BLACK, " %d ", innflag);
	// --------------------------------------------------------
}

void SafeArea::Draw_End() {
	DrawStringToHandle(0, 0, "拠点画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面 %d / %d", count, endCount);
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
					price = itemm->SearchPrice(2);
					ID = 2;
					break;
				case 1:		// 清らかな水
					price = itemm->SearchPrice(3);
					ID = 3;
					break;
				case 2:		// けむりダマ
					price = itemm->SearchPrice(4);
					ID = 4;
					break;
				case 3:		// 世界樹のハ
					price = itemm->SearchPrice(5);
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
					price = itemm->SearchPrice(item[shopmY]);
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
	money += itemm->SearchPrice(ID);
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