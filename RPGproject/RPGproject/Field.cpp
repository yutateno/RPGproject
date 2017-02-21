#include "Manager.h"

Field::Field() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

	// �摜�ǂݍ���
	Gr_Back = LoadGraph("img\\field_background.png");
	mapchip0 = LoadGraph("img\\mapchip0.png");
	mapchip1 = LoadGraph("img\\mapchip1.png");
	mapchip2 = LoadGraph("img\\mapchip2.png");

	// �}�b�v�f�[�^�ǂݍ���
	ReadMapData();

	// �J�����̈ꉞ�̏������B0�͎g���Ȃ�
	cameraX = 0;
	cameraY = 0;
}
Field::~Field() {
	// �摜�f�[�^���쏜
	DeleteGraph(Gr_Back);
	DeleteGraph(mapchip0);
	DeleteGraph(mapchip1);
	DeleteGraph(mapchip2);
}

void Field::UpDate() {
	switch (this->step) {
	case eStep::Start:	// �J�n���
		this->UpDate_Start();
		break;
	case eStep::Main:	// ���C���������
		this->UpDate_Main();
		break;
	case eStep::End:	// �I�����
		this->UpDate_End();
		break;
	default:
		this->endFlag = true;	// �G���[�I��
		break;
	}
}
void Field::UpDate(int playerX, int playerY)
{
	switch (this->step) {
	case eStep::Start:	// �J�n���
		this->UpDate_Start();
		break;
	case eStep::Main:	// ���C���������
		this->UpDate_Main(playerX, playerY);
		break;
	case eStep::End:	// �I�����
		this->UpDate_End();
		break;
	default:
		this->endFlag = true;	// �G���[�I��
		break;
	}
}

void Field::UpDate_Start() {
	this->startCount++;

	if (this->startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	this->step = eStep::Main;
}
void Field::UpDate_Main() {

	// Z�L�[�Ő퓬��ʂ�
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	// X�L�[�ŋ��_��ʂ�
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_SafeArea;
		this->step = eStep::End;
	}
	// C�L�[�Ń_���W������ʂ�
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_Dungeon;
		this->step = eStep::End;
	}
}
void Field::UpDate_Main(int playerX, int playerY) {

	// Z�L�[�Ő퓬��ʂ�
	/*
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	*/
	// X�L�[�ŋ��_��ʂ�
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_SafeArea;
		this->step = eStep::End;
	}
	// C�L�[�Ń_���W������ʂ�
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_Dungeon;
		this->step = eStep::End;
	}
}
void Field::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50�t���[���ŏI����ʏI��
	this->endFlag = true;
}
void Field::Draw() {
	switch (this->step) {
	case eStep::Start:	// �J�n���
		this->Draw_Start();
		break;
	case eStep::Main:	// ���C���������
		this->Draw_Main();
		break;
	case eStep::End:	// �I�����
		this->Draw_End();
		break;
	default:
		this->endFlag = true;	// �G���[�I��
		break;
	}
}
void Field::Draw_Start() {
	DrawStringToHandle(0, 0, "�t�B�[���h���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n���%d", this->startCount);
}
void Field::Draw_Main() {
	// �w�i
	DrawGraph(0, 0, Gr_Back, true);

	// �}�b�v�`�b�v
	for (int i = 0, n = mapdata.size();i < n;i++)
	{
		for (int j = 0, m = mapdata[i].size();j < m;j++)
		{
			switch (mapdata[i][j])
			{
			case 0:		// �}�b�v�`�b�v0
				DrawGraph(j * 32 - cameraX, i * 32 - cameraY, mapchip0, true);
				break;

			case 1:		// �}�b�v�`�b�v1
				DrawGraph(j * 32 - cameraX, i * 32 - cameraY, mapchip1, true);
				break;

			case 2:		// �}�b�v�`�b�v2
				DrawGraph(j * 32 - cameraX, i * 32 - cameraY, mapchip2, true);
				break;

			default:	// ���s���ɗ���G���[�ł͂Ȃ�
				break;
			}
		}
	}
	/*
	DrawStringToHandle(0, 0, "�t�B�[���h���", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "���C���������", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Z�L�[�Ő퓬��ʂ�", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "X�L�[�ŋ��_��ʂ�", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 400, "C�L�[�Ń_���W������ʂ�", WHITE, Font::Get(eFont::SELECT));
	*/
	DrawFormatString(420, 360, BLACK, "�t�B�[���h���\n���C���������\nX�L�[�ŋ��_��ʂ�\nC�L�[�Ń_���W������ʂ�\n");
}
void Field::Draw_End() {
	DrawStringToHandle(0, 0, "�t�B�[���h���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I�����%d", this->endCount);
}

void Field::ReadMapData()
{
	ifstream ifs("mapdata.txt");
	// �}�b�v�f�[�^�ǂݍ��ݎ��s
	if (!ifs)
	{
		endFlag = true;
	}

	// �}�b�v���e�L�X�g����ǂݍ��ނ��߂̉��u���̕ϐ�
	string str;
	int count = 0;
	int count2 = 0;

	while (getline(ifs, str)) {
		string token;
		istringstream stream(str);

		mapdata.resize(count + 1);

		//1�s�̂����A������ƃR���}�𕪊�����
		while (getline(stream, token, ',')) {
			//���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
			//���l�͕ϊ����K�v
			mapdata.at(count).push_back((int)stof(token)); //stof(string str) : string��float�ɕϊ�
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