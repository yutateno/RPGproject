#include "Manager.h"
#include "SafeArea.h"

SafeArea::SafeArea() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;
	MapData();

	Gr_Wall = LoadGraph("Dungeon\\wall.png");
	Gr_Back = LoadGraph("img\\safearea_background.png");

	x = 0;
	y = 0;
	fieldflag = false;
	peopleflag = false;
	itemflag = false;
	healflag = false;
	healY = false;
	talkflag = false;
	shopflag = false;
	buyflag = false;
	sellflag = false;
	healcount = 0;
	shopcount = 0;
	shopmenu = 0;
	shopmY = 0;
	money = 0;
	premoney = 0;
	ID = 0;
	for (int i = 0; i < 9; i++) {
		item[i] = 0;
	}
	itemm = new Item();
}
SafeArea::~SafeArea() {
	DeleteGraph(Gr_Wall);
	DeleteGraph(Gr_Back);
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
	this->startCount++;

	if (this->startCount < 50) return;	// 50フレームで開始画面終了
	this->step = eStep::Main;
}

void SafeArea::UpDate_Main() {

	//// Xキーで戦闘画面に
	//if (KeyData::Get(KEY_INPUT_X) == 1) {
	//	this->nextScene = eScene::S_Battle;
	//	this->step = eStep::End;
	//}

	// 特定の場所行ったらフィールド画面へ
	if (fieldflag == true) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}

	HealProcess();
	PeopleProcess();
	ShopProcess();
}

void SafeArea::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50フレームで終了画面終了
	this->endFlag = true;
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
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "開始画面%d", this->startCount);
}

void SafeArea::Draw_Main(int x, int y) {

	DrawGraph(0, 0, Gr_Back, false);

	for (int i = 0, n = (int)map.size(); i < n; i++) {
		for (int j = 0, m = (int)map[i].size(); j < m; j++) {
			//stoi で文字を数値に変換
			switch ((int)(stoi(map[i][j]) * 0.1)) {
			case 0:	//00
				break;

			case 1:	//壁
				switch (stoi(map[i][j]) % 10) {
				case 0:	//10
					DrawGraph(j * 32 - x, i * 32 - y, Gr_Wall, false);
					break;

				case 1:
					DrawBox(j * 32 - x, i * 32 - y, j * 32 - x + 32, i * 32 - y + 32, BLUE, TRUE);	// 出口
					break;

				case 2:
					DrawBox(j * 32 - x, i * 32 - y, j * 32 - x + 32, i * 32 - y + 32, WHITE, TRUE);	// 案内人
					break;

				case 3:
					DrawBox(j * 32 - x, i * 32 - y, j * 32 - x + 32, i * 32 - y + 32, YELLOW, TRUE);	// 道具屋
					break;

				case 4:
					DrawBox(j * 32 - x, i * 32 - y, j * 32 - x + 32, i * 32 - y + 32, RED, TRUE);	// 癒し
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}

	// 回復店主
	if (innflag == true && talkflag == true) {
		DrawFormatString(320, 150, BLACK, "所持金：%d円", premoney);
		DrawFormatString(320, 118, BLACK, "100円");
		DrawFormatString(0, cursor * 0, BLACK, "泊まりますか？");
		DrawFormatString(35, cursor * 1, BLACK, "休みます");
		DrawFormatString(35, cursor * 2, BLACK, "やめときます");
		DrawBox(0, (healY + 1) * cursor, 32, 32 + ((healY + 1) * cursor), BLUE, true);
	}
	// 回復表示
	if (healcount > 0) {
		if (premoney > money) {
			DrawFormatString(320, 240, BLACK, "回復しました。");
		}
		else {
			DrawFormatString(320, 240, BLACK, "出直して");
		}
	}

	// 村人のセリフ
	if (peopleflag == true && talkflag == true) {
		DrawFormatString(320, 240, BLACK, "ここは町です。");
	}

	//買い物関連----------------------------------------------------
	if (itemflag == true && shopflag == true) {
		// 所持金
		DrawFormatString(320, 150, BLACK, "所持金：%d円", premoney);
		// 最初のメニュー
		if (shopmenu == 0) {
			DrawFormatString(35, cursor * 0, BLACK, "買う");
			DrawFormatString(35, cursor * 1, BLACK, "売る");
			DrawFormatString(35, cursor * 2, BLACK, "やめる");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "いらっしゃーい");
		}
		// 買うときのメニュー
		else if(shopmenu == 1) {
			DrawFormatString(35, cursor * 0, BLACK, "やく(にたちそうな)くさ");
			DrawFormatString(35, cursor * 1, BLACK, "清らかな水");
			DrawFormatString(35, cursor * 2, BLACK, "けむりダマ");
			DrawFormatString(35, cursor * 3, BLACK, "世界樹のハ");
			DrawFormatString(35, cursor * 4, BLACK, "戻る");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "何を買う？");
			if (shopmY < 4) {
				DrawFormatString(320, 118, BLACK, "%d円", money);
			}
		}
		// 売るときのメニュー
		else {
			for (int i = 0; i < 9; i++)
			{
				DrawFormatString(35, cursor * i, BLACK, itemm->SearchName(item[i]).c_str());
			}
			DrawFormatString(35, cursor * 9, BLACK, "戻る");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "何を売る？");
			if (shopmY != 9) {
				DrawFormatString(320, 118, BLACK, "%d円", money);
			}
		}
	}
	// 店主のセリフ
	// 買ったとき
	if (shopmenu == 1 && shopcount >= 0) {
		if (premoney > money) {
			DrawFormatString(320, 208, BLACK, "まいど～");
		}
		else {
			DrawFormatString(320, 208, BLACK, "出直して");
		}
	}
	// 売ったとき
	if (shopmenu == 2 && shopcount >= 0) {
		// 無以外を売ったとき
		if (item[shopmY] != 0) {
			DrawFormatString(320, 208, BLACK, "まいど～");
		}
		// 無を売るとき
		else {
			DrawFormatString(320, 208, BLACK, "はい");
		}
	}
	//--------------------------------------------------------------
}

void SafeArea::Draw_End() {
	DrawStringToHandle(0, 0, "拠点画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面%d", this->endCount);
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
	// 宿の店主に触れたら
	if (innflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			// セリフが出たら
			money = 100;
			if (talkflag == true) {
				// 回復頼んだら
				if (healY == 0) {
					// お金あれば
					if (premoney >= money) {
						premoney -= money;
						healflag = true;
					}
					// お金なければ
					else {
						
					}
					healcount = heal;
					healY = 0;
				}
				// 回復やめたら
				else {
					healY = 0;
				}
				talkflag = false;
			}
			// 触れただけの時
			else {
				talkflag = true;
			}
		}
	}
	// 選択肢
	if (innflag == true && talkflag == true) {
		if (KeyData::Get(KEY_INPUT_UP) == 1) {
			healY = 0;
		}
		if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
			healY = 1;
		}
	}
	// 回復の表示
	if (healcount > 0) {
		healcount--;
	}
}

void SafeArea::PeopleProcess() {
	// 一般人に触れたら
	if (peopleflag == true) {
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
}

void SafeArea::ShopProcess() {
	// 道具屋に触れたら
	if (itemflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			// 買い物の最初の画面
			if (shopflag == true) {
				if (shopmenu == 0) {
					// 買うを押したとき
					if (shopmY == 0) {
						shopmenu = 1;
					}
					// 売るを押したとき
					else if (shopmY == 1) {
						shopmenu = 2;
					}
					// やめるを押したとき
					else {
						shopflag = false;
					}
					shopmY = 0;
				}
				// 買うを開いたときのショップ画面
				else if (shopmenu == 1) {
					if (shopmY < 4) {
						if (premoney >= money) {
							ID = shopmY + 2;
							buyflag = true;
							premoney -= money;
						}
						else {

						}
						shopcount = shop;
					}
					else {
						shopmenu = 0;
						shopmY = 0;
					}
				}
				// 売るを開いたときのショップ画面
				else if (shopmenu == 2) {
					// 戻るボタン
					if (shopmY == 9) {
						shopmenu = 0;
						shopmY = 0;
					}
					// なにかしら売る
					else {
						premoney += money;
						itemnum = shopmY;
						ID = item[shopmY];
						shopcount = shop;
						sellflag = true;
					}
				}
			}
			// 触れただけの時
			else {
				shopflag = true;
			}
		}
	}
	// ショップの売買後の会話表示
	if (shopcount >= 0) {
		shopcount--;
	}
	// 買うときのショップの値段表示
	if (shopmenu == 1) {
		switch (shopmY) {
		case 0:
			money = 10;
			break;
		case 1:
			money = 15;
			break;
		case 2:
			money = 10;
			break;
		case 3:
			money = 20;
			break;
		default:
			money = 0;
			break;
		}
	}
	// 売るときのショップの値段表示
	if (shopmenu == 2) {
		switch (item[shopmY]) {
		case 2:
			money = 5;
			break;
		case 3:
			money = 7;
			break;
		case 4:
			money = 5;
			break;
		case 5:
			money = 10;
			break;
		default:
			money = 0;
			break;
		}
	}
	// ショップ画面でのカーソル移動
	if (shopflag == true && itemflag == true) {
		// 上を押した
		if (KeyData::Get(KEY_INPUT_UP) == 1) {
			// 一番上じゃなければ
			if (shopmY > 0) {
				shopmY--;
			}
			// 一番上なら
			else {

			}
		}
		// 下を押した
		if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
			if (shopmenu == 0) {
				// 一番下じゃなければ
				if (shopmY < 2) {
					shopmY++;
				}
				// 一番下なら
				else {

				}
			}
			else if (shopmenu == 1) {
				// 一番下じゃなければ
				if (shopmY < 4) {
					shopmY++;
				}
				// 一番下なら
				else {

				}
			}
			else {
				// 一番下じゃなければ
				if (shopmY < 9) {
					shopmY++;
				}
				// 一番下なら
				else {

				}
			}
		}
	}
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

void SafeArea::SetNum(int num) {
	itemnum = num;
}

int SafeArea::GetNum() {
	return itemnum;
}

void SafeArea::SetnumID(int num, int ID) {
	item[num] = ID;
}

void SafeArea::SetMoney(int money) {
	premoney = money;
}

int SafeArea::GetMoney() {
	return premoney;
}

eStep SafeArea::GetStep() {
	return step;
}