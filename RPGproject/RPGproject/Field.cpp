#include "Manager.h"

Field::Field() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

	// 画像読み込み
	Gr_Back = LoadGraph("img\\field_background.png");
	mapchip1 = LoadGraph("img\\mapchip1.png");
	mapchip2 = LoadGraph("img\\mapchip2.png");

	// マップデータ読み込み
	ReadMapData();
}
Field::~Field() {
	DeleteGraph(Gr_Back);
	DeleteGraph(mapchip1);
	DeleteGraph(mapchip2);
}

void Field::UpDate() {
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
void Field::UpDate(int playerX, int playerY)
{
	switch (this->step) {
	case eStep::Start:	// 開始画面
		this->UpDate_Start();
		break;
	case eStep::Main:	// メイン処理画面
		this->UpDate_Main(playerX, playerY);
		break;
	case eStep::End:	// 終了画面
		this->UpDate_End();
		break;
	default:
		this->endFlag = true;	// エラー終了
		break;
	}
}

void Field::UpDate_Start() {
	this->startCount++;

	if (this->startCount < 50) return;	// 50フレームで開始画面終了
	this->step = eStep::Main;
}
void Field::UpDate_Main() {

	// Zキーで戦闘画面に
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	// Xキーで拠点画面に
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_SafeArea;
		this->step = eStep::End;
	}
	// Cキーでダンジョン画面に
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_Dungeon;
		this->step = eStep::End;
	}
}
void Field::UpDate_Main(int playerX, int playerY) {

	// Zキーで戦闘画面に
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	// Xキーで拠点画面に
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_SafeArea;
		this->step = eStep::End;
	}
	// Cキーでダンジョン画面に
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_Dungeon;
		this->step = eStep::End;
	}
}
void Field::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50フレームで終了画面終了
	this->endFlag = true;
}
void Field::Draw() {
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
void Field::Draw_Start() {
	DrawStringToHandle(0, 0, "フィールド画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "開始画面%d", this->startCount);
}
void Field::Draw_Main() {
	// 背景
	DrawGraph(0, 0, Gr_Back, true);

	// マップチップ
	for (int i = 0,n = mapdata.size();i < n;i++)
	{
		for (int j = 0, m = mapdata.at(i).size();j < m;j++)
		{
			switch (mapdata.at(i).at(j))
			{
			case 0:		// 何もなし
				break;

			case 1:		// マップチップ1
				DrawGraph(j * 32, i * 32, mapchip1, true);
				break;

			case 2:
				DrawGraph(j * 32, i * 32, mapchip2, true);
				break;

			default:	// 改行時に来るエラーではない
				break;
			}
		}
	}
	DrawStringToHandle(0, 0, "フィールド画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "メイン処理画面", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Zキーで戦闘画面へ", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "Xキーで拠点画面へ", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 400, "Cキーでダンジョン画面へ", WHITE, Font::Get(eFont::SELECT));
}
void Field::Draw_End() {
	DrawStringToHandle(0, 0, "フィールド画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面%d", this->endCount);
}

void Field::ReadMapData()
{
	ifstream ifs("mapdata.txt");
	// マップデータ読み込み失敗
	if (!ifs)
	{
		endFlag = true;
	}

	string str;
	int count = 0;
	int count2 = 0;
	while (getline(ifs, str)) {
		string token;
		istringstream stream(str);

		mapdata.resize(count + 1);

		//1行のうち、文字列とコンマを分割する
		while (getline(stream, token, ',')) {
			//すべて文字列として読み込まれるため
			//数値は変換が必要
			mapdata.at(count).push_back(stof(token)); //stof(string str) : stringをfloatに変換
			count2++;
		}
		count++;
	}
}

void Field::SetMapData(int x, int y, int data)
{
	mapdata[(int)(y / 32)][(int)(x / 32)] = data;
}
int Field::GetMapData(int x, int y)
{
	return mapdata[(int)(y / 32)][(int)(x / 32)];
}
void Field::SetStep(eStep step)
{
	this->step = step;
}
eStep Field::GetStep()
{
	return step;
}
void Field::SetNextScene(eScene nextScene)
{
	this->nextScene = nextScene;
}