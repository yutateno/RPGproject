#include "Manager.h"

Manager::Manager() {
	playerX = 0;
	playerY = 0;
	probability = 200;

	// �퓬�֘A
	turn = true;		// true : �v���C���[�̃^�[��
	count = 0;
	preHP = 0;
	lose = false;

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
		FieldProcess();
		break;

	case eScene::S_Battle:// �퓬���
		// ���O��HP��ۑ�
		if (count == 0)
		{
			if (turn)
			{
				preHP = enemy->GetHP();
			}
			else
			{
				preHP = player->GetHP();
			}
		}

		BattleProcess();
		break;
		
	case eScene::S_SafeArea:// ���_���
		SafeAreaProcess();
		break;

	case eScene::S_Dungeon://�_���W�������
		DungeonProcess();
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
		count = 0;
		enemy = new Enemy((int)GetRand(1));
		// �t�B�[���h��ʂ���ڍs�������Ƃ�ۑ�
		this->battle->SetReturnScene(eScene::S_Field);
		break;
	case eScene::S_SafeArea:// ���_���
		this->safeArea = new SafeArea();
		// �v���C���[�̏����ʒu�ړ�
		player->SetX(320 - 16);
		player->SetY(480 - 64);
		delete this->field;	// �t�B�[���h��ʎ��̍폜
		break;
	case eScene::S_Dungeon://�_���W�������
		this->dungeon = new Dungeon();
		player->SetX(464);
		player->SetY(864);
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

	if (lose)
	{
		NowScene = eScene::S_GameOver;
	}
	else
	{
		// �o���l�̏����̏���
		player->SetEXP(player->GetEXP() + enemy->GetEXP());


		// ���x���A�b�v�̏���
		if (player->GetLV() * 20 < player->GetEXP())
		{
			player->SetEXP(0);
			player->SetLV(player->GetLV() + 1);
			// �ő�HPMP�㏸
			player->SetMaxHP(player->GetMaxHP() + player->GetLV());
			player->SetMaxMP(player->GetMaxMP() + player->GetLV());
		}
		this->NowScene = this->battle->GetNextScene();
	}

	switch (this->NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		this->field = new Field();

		// �v���C���[�̏����ʒu�ړ�
		player->SetX(playerX);
		player->SetY(playerY);

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

		// �v���C���[�̏����ʒu�ړ�
		player->SetX(320 - 16);
		player->SetY(240 - 16);

		delete this->safeArea;	// ���_��ʎ��̍폜
		break;
	case eScene::S_Battle:// �퓬���
		this->battle = new Battle();
		count = 0;
		enemy = new Enemy();
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
		// �v���C���[�̏����ʒu�ړ�
		player->SetX(320 - 16);
		player->SetY(240 - 16);
		delete this->dungeon;	// �_���W������ʎ��̍폜
		break;
	case eScene::S_Battle:// �퓬���
		this->battle = new Battle();
		count = 0;
		enemy = new Enemy();
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

		break;
	case eScene::S_Battle:// �퓬���
		// �R�}���h�̕\��
		if (turn&&count == 0)
		{
			battle->Draw(true);
		}
		else
		{
			battle->Draw(false);
		}

		// ���O�̕\��
		if (count != 0)
		{
			// ������
			if (enemy->GetHP() <= 0)
			{
				DrawFormatString(0, 384, WHITE, "����\n %d �̌o���l���l���I", enemy->GetEXP());
			}
			// �s�k��
			else if (player->GetHP() <= 0)
			{
				DrawFormatString(0, 384, WHITE, "�s�k");
			}
			else
			{
				if (turn)
				{
					DrawFormatString(0, 384, WHITE, " %s �̍U���I\n %s �� %d �_���[�W�I", player->GetName().c_str(), enemy->GetName().c_str(), preHP - enemy->GetHP());
				}
				else
				{
					DrawFormatString(0, 384, WHITE, " %s �̍U���I\n %s �� %d �_���[�W�I", enemy->GetName().c_str(), player->GetName().c_str(), preHP - player->GetHP());
				}
			}
		}

		// ���C����ʂ݂̂̕`��
		if (battle->GetStep() == eStep::Main)
		{
			// �G�̕`��
			if (turn)
			{
				if (battle->GetDamageFlag())
				{
					if (count % 5 != 0)
					{
						enemy->aaaDraw();
					}
				}
				else
				{
					enemy->aaaDraw();
				}
			}
			else
			{
				enemy->aaaDraw();
			}

			// �v���C���[�̃X�e�[�^�X
			DrawFormatString(0, 0, WHITE, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());

			// debug-------------------------------------------------------------------------------------
			// �G�̃X�e�[�^�X
			DrawFormatString(300, 0, WHITE, "%s\nHP:%d\nMP:%d", enemy->GetName().c_str(), enemy->GetHP(), enemy->GetMP());
			// -----------------------------------------------------------------------------------------
		}
		break;

	case eScene::S_SafeArea:// ���_���

		this->safeArea->Draw();

		//�}�b�v�`�b�v�̓����蔻��
		if (safeArea->GetStep() == eStep::Main) {
			player->aaaDraw(safeArea->GetMapWidth(), safeArea->GetMapHeight());
		}
		break;

	case eScene::S_Dungeon://�_���W�������
		
		this->dungeon->Draw();
		
		//�}�b�v�`�b�v�̓����蔻��
		if (dungeon->GetStep() == eStep::Main) {
			player->aaaDraw(dungeon->GetMapWidth(), dungeon->GetMapHeight());
		}
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

void Manager::FieldProcess()
{
	// ���̃V�[���̃v���Z�X
	this->field->UpDate(player->GetX(), player->GetY());

	// �v���C���[�����������ǂ����𔻒f���邽�߂ɒ��O�̍��W��ۑ�
	playerX = player->GetX();
	playerY = player->GetY();

	// �t�B�[���h�̃��C���v���Z�X�������Ă�ԃv���C���[�̃v���Z�X���Ăяo��
	if (field->GetStep() == eStep::Main)
	{
		player->Process();
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

	// �}�b�v�Ƃ̓����蔻��----------------------------------
	for (int i = 0;i < 2;i++)
	{
		for (int j = 0;j < 2;j++)
		{
			switch (field->GetMapData(player->GetX() + (i * (32 - 1)), player->GetY() + (j * (32 - 1))))
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
		}
	}
	// --------------------------------------------------
}

void Manager::BattleProcess()
{
	// ���O�̕\�����͓��͂��󂯕t���Ȃ�
	if (count == 0 || battle->GetStep() == eStep::End)
	{
		this->battle->UpDate();
	}
	else
	{
		// �A�j���[�V�����Ƃ���������΂�������
	}

	// �퓬����
	if (enemy->GetHP() <= 0)
	{
		if (count < 100)			// ���O��X�t���[���\������
		{
			count++;
		}
		else
		{
			battle->SetStep(eStep::End);
		}
	}
	// �퓬�s�k
	else if (player->GetHP() <= 0)
	{
		if (count < 100)			// ���O��X�t���[���\������
		{
			count++;
		}
		else
		{
			lose = true;
			battle->SetStep(eStep::End);
		}
	}
	else
	{
		// �����̃^�[��
		if (turn)
		{
			if (battle->GetDamageFlag())		// battle����_���[�W��^����x�����󂯂���
			{
				if (count == 0)
				{
					switch (battle->GetCommand())
					{
					case NEUTRAL:			// �����Ȃ�
						break;

					case ATTACK:
						break;

					case MAGIC:
						// MP����
						if (player->GetMP() > 0)
						{
							player->SetMP(player->GetMP() - 1);
						}
						else
						{
							battle->SetDamageFlag(false);			// �t���O��܂�
							battle->SetCommand(NEUTRAL);
							count = 0;			// �J�E���g��߂�
							return;
						}
						break;

					case RUN_AWAY:
						break;

					default:
						break;
					}
					player->SetATK(battle->GetDamageWidth());			// �I�������s���𔽉f����
					enemy->SetHP(enemy->GetHP() - player->GetATK());		// �_���[�W
				}
				if (count < 50)			// ���O��X�t���[���\������
				{
					count++;
				}
				else
				{
					battle->SetDamageFlag(false);			// �t���O��܂�
					battle->SetCommand(NEUTRAL);
					count = 0;			// �J�E���g��߂�
					turn = false;			// �����ĂɃ^�[����n��
				}
			}
		}
		// ����̃^�[��
		else
		{
			if (count == 0)
			{
				player->SetHP(player->GetHP() - enemy->GetATK());		// �U���͕������_���[�W
			}
			if (count < 50)			// ���O��X�t���[���\������
			{
				count++;
			}
			else
			{
				count = 0;			// �J�E���g��߂�
				turn = true;			// �v���C���[�Ƀ^�[����n��
			}
		}
	}
}

void Manager::DungeonProcess() {
	this->dungeon->UpDate(player->GetX(), player->GetY());

	// �v���C���[�����������ǂ����𔻒f���邽�߂ɒ��O�̍��W��ۑ�
	playerX = player->GetX();
	playerY = player->GetY();

	// �_���W�����̃��C���v���Z�X�������Ă�ԃv���C���[�̃v���Z�X���Ăяo��
	if (dungeon->GetStep() == eStep::Main)
	{
		player->Process();
	}

	// �ʒu�C��
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			switch (dungeon->GetMapData(player->GetX() + (i * (32 - 1)), player->GetY() + (j * (32 - 1))))
			{
			case 10:
				player->MoveReset();		// �v���C���[�̍��W�𒼑O�̂��̂ɖ߂�
				break;
			case 20:
				dungeon->SetField(true);
				break;
			case 30:
				player->MoveReset();
				dungeon->SetBoss(true);
				break;
			default:
				// ��{�I�ɗ��Ȃ�
				break;
			}
		}
	}

	// �{�X�ɐG�ꂽ��
	if (dungeon->GetBoss() == true && player->GetmenuFlag() == false) {
		// ��������L�����Z��
		if (playerY != player->GetY() || playerX != player->GetX()) {
			dungeon->SetBoss(false);
		}
		// ���̂܂܂Ȃ�퓬
		else {
			if (KeyData::Get(KEY_INPUT_Z) == 1) {
				dungeon->SetBattle(true);
			}
		}
	}
	// �G�Ƃ̃G���J�E���g
	if ((player->GetX() != playerX || player->GetY() != playerY) && player->GetmenuFlag() == false)
	{
		if (GetRand(probability) == 0)
		{
			dungeon->SetBattle(true);
		}
	}
	// �J�����̈ʒu���v���C���[�̍��W����v�Z���đ��
	if (player->GetX() < (320 - 16))		// ���[
	{
		dungeon->SetX(-32);
	}
	else if (player->GetX() > (dungeon->GetMapWidth() * 32 - 32) - (320 - 16))		// �E�[
	{
		dungeon->SetX((dungeon->GetMapWidth() * 32) - 640 - 32);
	}
	else		// ����ȊO
	{
		dungeon->SetX(player->GetX() - (320 - 16) - 32);
	}

	if (player->GetY() < (240 - 16))		// ��[
	{
		dungeon->SetY(-32);
	}
	else if (player->GetY() > (dungeon->GetMapHeight() * 32 - 32) - (240 - 16))		// ���[
	{
		dungeon->SetY((dungeon->GetMapHeight() * 32) - 480 - 32);
	}
	else		// ����ȊO
	{
		dungeon->SetY(player->GetY() - (240 - 16) - 32);
	}
}

void Manager::SafeAreaProcess() {
	this->safeArea->UpDate(player->GetX(), player->GetY());

	// �v���C���[�����������ǂ����𔻒f���邽�߂ɒ��O�̍��W��ۑ�
	playerX = player->GetX();
	playerY = player->GetY();
	
	if (safeArea->GetStep() == eStep::Main && safeArea->GetTalk() == false && safeArea->GetShop() == false)
	{
		player->Process();
	}

	// �J�����̈ʒu���v���C���[�̍��W����v�Z���đ��
	if (player->GetX() < (320 - 16))		// ���[
	{
		safeArea->SetX(0);
	}
	else if (player->GetX() > (safeArea->GetMapWidth() * 32 - 32) - (320 - 16))		// �E�[
	{
		safeArea->SetX((safeArea->GetMapWidth() * 32) - 640);
	}
	else		// ����ȊO
	{
		safeArea->SetX(player->GetX() - (320 - 16));
	}

	if (player->GetY() < (240 - 16))		// ��[
	{
		safeArea->SetY(0);
	}
	else if (player->GetY() > (safeArea->GetMapHeight() * 32 - 32) - (240 - 16))		// ���[
	{
		safeArea->SetY((safeArea->GetMapHeight() * 32) - 480);
	}
	else		// ����ȊO
	{
		safeArea->SetY(player->GetY() - (240 - 16));
	}

	// �ʒu�C��
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			switch (safeArea->GetMapData(player->GetX() + (i * (32 - 1)), player->GetY() + (j * (32 - 1))))
			{
			case 10:	// ��
				player->MoveReset();
				break;

			case 11:	// �o��
				safeArea->SetField(true);
				break;

			case 12:	// �ē��l
				player->MoveReset();
				safeArea->SetPeople(true);
				break;

			case 13:	//����
				player->MoveReset();
				safeArea->SetItem(true);
				break;

			case 14:	// ����
				player->MoveReset();
				safeArea->SetInn(true);
				break;

			default:
				break;

			}
		}
	}

	// ��ʐl�ɐG�ꂽ��
	if (safeArea->GetPeople() == true) {
		// ��������L�����Z��
		if (playerY != player->GetY() || playerX != player->GetX()) {
			safeArea->SetPeople(false);
		}
		// ���j���[���J������
		else if (player->GetmenuFlag() == true) {
			safeArea->SetPeople(false);
		}
		// ���̂܂܂Ȃ��b
		else {
			// safearea �ɂē��삳���Ă�
		}
	}

	// �����ɐG�ꂽ��
	if (safeArea->GetInn() == true) {
		// ��������L�����Z��
		if (playerY != player->GetY() || playerX != player->GetX()) {
			safeArea->SetInn(false);
		}
		// ���j���[���J������
		else if (player->GetmenuFlag() == true) {
			safeArea->SetInn(false);
		}
		// ���̂܂܂Ȃ��
		else {
			if (safeArea->GetHeal() == true) {
				player->SetHP(player->GetMaxHP());
				player->SetMP(player->GetMaxMP());
				safeArea->SetHeal(false);
			}
		}
	}

	// ����ɐG�ꂽ��
	if (safeArea->GetItem() == true) {
		// ��������L�����Z��
		if (playerY != player->GetY() || playerX != player->GetX()) {
			safeArea->SetItem(false);
		}
		// ���j���[���J������
		else if (player->GetmenuFlag() == true) {
			safeArea->SetItem(false);
		}
		// ���̂܂܂Ȃ�V���b�v���
		else {
			// �������Ƃ�
			if (safeArea->GetBuy() == true) {
				player->BuyItem(safeArea->GetID());
				safeArea->SetBuy(false);
			}
			// �������Ƃ�
			if (safeArea->GetSell() == true) {
				player->SellItem(safeArea->GetNum(), safeArea->GetID());
				safeArea->SetSell(false);
			}
			// ���������̎ʂ�
			for (int i = 0; i < 9; i++) {
				safeArea->SetnumID(i, player->GetID(i));
			}
			// safearea �ɂē���
		}
	}
}