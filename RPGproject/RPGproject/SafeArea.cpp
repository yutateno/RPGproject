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
	talkflag = false;
	shopflag = false;
	healcount = 0;
	shopmenu = 0;
	shopmY = 0;
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

	// 噴水に触れたら
	if (healflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			healcount = heal;
		}
	}

	// 一般人に触れたら
	if (peopleflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			if (talkflag == false) {
				talkflag = true;
			}
			else {
				talkflag = false;
			}
		}
	}
	
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
					switch (shopmY) {
					case 0:
						//str = "やく(にたちそうな)くさ";
						break;
					case 1:
						//str = "清らかな水";
						break;
					case 2:
						//str = "けむりダマ";
						break;
					case 3:
						//str = "世界樹のハ";
						break;
					default:
						shopmenu = 0;
						shopmY = 0;
						break;
					}
				}
				// 売るを開いたときのショップ画面
				else if (shopmenu == 2) {
					switch (shopmY) {
					case 0:
						//str = "やく(にたちそうな)くさ";
						break;
					case 1:
						//str = "清らかな水";
						break;
					case 2:
						//str = "けむりダマ";
						break;
					case 3:
						//str = "世界樹のハ";
						break;
					default:
						shopmenu = 0;
						shopmY = 0;
						break;
					}
				}
			}
			// 触れただけの時
			else {
				shopflag = true;
			}
		}
	}
	// ショップ画面でのカーソル移動
	if (shopflag == true && itemflag == true) {
		// 上を押した
		if (KeyData::Get(KEY_INPUT_UP) == 1) {
			// 一番上じゃなければ
			if (shopmY > 0) {
				shopmY --;
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
				if (shopmY < 4) {
					shopmY++;
				}
				// 一番下なら
				else {

				}
			}
		}
	}
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

	if (healcount > 0) {
		DrawFormatString(320, 240, BLACK, "回復しました。");
		healcount--;
	}

	if (peopleflag == true && talkflag == true) {
		DrawFormatString(320, 240, BLACK, "ここは町です。");
	}

	if (itemflag == true && shopflag == true) {
		if (shopmenu == 0) {
			DrawFormatString(35, cursor * 0, BLACK, "買う");
			DrawFormatString(35, cursor * 1, BLACK, "売る");
			DrawFormatString(35, cursor * 2, BLACK, "やめる");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "いらっしゃーい");
		}
		else if(shopmenu == 1) {
			DrawFormatString(35, cursor * 0, BLACK, "やく(にたちそうな)くさ");
			DrawFormatString(35, cursor * 1, BLACK, "清らかな水");
			DrawFormatString(35, cursor * 2, BLACK, "けむりダマ");
			DrawFormatString(35, cursor * 3, BLACK, "世界樹のハ");
			DrawFormatString(35, cursor * 4, BLACK, "戻る");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "何を買う？");
		}
		else {
			DrawFormatString(35, cursor * 0, BLACK, "やく(にたちそうな)くさ");
			DrawFormatString(35, cursor * 1, BLACK, "清らかな水");
			DrawFormatString(35, cursor * 2, BLACK, "けむりダマ");
			DrawFormatString(35, cursor * 3, BLACK, "世界樹のハ");
			DrawFormatString(35, cursor * 4, BLACK, "戻る");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "何を売る？");
		}
	}
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
	if (fieldflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetPeople(bool flag) {
	peopleflag = flag;
}

bool SafeArea::GetPeople() {
	if (peopleflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetItem(bool flag) {
	itemflag = flag;
}

bool SafeArea::GetItem() {
	if (itemflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetShop(bool flag) {
	shopflag = flag;
}

bool SafeArea::GetShop(){
	if (shopflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetHeal(bool flag) {
	healflag = flag;
}

bool SafeArea::GetHeal() {
	if (healflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetTalk(bool flag) {
	talkflag = flag;
}

bool SafeArea::GetTalk() {
	if (talkflag == true) {
		return true;
	}
	else {
		return false;
	}
}

eStep SafeArea::GetStep() {
	return step;
}