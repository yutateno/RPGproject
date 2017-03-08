#include "Manager.h"

Field::Field() {
	// ����֌W
	this->endFlag = false;				// �V�[���̏I�����Ǘ�
	this->nextScene = eScene::S_End;	// �ꉞ�̏�����

	// ���o�֌W
	this->step = eStep::Start;			// ���̃V�[���̊J�n����
	this->startCount = 50;				// �J�n���o�̎���
	this->endCount = 50;				// �I�����o�̎���
	count = 0;							// (�t���[��)���Ԃ̃J�E���g

	// �摜�ǂݍ���
	Gr_Back = LoadGraph("img\\field_background.png");		// �w�i
	mapchip[0] = LoadGraph("img\\mapchip0.png");			// ��
	mapchip[1] = LoadGraph("img\\mapchip1.png");			// ��
	mapchip[2] = LoadGraph("img\\mapchip2.png");			// �X
	mapchip[3] = LoadGraph("img\\mapchip3.png");			// �_���W����
	mapchipForID = 0;										// �`�ʗp

	// �}�b�v�`�b�v�֌W
	mapchipNum = 4;			// �}�b�v�`�b�v�̎�ސ�
	mapchipSize = 32;		// �}�b�v�`�b�v�̑傫��

	// �}�b�v�f�[�^�ǂݍ���
	ReadMapData();

	// �J�����֌W
	cameraX = 0;		// �ꉞ�̏�����
	cameraY = 0;		// �ꉞ�̏�����
}
Field::~Field() {
	// �摜�f�[�^���쏜
	DeleteGraph(Gr_Back);
	for (int i = 0;i < mapchipNum;i++)
	{
		DeleteGraph(mapchip[i]);
	}
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
	// �J�E���g�A�b�v
	this->count++;

	// startCount�������o����
	if (this->count < startCount) return;
	// �J�E���g�����Z�b�g���ăX�e�b�v�i�s
	count = 0;
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

	// 2:�X
	if (mapdata[(int)(playerY / mapchipSize)][(int)(playerX / mapchipSize)] == 2)
	{
		// ���̃V�[����ݒ肵�ăX�e�b�v�i�s
		nextScene = eScene::S_SafeArea;
		step = eStep::End;
	}
	// 3:�_���W����
	else if (mapdata[(int)(playerY / mapchipSize)][(int)(playerX / mapchipSize)] == 3)
	{
		// ���̃V�[����ݒ肵�ăX�e�b�v�i�s
		nextScene = eScene::S_Dungeon;
		step = eStep::End;
	}
}
void Field::UpDate_End() {
	// �J�E���g�A�b�v
	this->count++;

	// endCount�������o����
	if (this->count < endCount) return;
	// �J�E���g�����Z�b�g���Ă��̃V�[�����I������
	count = 0;
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
	// debug---------------------------------------------------------------------------------------------------
	DrawStringToHandle(0, 0, "�t�B�[���h���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n��� %d / %d", count, this->startCount);
	// --------------------------------------------------------------------------------------------------------
}
void Field::Draw_Main() {
	// �w�i
	DrawGraph(0, 0, Gr_Back, true);

	// �}�b�v�`�b�v
	for (int i = 0, n = mapdata.size();i < n;i++)
	{
		for (int j = 0, m = mapdata[i].size();j < m;j++)
		{
			// �ꎞ�I�ɕۑ�
			mapchipForID = mapchip[mapdata[i][j]];

			// �`��
			DrawGraph(j * 32 - cameraX, i * 32 - cameraY, mapchipForID, true);
		}
	}
}
void Field::Draw_End() {
	// debug-------------------------------------------------------------------------------------------------
	DrawStringToHandle(0, 0, "�t�B�[���h���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I����� %d / %d", count, endCount);
	// ------------------------------------------------------------------------------------------------------
}

void Field::ReadMapData()
{
	ifs.open("mapdata.txt");
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
		// ��s���̃f�[�^
		string token;
		istringstream stream(str);

		// �������m��
		mapdata.resize(count + 1);

		//1�s�̂����A������ƃR���}�𕪊�����
		while (getline(stream, token, ',')) {
			//���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
			//���l�͕ϊ����K�v
			mapdata.at(count).push_back((int)stof(token)); //stof(string str) : string��float�ɕϊ�

			// �J�E���g�A�b�v
			count2++;
		}
		// �J�E���g�A�b�v
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