#include "Manager.h"
#include "Dungeon.h"

Dungeon::Dungeon() {
	endFlag = false;
	nextScene = eScene::S_End;
	step = eStep::Start;
	startCount = 0;
	endCount = 0;

	Gr_Back = LoadGraph("Dungeon\\Dungeon_Back.png");
	Gr_Wall = LoadGraph("Dungeon\\wall.png");
	Gr_Treasure = LoadGraph("Dungeon\\Treasure.png");
	Gr_Open = LoadGraph("Dungeon\\open.png");
	MapData();

	x = 0;
	y = 0;
	fieldflag = false;
	battleflag = false;
	bossflag = false;

	comment = 0;
	treasureMax = 10;
	num = 0;
	for (int i = 0; i < treasureMax; i++) {
		treasure[i] = false;
	}
	touchflag = false;
}

Dungeon::~Dungeon() {
	DeleteGraph(Gr_Back);
	DeleteGraph(Gr_Wall);
	DeleteGraph(Gr_Treasure);
	DeleteGraph(Gr_Open);
}

void Dungeon::UpDate() {
	switch (step) {
	case eStep::Start:	// 開始画面
		UpDate_Start();
		break;
	case eStep::Main:	// メイン処理画面
		UpDate_Main();
		break;
	case eStep::End:	// 終了画面
		UpDate_End();
		break;
	default:
		endFlag = true;	// エラー終了
		break;
	}
}

void Dungeon::UpDate(int playerX, int playerY) {
	switch (step) {
	case eStep::Start:	// 開始画面
		UpDate_Start();
		break;
	case eStep::Main:	// メイン処理画面
		UpDate_Main();
		break;
	case eStep::End:	// 終了画面
		UpDate_End();
		break;
	default:
		endFlag = true;	// エラー終了
		break;
	}
}

void Dungeon::UpDate_Start() {
	startCount++;

	if (startCount < 50) return;	// 50フレームで開始画面終了
	step = eStep::Main;
}

void Dungeon::UpDate_Main() {

	// ボスチップに当たったら戦闘画面
	if (battleflag == true) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	// 特定の場所行ったらフィールド画面へ
	if (fieldflag == true) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}
	// Cキーでゲームクリア画面に
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_GameClear;
		this->step = eStep::End;
	}
	// 宝箱をクリックした
	if (touchflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			if (treasure[num] == false)
				comment = flame;
		}
	}
	if (comment > 0) {
		comment--;
	}
}
void Dungeon::UpDate_End() {
	endCount++;

	if (endCount < 50) return;	// 50フレームで終了画面終了
	endFlag = true;
}
void Dungeon::Draw() {
	switch (step) {
	case eStep::Start:	// 開始画面
		Draw_Start();
		break;
	case eStep::Main:	// メイン処理画面
		Draw_Main(GetX(), GetY());
		break;
	case eStep::End:	// 終了画面
		Draw_End();
		break;
	default:
		endFlag = true;	// エラー終了
		break;
	}
}

void Dungeon::Draw_Start() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, startCount * 3);
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Dungeon::Draw_Main(int x, int y) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0, n = (int)map.size(); i < n; i++) {
		for (int j = 0, m = (int)map[i].size(); j < m; j++) {
				//stoi で文字を数値に変換
			switch ((int)(stoi(map[i][j]) * 0.1)) {
			case 0:	//00
				break;

			case 1:	//壁
				switch (stoi(map[i][j]) % 10) {
				case 0:	//10
					DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Wall, false);
					break;

				default:
					break;
				}
				break;

			case 2:
				switch (stoi(map[i][j]) % 10) {
				case 0:
					DrawBox(j * 32 - x - 32, i * 32 - y - 32, j * 32 - x, i * 32 - y, BLUE, TRUE);
					break;

				default:
					break;
				}
				break;

			case 3:
				switch (stoi(map[i][j]) % 10) {
				case 0:
					DrawBox(j * 32 - x - 32, i * 32 - y - 32, j * 32 - x, i * 32 - y, BLACK, TRUE);
					break;

				default:
					break;
				}
				break;

			case 4:
				switch (stoi(map[i][j]) % 10) {
				case 0:
					if (treasure[0] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 1:
					if (treasure[1] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 2:
					if (treasure[2] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 3:
					if (treasure[3] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 4:
					if (treasure[4] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 5:
					if (treasure[5] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 6:
					if (treasure[6] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 7:
					if (treasure[7] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 8:
					if (treasure[8] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
					break;
				case 9:
					if (treasure[9] == false) {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Treasure, TRUE);
					}
					else {
						DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Open, TRUE);
					}
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

	DrawFormatString(320, 400, WHITE, "Cキーでゲームクリア画面へ");
}

void Dungeon::Draw_End() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150 - (endCount * 3));
	DrawRotaGraph(320, 240, 1.0, endCount, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Dungeon::Draw_UI() {
	if (comment > 0) {
		DrawBox(150 - 10, 150 - 10, 150 + 200, 150 + 35, BLACK, true);
		DrawBox(150 - 10, 150 - 10, 150 + 200, 150 + 35, GREEN, false);
		DrawFormatString(150, 150, WHITE, "世界樹のハを手に入れた！");
	}
}

void Dungeon::MapData() {
	read_file.open("Dungeon\\DungeonMap.txt");
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

int Dungeon::GetMapData(int x, int y) {
	return stoi(map[(int)(y / 32)][(int)(x / 32)]);
}

int Dungeon::GetMapWidth(){
	return (int)map[0].size();
}
int Dungeon::GetMapHeight(){
	return (int)map.size();
}

void Dungeon::SetX(int x) {
	this->x = x;
}

int Dungeon::GetX() {
	return this->x;
}

void Dungeon::SetY(int y) {
	this->y = y;
}

int Dungeon::GetY() {
	return this->y;
}

void Dungeon::SetField(bool flag) {
	fieldflag = flag;
}

bool Dungeon::GetField() {
	return fieldflag;
}

void Dungeon::SetBattle(bool flag) {
	battleflag = flag;
}

bool Dungeon::GetBattle() {
	return battleflag;
}

void Dungeon::SetBoss(bool flag) {
	bossflag = flag;
}

bool Dungeon::GetBoss() {
	return bossflag;
}

void Dungeon::SetNum(int num) {
	this->num = num;
}

int Dungeon::GetNum() {
	return num;
}

void Dungeon::SetTreasure(int num, bool treasure) {
	this->treasure[num] = treasure;
}

bool Dungeon::GetTreasure(int num) {
	return treasure[num];
}

void Dungeon::SetTouch(bool flag) {
	touchflag = flag;
}

bool Dungeon::GetTouch() {
	return touchflag;
}

eStep Dungeon::GetStep(){
	return step;
}