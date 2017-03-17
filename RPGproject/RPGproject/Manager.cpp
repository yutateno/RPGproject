#include "Manager.h"

Manager::Manager() {
	// �ړ��S��
	playerX = 0;		// ��΍��W
	playerY = 0;		// ��΍��W
	playerDamageFlag = false;	// �_���[�W���󂯂Ă��邩�ǂ���
	enemyDamageFlag = false;	// �_���[�W���󂯂Ă��邩�ǂ���
	probability = 200;	// �G���J�E���g����m�� : 1/probability

	// �퓬�֘A
	turn = true;			// true : �v���C���[�̃^�[��
	statusX = 16;			// �R�}���h������Ă�̍��W
	statusY = 16;			// �R�}���h������Ă�̍��W
	preHP = 0;				// ���O��HP
	damage = 0;				// �\���p

	// ���O�֌W
	logCount = 0;			//(�t���[��)�J�E���g
	logTime = 0;			// �\������			
	logX = 8;				// ���O������Ă�̍��W
	logY = 320;				// ���O������Ă�̍��W

	// �Q�[���i�s�֌W
	player = new Player();			// �v���C���[�{��
	endFlag = false;				// �Q�[���I������t���O
	NowScene = eScene::S_Title;		// �ŏ��̉�ʂ��w��
	title = new Title();			// �ŏ��̉�ʂ𐶐�

	// �e�L�X�g�{�b�N�X
	// �X�e�[�^�X
	statusWidth = 112;		// �X�e�[�^�X�̕�
	statusHeight = 96;		// �X�e�[�^�X�̍���
	statusX = 0;			// �X�e�[�^�X�̍��W
	statusY = 0;			// �X�e�[�^�X�̍��W
	// ���O
	logX = 112;				// ���W
	logWidth = 640 - logX;	// ��
	logHeight = 96;			// ����
	logY = 480 - logHeight;	// ���W
}
Manager::~Manager() {
	// ���݂̃V�[�����폜
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

	// �v���C���[�폜
	delete player;
}

void Manager::UpDate() {

	// �y��ʐ؂�ւ��z
	switch (NowScene) {
	case eScene::S_Title://�^�C�g�����
		// �G���h�t���O���������玟�̃V�[���ֈڍs
		if (title->GetEndFlag()) {
			ChengeScene_Title();
		}
		break;

	case eScene::S_Field:// �t�B�[���h���
		if (field->GetEndFlag()) {
			ChengeScene_Field();
		}
		break;

	case eScene::S_Battle:// �퓬���
		if (battle->GetEndFlag()) {
			ChengeScene_Battle();
		}
		break;

	case eScene::S_SafeArea:// ���_���
		if (safeArea->GetEndFlag()) {
			ChengeScene_SafeArea();
		}
		break;

	case eScene::S_Dungeon://�_���W�������
		if (dungeon->GetEndFlag()) {
			ChengeScene_Dungeon();
		}
		break;
	case eScene::S_GameOver://�Q�[���I�[�o�[���
		if (gameOver->GetEndFlag()) {
			ChengeScene_GameOver();
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
	switch (NowScene) {
	case eScene::S_Title://�^�C�g�����
		title->UpDate();
		break;

	case eScene::S_Field:// �t�B�[���h���
		// �t�B�[���h�̏����͒����̂ŕʂ̊֐��֓�������
		FieldProcess();
		break;

	case eScene::S_Battle:// �퓬���
		// �o�g���̏����͒����̂ŕʂ̊֐��֓�������
		BattleProcess();
		break;
		
	case eScene::S_SafeArea:// ���_���
		SafeAreaProcess();
		break;

	case eScene::S_Dungeon://�_���W�������
		DungeonProcess();
		break;

	case eScene::S_GameOver://�Q�[���I�[�o�[���
		gameOver->UpDate();
		break;

	case eScene::S_GameClear://�Q�[���N���A���
		gameClear->UpDate();
		break;

	default:	//Error
		endFlag = true;
		break;
	}
}

// �^�C�g����ʂ���̃V�[���ڍs
void Manager::ChengeScene_Title() {
	// ���̃V�[�����^�C�g������擾���Đݒ�
	NowScene = title->GetNextScene();

	// ���̃V�[���ɂ���ď�����ς���
	switch (NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		// �t�B�[���h����
		field = new Field();

		// �v���C���[�̏����ʒu�ړ�
		player->SetX(64);
		player->SetY(64);
		break;

	case eScene::S_End://�Q�[���I��
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// �^�C�g���폜
	delete title;
}

// �t�B�[���h��ʂ���̃V�[���ڍs
void Manager::ChengeScene_Field() {
	// ���̃V�[�����t�B�[���h����擾
	NowScene = field->GetNextScene();

	// ���̃V�[���ɂ���ď�����ς���
	switch (NowScene) {
	case eScene::S_Battle:// �퓬���
		battle = new Battle();

		// �t�B�[���h��ʂ���ڍs�������Ƃ�ۑ�
		battle->SetReturnScene(eScene::S_Field);

		// �G�̐���
		enemy = new Enemy((int)GetRand(1));
		break;

	case eScene::S_SafeArea:// ���_���
		this->safeArea = new SafeArea();
		// �v���C���[�̏����ʒu�ړ�
		player->SetX(320 - 16);
		player->SetY(480 - 64);
		safeArea->SetMoney(player->GetMoney());
		break;

	case eScene::S_Dungeon://�_���W�������
		dungeon = new Dungeon();
		player->SetX(464);
		player->SetY(864);
		break;

	case eScene::S_End://�Q�[���I��
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// �t�B�[���h��ʎ��̍폜
	delete field;
}

// �퓬��ʂ���̃V�[���ڍs
void Manager::ChengeScene_Battle() {
	// �o�g�����玟�̃V�[�����擾
	NowScene = battle->GetNextScene();

	// ���̃V�[���ɂ���ď�����ύX
	switch (NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		field = new Field();

		// �v���C���[�̏����ʒu��ۑ����Ă�����
		player->SetX(playerX);
		player->SetY(playerY);
		break;

	case eScene::S_SafeArea:// ���_���
		safeArea = new SafeArea();
		safeArea->SetMoney(player->GetMoney());
		break;

	case eScene::S_Dungeon://�_���W�������
		dungeon = new Dungeon();
		break;

	case eScene::S_GameOver://�Q�[���I�[�o�[���
		gameOver = new GameOver();
		break;

	case eScene::S_End://�Q�[���I��
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	logCount = 0;
	logTime = 0;
	turn = true;

	// �G�폜
	delete enemy;

	// �퓬��ʎ��̍폜
	delete battle;
}

// ���_��ʂ���̃V�[���ڍs
void Manager::ChengeScene_SafeArea() {
	// ���̃V�[�����Z�[�t�G���A����擾
	NowScene = safeArea->GetNextScene();

	switch (NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		field = new Field();

		// �v���C���[�̏����ʒu�ړ�
		player->SetX(8 * 32);
		player->SetY(5 * 32);
		break;

	case eScene::S_Battle:// �퓬���
		battle = new Battle();

		// �G����
		enemy = new Enemy(2);

		// ���_��ʂ���ڍs�������Ƃ�ۑ�
		battle->SetReturnScene(eScene::S_SafeArea);
		break;

	case eScene::S_End://�Q�[���I��
		endFlag = true;
		break;

	default:	//Error
		this->endFlag = true;
		break;
	}

	// ���_��ʎ��̍폜
	delete safeArea;
}

// �_���W������ʂ���̃V�[���ڍs
void Manager::ChengeScene_Dungeon() {
	// ���̃V�[�����_���W�����������
	NowScene = dungeon->GetNextScene();

	switch (NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		field = new Field();

		// �v���C���[�̏����ʒu�ړ�
		player->SetX(7 * 32);
		player->SetY(9 * 32);
		break;

	case eScene::S_Battle:// �퓬���
		battle = new Battle();

		// �G����
		// �{�X
		if (dungeon->GetBattle() == true) {
			enemy = new Enemy(3);
		}
		else {
			enemy = new Enemy((int)GetRand(1));
		}

		// �_���W������ʂ���ڍs�������Ƃ�ۑ�
		this->battle->SetReturnScene(eScene::S_Dungeon);
		break;

	case eScene::S_GameClear://�Q�[���N���A���
		this->gameClear = new GameClear();
		break;

	case eScene::S_End://�Q�[���I��
		this->endFlag = true;
		break;

	default:	//Error
		this->endFlag = true;
		break;
	}

	delete dungeon;	// �_���W������ʎ��̍폜
}

// �Q�[���I�[�o�[��ʂ���̃V�[���ڍs
void Manager::ChengeScene_GameOver() {
	// �Q�[���I�[�o�[���玟�̃V�[�����擾
	NowScene = gameOver->GetNextScene();

	switch (NowScene) {
	case eScene::S_Title://�^�C�g�����

		// 

		title = new Title();
		break;

	case eScene::S_End://�Q�[���I��
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// �Q�[���I�[�o�[��ʎ��̍폜
	delete gameOver;
}

// �Q�[���N���A��ʂ���̃V�[���ڍs
void Manager::ChengeScene_GameClear() {
	// �Q�[���N���A���玟�̃V�[�����擾
	NowScene = gameClear->GetNextScene();

	switch (NowScene) {
	case eScene::S_Title://�^�C�g�����
		title = new Title();
		break;

	case eScene::S_End://�Q�[���I��
		endFlag = true;
		break;

	default:	//Error
		endFlag = true;
		break;
	}

	// �Q�[���N���A��ʎ��̍폜
	delete gameClear;
}

void Manager::Draw() {
	// �y�e��ʕ`��z
	switch (NowScene) {
	case eScene::S_Title://�^�C�g�����
		title->Draw();
		break;

	case eScene::S_Field:// �t�B�[���h���
		// �w�i�ƃ}�b�v�`�b�v
		field->Draw();

		// �t�B�[���h�̃X�e�b�v�����C���Ȃ�v���C���[��`��
		if (field->GetStep() == eStep::Main)
		{
			player->aaaDraw(field->GetMapWidth(), field->GetMapHeight());
		}


		break;

	case eScene::S_Battle:// �퓬���
		BattleDraw();
		break;

	case eScene::S_SafeArea:// ���_���

		this->safeArea->Draw();

		//�}�b�v�`�b�v�̓����蔻��
		if (safeArea->GetStep() == eStep::Main) {
			player->aaaDraw(safeArea->GetMapWidth(), safeArea->GetMapHeight());
			safeArea->Draw_UI();
		}
		
		break;

	case eScene::S_Dungeon://�_���W�������
		
		this->dungeon->Draw();
		
		//�}�b�v�`�b�v�̓����蔻��
		if (dungeon->GetStep() == eStep::Main) {
			player->aaaDraw(dungeon->GetMapWidth(), dungeon->GetMapHeight());
			dungeon->Draw_UI();
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
	// ���O�\�������ǂ���
	// �\����
	if (field->GetTreasureFlag())
	{
		if (KeyData::Get(KEY_INPUT_Z) == 1)
		{
			field->SetTreasureFlag(false);
		}
	}
	// �\�����ĂȂ��Ƃ�
	else
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

		// --------------------------------------------------
		// �}�b�v�Ƃ̓����蔻��------------------------------
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
		// --------------------------------------------------


		// --------------------------------------------------
		// �󔠂Ƃ̓����蔻��
		for (int i = 0;i < 2;i++)
		{
			for (int j = 0;j < 2;j++)
			{
				for (int n = 0, m = field->GetTreasureNum();n < m;n++)
				{
					// �ʒu�����Ԃ��Ă����
					if (field->GetTreasureX(n) < (player->GetSpeed() + 1) + player->GetX() + (i * (32 - ((player->GetSpeed() + 1) * 2)))
						&& (player->GetSpeed() + 1) + player->GetX() + (i * (32 - ((player->GetSpeed() + 1) * 2))) < field->GetTreasureX(n) + 32
						&& field->GetTreasureY(n) < (player->GetSpeed() + 1) + player->GetY() + (j * (32 - ((player->GetSpeed() + 1) * 2)))
						&& (player->GetSpeed() + 1) + player->GetY() + (j * (32 - ((player->GetSpeed() + 1) * 2))) < field->GetTreasureY(n) + 32)
					{
						// �ʂ蔲���֎~
						player->MoveReset();
					}
					// �ʒu�����Ԃ��Ă����
					if (field->GetTreasureX(n) < player->GetX() + (i * 32)
						&& player->GetX() + (i * 32) < field->GetTreasureX(n) + 32
						&& field->GetTreasureY(n) < player->GetY() + (j * 32)
						&& player->GetY() + (j * 32) < field->GetTreasureY(n) + 32)
					{
						// �A�C�e���ɋ󂫂������
						if (KeyData::Get(KEY_INPUT_Z) == 1 && player->BuyItem(0))
						{
							player->BuyItem(field->OpenTreasure(n));
						}
					}
				}
			}
		}
		// --------------------------------------------------
		// --------------------------------------------------
	}
}

void Manager::BattleProcess()
{
	switch (battle->GetStep())
	{
	case eStep::Start:
		// �R�}���h���̏���
		battle->UpDate();
		break;

	case eStep::Main:
		// �퓬����
		if (enemy->GetHP() <= 0)
		{
			if (logCount < logTime)
			{
				// �J�E���g
				logCount++;
			}
			else
			{
				// ������
				logCount = 0;
				logTime = 0;
				// �t���O��܂�
				battle->SetDamageFlag(false);

				// �퓬��V
				player->SetEXP(player->GetEXP() + enemy->GetEXP());				// �o���l
				player->SetMoney(player->GetMoney() + enemy->GetMoney());		// ����

				// �\������
				logTime = 180;

				// ���x���A�b�v
				if (player->GetEXP() > player->GetLV() * 20)
				{
					logTime += 180;
					// �J�z����^����
					player->SetEXP(player->GetEXP() - player->GetLV() * 20);
					// ���x�����グ��
					player->SetLV(player->GetLV() + 1);
					// �X�e�[�^�X�㏸
					player->SetMaxHP(player->GetMaxHP() + player->GetLV());
					player->SetMaxMP(player->GetMaxMP() + player->GetLV());
					player->SetPower(player->GetPower() + player->GetLV());
				}

				// �o�g���̃X�e�b�v�i�s
				battle->SetStep(eStep::End);
			}
		}
		// �퓬�s�k
		else if (player->GetHP() <= 0)
		{
			// ���O�o��
			if (logCount > 0)
			{
				if (logCount < logTime)
				{
					// �J�E���g
					logCount++;
				}
				else
				{
					// ������
					logCount = 0;
					logTime = 0;
					// �t���O��܂�
					battle->SetDamageFlag(false);

					// �Q�[���I�[�o�[��ʂ�
					battle->SetNextScene(eScene::S_GameOver);

					// �o�g���̃X�e�b�v�i�s
					battle->SetStep(eStep::End);
				}
			}
		}
		else
		{
			// �����̃^�[��
			if (turn)
			{
				// ���O�o��
				if (logCount > 0)
				{
					if (logCount < logTime)
					{
						// �J�E���g
						logCount++;
					}
					else
					{
						// ������
						logCount = 0;
						logTime = 0;

						// �t���O��܂�
						battle->SetDamageFlag(false);
						// �����ĂɃ^�[����n��
						turn = false;
					}
				}
				else
				{
					// �R�}���h���̏���
					battle->UpDate();

					// battle����_���[�W��^����w�����󂯂���
					if (battle->GetDamageFlag())
					{
						// �J�E���g�A�b�v
						logCount++;
						// �\������
						logTime = 120;
						switch (battle->GetCommand())
						{
						case NEUTRAL:			// �����Ȃ�
							break;

						case ATTACK:
							player->SetATKName("�U��");
							break;

						case MAGIC:
							// MP����
							if (player->GetMP() > 0)
							{
								player->SetATKName("���@�U��");
								player->SetMP(player->GetMP() - 1);
							}
							// MP������Ȃ��ꍇ
							else
							{
								battle->SetDamageFlag(false);			// �t���O��܂�
								battle->SetCommand(NEUTRAL);			// �o�g���̃R�}���h�����ɖ߂�
								return;
							}
							break;

						case RUN_AWAY:
							break;

						default:
							break;
						}

						//�_���[�W����
						player->SetATK(battle->GetDamageWidth());		// �I�������s���𔽉f����
						preHP = enemy->GetHP();							// ���O��HP
						damage = enemy->GetHP() - player->GetATK();		// �_���[�W���󂯂����Ƃ�HP
						enemy->SetHP(damage);							// �_���[�W
						enemyDamageFlag = true;							// �_���[�W�t���O�𗧂Ăĉ��o
					}
				}
			}
			// ����̃^�[��
			else
			{
				// ���O�o��
				if (logCount > 0)
				{
					if (logCount < logTime)
					{
						// �J�E���g
						logCount++;
					}
					else
					{
						// ������
						logCount = 0;
						logTime = 0;

						// �o�g���̃R�}���h��߂�
						battle->SetCommand(NEUTRAL);
						// �v���C���[�Ƀ^�[����n��
						turn = true;
					}
				}
				else
				{
					// �J�E���g�A�b�v
					logCount++;
					// �\������
					logTime = 120;

					// �U�������ƃ_���[�W
					enemy->AttackProcess();			// �U���̏���
					preHP = player->GetHP();		// ���O��HP
					damage = player->GetHP() - enemy->GetATK();	// �_���[�W�ۑ�
					player->SetHP(damage);			// �U���͕������_���[�W
					playerDamageFlag = true;		// �_���[�W�t���O�𗧂Ăĉ��o
				}
			}
		}
		break;

	case eStep::End:
		// ���o���ł͂Ȃ����
		if (logCount < logTime)
		{
			// �J�E���g�A�b�v
			logCount++;
		}
		else
		{
			battle->UpDate();
		}
		break;

	default:
		// �G���[
		break;
	}
}
void Manager::BattleDraw()
{
	// �X�e�b�v�ɂ���ĕ\���𕪂���
	switch (battle->GetStep())
	{
	case eStep::Start:
		// ���X�ɉ�ʂ̕\�����鏈��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, battle->GetCount() * 3);
		// �w�i
		battle->Draw();
		// �G
		enemy->aaaDraw();
		// �u�����h���[�h�̌㏈��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// �X�e�[�^�X
		Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
			player->GetName() + "\n" +
			"HP:" + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()) + "\n" +
			"MP:" + std::to_string(player->GetMP()) + " / " + std::to_string(player->GetMaxMP()) + "\n" +
			"LV:" + std::to_string(player->GetLV()));
		// �R�}���h
		battle->Draw_Command();
		// ���O
		Textbox::Draw(logX, logY, logWidth, logHeight, "");

		// ���O
		Textbox::Draw(logX, logY, enemy->GetName() + " �������ꂽ�I");
		break;

	case eStep::Main:
		// �w�i
		battle->Draw();
		// �X�e�[�^�X
		Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
			player->GetName() + "\n" +
			"HP:" + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()) + "\n" +
			"MP:" + std::to_string(player->GetMP()) + " / " + std::to_string(player->GetMaxMP()) + "\n" +
			"LV:" + std::to_string(player->GetLV()));
		// �R�}���h
		battle->Draw_Command();
		// ���O
		Textbox::Draw(logX, logY, logWidth, logHeight, "");

		// �_���[�W���o
		if (logCount > 60 && turn)
		{
			if (logCount % 5 == 0)
			{
				// �G
				enemy->aaaDraw();
			}
		}
		else
		{
			// �G
			enemy->aaaDraw();
		}

		// �_���[�W�\��
		if (battle->GetDamageFlag())
		{
			// ���O
			Textbox::Draw(logX, logY, player->GetName() + " �� " + player->GetATKName() + " !");
			if (logCount > 60)
			{
				Textbox::Draw(logX, logY + 16, enemy->GetName() + " �� " + to_string(preHP - damage) + " �̃_���[�W�I");
			}
		}
		if (!turn)
		{
			// ���O
			Textbox::Draw(logX, logY, enemy->GetName() + " �� " + enemy->GetATKName() + " !");
			if (logCount > 60)
			{
				Textbox::Draw(logX, logY + 16, player->GetName() + " ��" + to_string(preHP - damage) + " �̃_���[�W�I");
			}
		}
		break;

	case eStep::End:
		// ����
		if (enemy->GetHP() <= 0)
		{
			// �w�i
			battle->Draw();

			// ���X�ɉ�ʂ̕\�����鏈��
			if (logCount < 60)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - logCount * ((int)255 / 60));
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
			}
			// �G
			enemy->aaaDraw();
			// �u�����h���[�h�̌㏈��
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// �X�e�[�^�X
			Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
				player->GetName() + "\n" +
				"HP:" + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()) + "\n" +
				"MP:" + std::to_string(player->GetMP()) + " / " + std::to_string(player->GetMaxMP()) + "\n" +
				"LV:" + std::to_string(player->GetLV()));
			// �R�}���h
			battle->Draw_Command();
			// ���O
			Textbox::Draw(logX, logY, logWidth, logHeight, "");

			// ���O
			Textbox::Draw(logX, logY,enemy->GetName() + " ��|�����I");
			if (logCount > 60)
			{
				Textbox::Draw(logX, logY + 16, to_string(enemy->GetEXP()) + " �̌o���l���l���I");
			}
			if (logCount > 120)
			{
				Textbox::Draw(logX, logY + 32, to_string(enemy->GetMoney()) + " �S�[���h����ɓ��ꂽ�I");
			}
			// ���x���A�b�v
			if (logCount > 180)
			{
				Textbox::Draw(logX, logY, logWidth, logHeight, "���x���A�b�v�I");
			}
			if (logCount > 240)
			{
				Textbox::Draw(logX, logY + 16, player->GetName() + " �� LV" + to_string(player->GetLV()) + " �ɂȂ����I");
			}
			if (logCount > 300)
			{
				Textbox::Draw(logX, logY + 32, "�X�e�[�^�X���オ�����I");
			}
		}
		// �s�k
		else if (player->GetHP() <= 0)
		{
			// ���X�ɉ�ʂ̕\�����鏈��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - battle->GetCount() * 3);
			// �w�i
			battle->Draw();
			// �G
			enemy->aaaDraw();
			// �u�����h���[�h�̌㏈��
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// �X�e�[�^�X
			Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
				player->GetName() + "\n" +
				"HP:" + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()) + "\n" +
				"MP:" + std::to_string(player->GetMP()) + " / " + std::to_string(player->GetMaxMP()) + "\n" +
				"LV:" + std::to_string(player->GetLV()));
			// �R�}���h
			battle->Draw_Command();
			// ���O
			Textbox::Draw(logX, logY, logWidth, logHeight, "");

			// ���O
			Textbox::Draw(logX, logY, "���Ȃ��͎���ł��܂����E�E�E");
		}
		break;

	default:
		// �G���[
		break;
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
			switch (dungeon->GetMapData(player->GetX() + (i * 31), player->GetY() + (j * 31)))
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

	// �󔠂Ƃ̓����蔻��
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0, m = dungeon->GetTreasureNum(); k < m; k++)
			{
				// �Ԃ����Ă�����
				if (dungeon->GetTreasureX(k) < player->GetX() + (i * 32)			// ��
					&& player->GetX() + (i * 32) < dungeon->GetTreasureX(k) + 32	// �E
					&& dungeon->GetTreasureY(k) < player->GetY() + (j * 32)			// ��
					&& player->GetY() + (j * 32) < dungeon->GetTreasureY(k) + 32) {	// ��
					// �ђʂ����Ȃ�
					player->MoveReset();
					// Z����������
					if (KeyData::Get(KEY_INPUT_Z) == 1) {
						// �󔠂ɔ���������
						dungeon->SetTreasure(true);
						// 0���������炿���Ɣ��킹��
						if (player->BuyItem(0)) {
							player->BuyItem(dungeon->OpenTreasure(k));
							dungeon->SetOpen(true);
						}
						// ���������ꂽ��
						else if (dungeon->GetTreasureMoney() != 0) {
							dungeon->OpenTreasure(k);
							dungeon->SetOpen(true);
						}
						// 0�������Ȃ������ɂ���������Ȃ�������
						else {
							dungeon->SetOpen(false);
						}
						// ����������
						player->SetMoney(player->GetMoney() + dungeon->GetTreasureMoney());
					}
				}
			}
		}
	}

	// �{�X�ɐG�ꂽ��
	if (dungeon->GetBoss() == true) {
		// ��������L�����Z��
		if (playerY != player->GetY() || playerX != player->GetX()) {
			dungeon->SetBoss(false);
		}
		// ���j���[��ʂ��J������
		else if (player->GetmenuFlag() == true) {
			dungeon->SetBoss(false);
		}
		// ���̂܂܂Ȃ�퓬
		else {
			if (KeyData::Get(KEY_INPUT_Z) == 1) {
				dungeon->SetBattle(true);
			}
		}
	}
	
	/*// �G�Ƃ̃G���J�E���g
	if ((player->GetX() != playerX || player->GetY() != playerY) && player->GetmenuFlag() == false)
	{
		if (GetRand(probability) == 0)
		{
			dungeon->SetBattle(true);
		}
	}*/

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
	// �Z�[�t�G���A�̏���
	safeArea->UpDate(player->GetX(), player->GetY());

	// �v���C���[�̂����̓�����ǐՂ��Ĕ��f
	player->SetMoney(safeArea->GetMoney());

	// �V���b�v�̔����ʂł��\�[�g���������̂�
	player->ItemSort();

	// �v���C���[�����������ǂ����𔻒f���邽�߂ɒ��O�̍��W��ۑ�
	playerX = player->GetX();
	playerY = player->GetY();
	
	// ����������Ńv���C���[�{�̂̃v���Z�X���~
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
				// �w������
				if (player->BuyItem(0)) {
					safeArea->SetSuccess(true);
					player->BuyItem(safeArea->GetID());
				}
				// �w�����s
				else {
					safeArea->SetSuccess(false);
				}
				safeArea->SetBuy(false);
			}
			// �������Ƃ�
			if (safeArea->GetSell() == true) {
				player->SellItem(safeArea->GetItemPosition());
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