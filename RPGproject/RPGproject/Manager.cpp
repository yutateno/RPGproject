#include "Manager.h"

Manager::Manager() {
	playerX = 0;
	playerY = 0;
	probability = 50000;

	player = new Player();
	this->endFlag = false;
	this->NowScene = eScene::S_Title;
	this->title = new Title();
}
Manager::~Manager() {
	switch (NowScene)
	{
	case eScene::S_Title://�^�C�g�����
		delete title;
		break;
	case eScene::S_Field:// �t�B�[���h���
		delete field;
		break;
	case eScene::S_Battle:// �퓬���
		delete battle;
		break;
	case eScene::S_SafeArea:// ���_���
		delete safeArea;
		break;
	case eScene::S_Dungeon://�_���W�������
		delete dungeon;
		break;
	case eScene::S_GameOver://�Q�[���I�[�o�[���
		delete gameOver;
		break;
	case eScene::S_GameClear://�Q�[���N���A���
		delete gameClear;
		break;
	default:	//Error
		break;
	}

	delete player;
}

void Manager::UpDate() {

	// �y��ʐ؂�ւ��z
	switch (this->NowScene) {
	case eScene::S_Title://�^�C�g�����
		// �G���h�t���O���������玟�̃V�[���ֈڍs
		if (this->title->GetEndFlag()) {
			this->ChengeScene_Title();
		}
		break;
	case eScene::S_Field:// �t�B�[���h���
		if (this->field->GetEndFlag()) {
			this->ChengeScene_Field();
		}
		break;
	case eScene::S_Battle:// �퓬���
		if (this->battle->GetEndFlag()) {
			this->ChengeScene_Battle();
		}
		break;
	case eScene::S_SafeArea:// ���_���
		if (this->safeArea->GetEndFlag()) {
			this->ChengeScene_SafeArea();
		}
		break;
	case eScene::S_Dungeon://�_���W�������
		if (this->dungeon->GetEndFlag()) {
			this->ChengeScene_Dungeon();
		}
		break;
	case eScene::S_GameOver://�Q�[���I�[�o�[���
		if (this->gameOver->GetEndFlag()) {
			this->ChengeScene_GameOver();
		}
		break;
	case eScene::S_GameClear://�Q�[���N���A���
		if (this->gameClear->GetEndFlag()) {
			this->ChengeScene_GameClear();
		}
		break;
	default:	//Error
		this->endFlag = true;
		break;
	}



	// �y�e��ʃA�b�v�f�[�g�z
	switch (this->NowScene) {
	case eScene::S_Title://�^�C�g�����
		this->title->UpDate();
		break;
	case eScene::S_Field:// �t�B�[���h���

		// ���̃V�[���̃v���Z�X
		this->field->UpDate(player->GetX(), player->GetY());

		// �v���C���[�����������ǂ����𔻒f���邽�߂ɒ��O�̍��W��ۑ�
		playerX = player->GetX();
		playerY = player->GetY();

		// �t�B�[���h�̃��C���v���Z�X�������Ă�ԃv���C���[�̃v���Z�X���Ăяo��
		if (field->GetStep() == eStep::Main)
		{
			player->Move();
		}

		// �G�Ƃ̃G���J�E���g
		if (player->GetX() != playerX || player->GetY() != playerY)
		{
			if (GetRand(probability) == 0)
			{
				field->SetNextScene(eScene::S_Battle);
				field->SetStep(eStep::End);
			}
		}

		// �J�����̈ʒu���v���C���[�̍��W����v�Z���đ��
		if (player->GetX() < (320 - 16))		// ���[
		{
			field->SetCameraX(0);
		}
		else if (player->GetX() > ((field->GetMapWidth() - 1) * 32) - (320 - 16))		// �E�[
		{
			field->SetCameraX((field->GetMapWidth() * 32) - 640);
		}
		else		// ����ȊO
		{
			field->SetCameraX(player->GetX() - (320 - 16));
		}

		if (player->GetY() < (240 - 16))		// ��[
		{
			field->SetCameraY(0);
		}
		else if (player->GetY() > ((field->GetMapHeight() - 1) * 32) - (240 - 16))		// ���[
		{
			field->SetCameraY((field->GetMapHeight() * 32) - 480);
		}
		else		// ����ȊO
		{
			field->SetCameraY(player->GetY() - (240 - 16));
		}

		// �}�b�v�Ƃ̓����蔻��
		switch (field->GetMapData(player->GetX(), player->GetY()))
		{
		case 0:			// ��
			break;
		case 1:			// ��
			player->MoveReset();		// �v���C���[�̍��W�𒼑O�̂��̂ɖ߂�
			break;
		default:
			// ��{�I�ɗ��Ȃ�
			break;
		}
		break;

	case eScene::S_Battle:// �퓬���
		this->battle->UpDate();
		switch (battle->GetCommand())
		{
		case NEUTRAL:		// ���ł��Ȃ��Ƃ�
			break;
		case ATTACK:		// ���ł��Ȃ��Ƃ�
			break;
		case DATTACK:		// �U�����鎞
			enemy->SetHP(enemy->GetHP() - player->GetATK());		// �_���[�W��^����
			battle->SetCommand(NEUTRAL);
			break;
		case MAGIC:			// ���ł��Ȃ��Ƃ�
			break;
		case DMAGIC:		// ���@�U������Ƃ�
			enemy->SetHP(enemy->GetHP() - player->GetATK());		// �_���[�W��^����
			battle->SetCommand(NEUTRAL);
			break;
		case RUN_AWAY:		// ���ł��Ȃ��Ƃ�
			break;
		default:
			// �ʏ허�Ȃ�
			break;
		}

		// �퓬�I��
		if (enemy->GetHP() < 0 || player->GetHP() < 0)
		{
			battle->SetStep(eStep::End);
		}
		break;

	case eScene::S_SafeArea:// ���_���
		this->safeArea->UpDate();
		break;
	case eScene::S_Dungeon://�_���W�������
		this->dungeon->UpDate();
		player->Move();
		// �ʒu�C��
		if (dungeon->GetMapData(player->GetX(), player->GetY()) == 10)
		{
			player->MoveReset();
		}
		dungeon->SetX(player->GetX()-320);
		dungeon->SetY(player->GetY()-240);
		break;
	case eScene::S_GameOver://�Q�[���I�[�o�[���
		this->gameOver->UpDate();
		break;
	case eScene::S_GameClear://�Q�[���N���A���
		this->gameClear->UpDate();
		break;
	default:	//Error
		this->endFlag = true;
		break;
	}
}

// �^�C�g����ʂ���̃V�[���ڍs
void Manager::ChengeScene_Title() {
	//InitGraph();	// �S�O���t�B�b�N�폜
	InitSoundMem();	// �ȃf�[�^�S�폜

	this->NowScene = this->title->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		this->field = new Field();

		// �v���C���[�̏����ʒu�ړ�
		player->SetX(320 - 16);
		player->SetY(240 - 16);

		delete this->title;	// �^�C�g�����̍폜
		break;
	case eScene::S_End://�Q�[���I��
		this->endFlag = true;
		delete this->title;	// �^�C�g�����̍폜
		break;
	default:	//Error
		this->endFlag = true;
		delete this->title;	// �^�C�g�����̍폜
		break;
	}
}

// �t�B�[���h��ʂ���̃V�[���ڍs
void Manager::ChengeScene_Field() {
	//InitGraph();	// �S�O���t�B�b�N�폜
	InitSoundMem();	// �ȃf�[�^�S�폜

	this->NowScene = this->field->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Battle:// �퓬���
		this->battle = new Battle();
		enemy = new Enemy();
		// �t�B�[���h��ʂ���ڍs�������Ƃ�ۑ�
		this->battle->SetReturnScene(eScene::S_Field);
		break;
	case eScene::S_SafeArea:// ���_���
		this->safeArea = new SafeArea();
		delete this->field;	// �t�B�[���h��ʎ��̍폜
		break;
	case eScene::S_Dungeon://�_���W�������
		this->dungeon = new Dungeon();
		player->SetX(50);
		player->SetY(50);
		delete this->field;
		break;
	case eScene::S_End://�Q�[���I��
		this->endFlag = true;
		delete this->field;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->field;
		break;
	}
}

// �퓬��ʂ���̃V�[���ڍs
void Manager::ChengeScene_Battle() {
	//InitGraph();	// �S�O���t�B�b�N�폜
	InitSoundMem();	// �ȃf�[�^�S�폜

	this->NowScene = this->battle->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		this->field = new Field();
		delete this->battle;	// �퓬��ʎ��̍폜
		break;
	case eScene::S_SafeArea:// ���_���
		this->safeArea = new SafeArea();
		delete this->battle;
		break;
	case eScene::S_Dungeon://�_���W�������
		this->dungeon = new Dungeon();
		delete this->battle;
		break;
	case eScene::S_GameOver://�Q�[���I�[�o�[���
		this->gameOver = new GameOver();
		delete this->battle;
		break;
	case eScene::S_End://�Q�[���I��
		this->endFlag = true;
		delete this->battle;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->battle;
		break;
	}

	// �G�폜
	delete enemy;
}

// ���_��ʂ���̃V�[���ڍs
void Manager::ChengeScene_SafeArea() {
	//InitGraph();	// �S�O���t�B�b�N�폜
	InitSoundMem();	// �ȃf�[�^�S�폜

	this->NowScene = this->safeArea->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		this->field = new Field();
		delete this->safeArea;	// ���_��ʎ��̍폜
		break;
	case eScene::S_Battle:// �퓬���
		this->battle = new Battle();
		// ���_��ʂ���ڍs�������Ƃ�ۑ�
		this->battle->SetReturnScene(eScene::S_SafeArea);
		delete this->safeArea;
		break;
	case eScene::S_End://�Q�[���I��
		this->endFlag = true;
		delete this->safeArea;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->safeArea;
		break;
	}
}

// �_���W������ʂ���̃V�[���ڍs
void Manager::ChengeScene_Dungeon() {
	//InitGraph();	// �S�O���t�B�b�N�폜
	InitSoundMem();	// �ȃf�[�^�S�폜

	this->NowScene = this->dungeon->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		this->field = new Field();
		delete this->dungeon;	// �_���W������ʎ��̍폜
		break;
	case eScene::S_Battle:// �퓬���
		this->battle = new Battle();
		// �_���W������ʂ���ڍs�������Ƃ�ۑ�
		this->battle->SetReturnScene(eScene::S_Dungeon);
		delete this->dungeon;
		break;
	case eScene::S_GameClear://�Q�[���N���A���
		this->gameClear = new GameClear();
		delete this->dungeon;
		break;
	case eScene::S_End://�Q�[���I��
		this->endFlag = true;
		delete this->dungeon;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->dungeon;
		break;
	}
}

// �Q�[���I�[�o�[��ʂ���̃V�[���ڍs
void Manager::ChengeScene_GameOver() {
	//InitGraph();	// �S�O���t�B�b�N�폜
	InitSoundMem();	// �ȃf�[�^�S�폜

	this->NowScene = this->gameOver->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Title://�^�C�g�����
		this->title = new Title();
		delete this->gameOver;	// �Q�[���I�[�o�[��ʎ��̍폜
		break;
	case eScene::S_End://�Q�[���I��
		this->endFlag = true;
		delete this->gameOver;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->gameOver;
		break;
	}
}

// �Q�[���N���A��ʂ���̃V�[���ڍs
void Manager::ChengeScene_GameClear() {
	//InitGraph();	// �S�O���t�B�b�N�폜
	InitSoundMem();	// �ȃf�[�^�S�폜

	this->NowScene = this->gameClear->GetNextScene();

	switch (this->NowScene) {
	case eScene::S_Title://�^�C�g�����
		this->title = new Title();
		delete this->gameClear;	// �Q�[���N���A��ʎ��̍폜
		break;
	case eScene::S_End://�Q�[���I��
		this->endFlag = true;
		delete this->gameClear;
		break;
	default:	//Error
		this->endFlag = true;
		delete this->gameClear;
		break;
	}
}

void Manager::Draw() {
	// �y�e��ʕ`��z
	switch (this->NowScene) {
	case eScene::S_Title://�^�C�g�����
		this->title->Draw();
		break;
	case eScene::S_Field:// �t�B�[���h���
		this->field->Draw();

		if (field->GetStep() == eStep::Main)
		{
			player->aaaDraw(field->GetMapWidth(), field->GetMapHeight());
		}

		// Debug------------------------------------------------------------
		DrawFormatString(0, 400, (0, 0, 200), "%d", field->GetMapWidth());
		// -----------------------------------------------------------------

		break;
	case eScene::S_Battle:// �퓬���
		this->battle->Draw();

		// Debug------------------------------------------------------------
		DrawFormatString(0, 400, (0, 0, 200), "%d", enemy->GetHP());
		// -----------------------------------------------------------------

		break;
	case eScene::S_SafeArea:// ���_���
		this->safeArea->Draw();
		break;
	case eScene::S_Dungeon://�_���W�������
		this->dungeon->Draw();
		player->aaaDraw();
		dungeon->SetX(player->GetX());
		dungeon->SetY(player->GetY());
		break;
	case eScene::S_GameOver://�Q�[���I�[�o�[���
		this->gameOver->Draw();
		break;
	case eScene::S_GameClear://�Q�[���N���A���
		this->gameClear->Draw();
		break;
	default:	//Error
		this->endFlag = true;
		break;
	}
}