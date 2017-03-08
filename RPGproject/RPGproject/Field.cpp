#include "Manager.h"

Field::Field() {
	// 動作関係
	this->endFlag = false;				// シーンの終了を管理
	this->nextScene = eScene::S_End;	// 一応の初期化

	// 演出関係
	this->step = eStep::Start;			// このシーンの開始処理
	this->startCount = 50;				// 開始演出の時間
	this->endCount = 50;				// 終了演出の時間
	count = 0;							// (フレーム)時間のカウント

	// 画像読み込み
	Gr_Back = LoadGraph("img\\field_background.png");		// 背景
	mapchip[0] = LoadGraph("img\\mapchip0.png");			// 床
	mapchip[1] = LoadGraph("img\\mapchip1.png");			// 木
	mapchip[2] = LoadGraph("img\\mapchip2.png");			// 街
	mapchip[3] = LoadGraph("img\\mapchip3.png");			// ダンジョン
	mapchipForID = 0;										// 描写用

	// マップチップ関係
	mapchipNum = 4;			// マップチップの種類数
	mapchipSize = 32;		// マップチップの大きさ

	// マップデータ読み込み
	ReadMapData();

	// カメラ関係
	cameraX = 0;		// 一応の初期化
	cameraY = 0;		// 一応の初期化
}
Field::~Field() {
	// 画像データ座駆除
	DeleteGraph(Gr_Back);
	for (int i = 0;i < mapchipNum;i++)
	{
		DeleteGraph(mapchip[i]);
	}
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
	// カウントアップ
	this->count++;

	// startCountだけ演出する
	if (this->count < startCount) return;
	// カウントをリセットしてステップ進行
	count = 0;
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

	// 2:街
	if (mapdata[(int)(playerY / mapchipSize)][(int)(playerX / mapchipSize)] == 2)
	{
		// 次のシーンを設定してステップ進行
		nextScene = eScene::S_SafeArea;
		step = eStep::End;
	}
	// 3:ダンジョン
	else if (mapdata[(int)(playerY / mapchipSize)][(int)(playerX / mapchipSize)] == 3)
	{
		// 次のシーンを設定してステップ進行
		nextScene = eScene::S_Dungeon;
		step = eStep::End;
	}
}
void Field::UpDate_End() {
	// カウントアップ
	this->count++;

	// endCountだけ演出する
	if (this->count < endCount) return;
	// カウントをリセットしてこのシーンを終了する
	count = 0;
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
	// debug---------------------------------------------------------------------------------------------------
	DrawStringToHandle(0, 0, "フィールド画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "開始画面 %d / %d", count, this->startCount);
	// --------------------------------------------------------------------------------------------------------
}
void Field::Draw_Main() {
	// 背景
	DrawGraph(0, 0, Gr_Back, true);

	// マップチップ
	for (int i = 0, n = mapdata.size();i < n;i++)
	{
		for (int j = 0, m = mapdata[i].size();j < m;j++)
		{
			// 一時的に保存
			mapchipForID = mapchip[mapdata[i][j]];

			// 描写
			DrawGraph(j * 32 - cameraX, i * 32 - cameraY, mapchipForID, true);
		}
	}
}
void Field::Draw_End() {
	// debug-------------------------------------------------------------------------------------------------
	DrawStringToHandle(0, 0, "フィールド画面", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "終了画面 %d / %d", count, endCount);
	// ------------------------------------------------------------------------------------------------------
}

void Field::ReadMapData()
{
	ifs.open("mapdata.txt");
	// マップデータ読み込み失敗
	if (!ifs)
	{
		endFlag = true;
	}

	// マップをテキストから読み込むための仮置きの変数
	string str;
	int count = 0;
	int count2 = 0;

	while (getline(ifs, str)) {
		// 一行分のデータ
		string token;
		istringstream stream(str);

		// メモリ確保
		mapdata.resize(count + 1);

		//1行のうち、文字列とコンマを分割する
		while (getline(stream, token, ',')) {
			//すべて文字列として読み込まれるため
			//数値は変換が必要
			mapdata.at(count).push_back((int)stof(token)); //stof(string str) : stringをfloatに変換

			// カウントアップ
			count2++;
		}
		// カウントアップ
		count++;
	}
}

void Field::SetMapData(int x, int y, int data)
{
	mapdata[(int)(y / mapchipSize)][(int)(x / mapchipSize)] = data;
}
int Field::GetMapData(int x, int y)
{
	return mapdata[(int)(y / mapchipSize)][(int)(x / mapchipSize)];
}
int Field::GetMapWidth()
{
	return mapdata[0].size();
}
int Field::GetMapHeight()
{
	return mapdata.size();
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
void Field::SetCamera(int x, int y)
{
	cameraX = x;
	cameraY = y;
}
void Field::SetCameraX(int x)
{
	cameraX = x;
}
void Field::SetCameraY(int y)
{
	cameraY = y;
}