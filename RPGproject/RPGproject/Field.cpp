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

	// 宝箱関係
	// このマップは宝箱1~3を使用
	for (int i = 1;i < (1 + 3);i++)
	{
		treasure.push_back(i);
	}
	treasureFlag = false;	// 宝箱を開けた時のログ表示用
	treasureName = "";		// 手に入れたアイテムの名前

	// テキストボックス
	// ログ
	logX = 112;				// 座標
	logWidth = 640 - logX;	// 幅
	logHeight = 96;			// 高さ
	logY = 480 - logHeight;	// 座標
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

	for (int i = 0;i < 2;i++)
	{
		for (int j = 0;j < 2;j++)
		{
			switch (mapdata[(int)((playerY + (i * 31)) / mapchipSize)][(int)((playerX + (j * 31)) / mapchipSize)])
			{
			case 0:
				// 特になし
				break;

			case 1:
				// 壁。Managerで処理
				break;

			case 2:
				// 2:街
				// 次のシーンを設定してステップ進行
				nextScene = eScene::S_SafeArea;
				step = eStep::End;
				break;

			case 3:
				// 3:ダンジョン
				// 次のシーンを設定してステップ進行
				nextScene = eScene::S_Dungeon;
				step = eStep::End;
				break;

			default:
				// エラー
				break;
			}
		}
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

	// 宝箱
	for (int i = 0, n = treasure.size();i < n;i++)
	{
		treasure[i].Draw(cameraX, cameraY);
	}

	// ログ
	// 宝箱
	if (treasureFlag)
	{
		Textbox::Draw(logX, logY, logWidth, logHeight, treasureName + " を手に入れた！");
	}
}
void Field::Draw_End() {
	// 次のシーンによって処理を変える
	switch (nextScene) {
	case eScene::S_Battle:// 戦闘画面
		// 徐々に画面を暗くする処理
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (count * 5));
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
		// ブレンドモードの後処理
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;

	case eScene::S_SafeArea:// 拠点画面
		break;

	case eScene::S_Dungeon://ダンジョン画面
		break;

	case eScene::S_End://ゲーム終了
		break;

	default:	//Error
		break;
	}
}

void Field::ReadMapData()
{
	ifs.open("field\\mapdata.csv");
	// マップデータ読み込み失敗
	if (!ifs)
	{
		endFlag = true;
	}

	// 仮置き
	string str;
	int count = 0;

	while (getline(ifs, str)) {
		// 仮置き
		string token;
		istringstream stream(str);

		// メモリ確保
		mapdata.resize(count + 1);

		while (getline(stream, token, ',')) {
			mapdata[count].push_back(stoi(token));
		}
		// カウントアップ
		count++;
	}
}

int Field::OpenTreasure(int num)
{
	//仮置き
	int itemID = treasure[num].GetItemID();

	// ログ表示処理
	treasureFlag = true;
	treasureName = treasure[num].GetName();

	// データ入力処理
	treasure[num].OpenProcess();

	return itemID;
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
int Field::GetTreasureNum()
{
	return treasure.size();
}
int Field::GetTreasureX(int num)
{
	return treasure[num].GetX();
}
int Field::GetTreasureY(int num)
{
	return treasure[num].GetY();
}
void Field::SetTreasureFlag(bool flag)
{
	treasureFlag = flag;
}
bool Field::GetTreasureFlag()
{
	return treasureFlag;
}