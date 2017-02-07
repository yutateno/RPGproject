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
	Gr_Player = LoadGraph("Dungeon\\player.png");

	player_x = 0;
	player_y = 0;
}

Dungeon::~Dungeon() {

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
	MapDate();
}
void Dungeon::UpDate_Start() {
	startCount++;

	if (startCount < 50) return;	// 50フレームで開始画面終了
	step = eStep::Main;
}

void Dungeon::UpDate_Main() {

	// Zキーで戦闘画面に
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	// Xキーでフィールド画面に
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}
	// Cキーでゲームクリア画面に
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_GameClear;
		this->step = eStep::End;
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
		Draw_Main();
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
	//DrawStringToHandle(0, 0, "ダンジョン画面", WHITE, Font::Get(eFont::SELECT));
	//DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "開始画面%d", this->startCount);
}

void Dungeon::Draw_Main() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0, n = (int)map.size(); i < n; i++) {
		for (int j = 0, m = (int)map[i].size(); j < m; j++) {
			// 画面内なら描画　playerの位置を左上として右下までの範囲です
			if (j * 28 + player_x >= -28 && j * 28 + player_x <= 640 &&
				i * 28 + player_y >= -28 && i * 28 + player_y <= 480) {
				//stoi で文字を数値に変換
				switch ((int)(stoi(map[i][j]) * 0.1)) {
				case 0:	//00
					break;

				case 1:	//壁
					switch (stoi(map[i][j]) % 10) {
					case 0:	//10
						DrawGraph(j * 28 + player_x, i * 28 + player_y, Gr_Wall, false);
						break;

					default:
						break;
					}
					break;
				case 3:
					switch (stoi(map[i][j]) % 10) {
					case 0:
						DrawGraph(j * 28 + player_x, i * 28 + player_y, Gr_Player, false);
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
	}

	//DrawStringToHandle(0, 0, "ダンジョン画面", WHITE, Font::Get(eFont::SELECT));
	//DrawStringToHandle(0, 100, "メイン処理画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Zキーで戦闘画面へ", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "Xキーでフィールド画面へ", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 400, "Cキーでゲームクリア画面へ", WHITE, Font::Get(eFont::SELECT));
}

void Dungeon::Draw_End() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150 - (endCount * 1));
	DrawRotaGraph(320, 240, 1.0, endCount * 1, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawStringToHandle(0, 0, "ダンジョン画面", WHITE, Font::Get(eFont::SELECT));
	//DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面%d", this->endCount);
}

void Dungeon::MapDate() {
	read_file.open("Dungeon\\DungeonMap.txt");
	read_count = 0;
	while (getline(read_file, read_line)) {	// 一行ずつ読み込み
		map.resize(read_count + 1);
		for (int i = 0, n = (int)read_line.length(); i < n; i += 2) {
			map[read_count].push_back(read_line.substr(i, 2));
		}
		read_count++;	// 次の行に
	}
}