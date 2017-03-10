#include "Manager.h"

Manager::Manager() {
	// �ړ��S��
	playerX = 0;		// ��΍��W
	playerY = 0;		// ��΍��W
	probability = 200;	// �G���J�E���g����m�� : 1/probability
	drop = 200;			// �G���A�C�e���𗎂Ƃ��m�� : item/drop

	// �퓬�֘A
	turn = true;			// true : �v���C���[�̃^�[��
	logCount = 120;			// ���o����
	count = 0;				// ���o�p��(�t���[��)���ԃJ�E���g
	preHP = 0;				// ���O�̂g�o
	preStep = eStep::Start;	// ���O�̃X�e�b�v
	lose = false;			// �퓬�ɔs�k�������Bfalse:���ĂȂ�
	statusX = 16;			// �R�}���h������Ă�̍��W
	statusY = 16;			// �R�}���h������Ă�̍��W
	logX = 8;				// ���O������Ă�̍��W
	logY = 320;				// ���O������Ă�̍��W
	logNum = 4;				// �P�y�[�W�ɉ��s�\�����邩

	// �Q�[���i�s�֌W
	player = new Player();			// �v���C���[�{��
	endFlag = false;				// �Q�[���I������t���O
	NowScene = eScene::S_Title;		// �ŏ��̉�ʂ��w��
	title = new Title();			// �ŏ��̉�ʂ𐶐�
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

		// ���O�̃X�e�b�v��ۑ�
		preStep = battle->GetStep();

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
		player->SetX(320 - 16);
		player->SetY(240 - 16);
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

		// ���o�p�̕ϐ�������
		count = 0;

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
	// �퓬�Ŕs�k�������ǂ����Ŏ��̃V�[����ύX
	// �s�k�����ꍇ
	if (lose)
	{
		NowScene = eScene::S_GameOver;
	}
	// ���������ꍇ
	else
	{
		// �o�g�����玟�̃V�[�����擾
		NowScene = battle->GetNextScene();
	}

	// ���̃V�[���ɂ���ď�����ύX
	switch (this->NowScene) {
	case eScene::S_Field:// �t�B�[���h���
		field = new Field();

		// �v���C���[�̏����ʒu��ۑ����Ă�����
		player->SetX(playerX);
		player->SetY(playerY);
		break;

	case eScene::S_SafeArea:// ���_���
		safeArea = new SafeArea();
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
		player->SetX(320 - 16);
		player->SetY(240 - 16);
		break;

	case eScene::S_Battle:// �퓬���
		battle = new Battle();

		// ���o�p�̕ϐ��̏�����
		count = 0;

		// �G����
		enemy = new Enemy();

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
		player->SetX(320 - 16);
		player->SetY(240 - 16);
		break;

	case eScene::S_Battle:// �퓬���
		battle = new Battle();

		// ���o�p�ϐ���������
		count = 0;

		// �G����
		enemy = new Enemy();

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

	// �s�k�t���O��܂�
	lose = false;

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
		}

		safeArea->Draw_UI();
		
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
	switch (battle->GetStep())
	{
	case eStep::Start:
		// �J�E���g�A�b�v
		count++;

		// ���O����
		if (count == 1)
		{
			log.push_back(enemy->GetName() + " �����ꂽ�I");
		}

		battle->UpDate();
		break;

	case eStep::Main:
		// ���o���łȂ���Α�����󂯕t����
		if (count == 0)
		{
			battle->UpDate();
		}

		// �퓬����
		if (enemy->GetHP() <= 0)
		{
			if (count < logCount)			// ���O��X�t���[���\������
			{
				// �J�E���g�A�b�v
				count++;

				// ���O����
				if (count == 1)
				{
					log.push_back(enemy->GetName() + " ��|�����I");
					log.push_back("��������I");
					log.push_back("�������I");
					log.push_back("��J���J���J���J�I�J");
					log.push_back(to_string(enemy->GetEXP()) + " �̌o���l���l���I");
				}
			}
			else
			{
				// ���l��
				player->SetMoney(player->GetMoney() + enemy->GetMoney());

				// �o���l�̏���
				player->SetEXP(player->GetEXP() + enemy->GetEXP());

				// �m���ŃA�C�e������
				int luck = GetRand(drop);
				if (luck == 0)
				{
					// ���E���̃n����
					player->BuyItem(5);
				}
				else if (luck < (4 + 1))
				{
					// ���ނ�_�}����
					player->BuyItem(4);
				}
				else if (luck < (16 + 1))
				{
					// ���炩�Ȑ�����
					player->BuyItem(3);
				}
				else if (luck < (64 + 1))
				{
					// �₭(�ɂ���������)��������
					player->BuyItem(2);
				}

				// ���x���A�b�v�̏���
				if (player->GetLV() * 20 < player->GetEXP())
				{
					log.push_back("���x���A�b�v�I");
					log.push_back(player->GetName() + " ��" + to_string(player->GetLV()) + " �ɂȂ����I");

					player->SetEXP(player->GetEXP() - (player->GetLV() * 20));	// �o���l��0�ɂ���
					player->SetLV(player->GetLV() + 1);							// ���x�����P�グ��
					player->SetMaxHP(player->GetMaxHP() + player->GetLV());		// HP�㏸
					player->SetMaxMP(player->GetMaxMP() + player->GetLV());		// MP�㏸

					log.push_back("���x���A�b�v�I");
					log.push_back(player->GetName() + " ��" + to_string(player->GetLV()) + " �ɂȂ����I");
				}

				
				// �o�g���̃X�e�b�v�i�s
				battle->SetStep(eStep::End);
			}
		}
		// �퓬�s�k
		else if (player->GetHP() <= 0)
		{
			if (count < logCount)			// ���O��X�t���[���\������
			{
				// �J�E���g�A�b�v
				count++;

				// ���O����
				if (count == 1)
				{
					log.push_back("�s�k");
				}
			}
			else
			{
				// �J�E���g���Z�b�g
				count = 0;
				// �s�k�t���O�𗧂Ă�
				lose = true;
				// �o�g���̃X�e�b�v�i�s
				battle->SetStep(eStep::End);
			}
		}
		else
		{
			// �����̃^�[��
			if (turn)
			{
				// battle����_���[�W��^����w�����󂯂���
				if (battle->GetDamageFlag())
				{
					// ���o���ł͂Ȃ��Ƃ�
					if (count == 0)
					{
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
								count = 0;								// �J�E���g��߂�
								return;
							}
							break;

						case RUN_AWAY:
							break;

						default:
							break;
						}
					}

					// ���o��
					if (count < logCount)			// ���O��X�t���[���\������
					{
						// �J�E���g�A�b�v
						count++;

						// ���O����
						if (count == 1)
						{
							log.push_back(player->GetName() + " ��" + player->GetATKName() + " �I");
						}

						// ���o�Ɠ������ă_���[�W
						if (count == 60)
						{
							//�_���[�W����
							player->SetATK(battle->GetDamageWidth());			// �I�������s���𔽉f����
							enemy->SetHP(enemy->GetHP() - player->GetATK());	// �_���[�W

							// ���O����
							log.push_back(enemy->GetName() + " ��" + to_string(preHP - enemy->GetHP()) + " �_���[�W�I");
						}
					}
					else
					{
						// �J�E���g���Z�b�g
						count = 0;

						battle->SetDamageFlag(false);			// �t���O��܂�
						battle->SetCommand(NEUTRAL);			// �o�g���̃R�}���h��߂�
						count = 0;								// �J�E���g��߂�
						turn = false;							// �����ĂɃ^�[����n��
					}
				}
			}
			// ����̃^�[��
			else
			{
				// ���o��
				if (count < logCount)			// ���O��X�t���[���\������
				{
					// �J�E���g�A�b�v
					count++;

					// ���O����
					if (count == 1)
					{
						log.push_back(enemy->GetName() + " ��" + enemy->GetATKName() + " �I");
					}

					// ���o�Ɠ������ă_���[�W
					if (count == 60)
					{
						enemy->AttackProcess();
						player->SetHP(player->GetHP() - enemy->GetATK());		// �U���͕������_���[�W

						// ���O����
						log.push_back(player->GetName() + " ��" + to_string(preHP - player->GetHP()) + " �_���[�W�I");
					}
				}
				else
				{
					count = 0;			// �J�E���g��߂�
					turn = true;		// �v���C���[�Ƀ^�[����n��
				}
			}
		}
		break;

	case eStep::End:
		// �J�E���g�A�b�v
		count++;

		battle->UpDate();
		break;

	default:
		// �G���[
		break;
	}

	// �X�e�b�v�ύX�Ŋe�탊�Z�b�g
	if (preStep != battle->GetStep())
	{
		count = 0;
		log.clear();
	}
}
void Manager::BattleDraw()
{
	// �w�i
	battle->Draw();

	// �X�e�b�v�ɂ���ĕ\���𕪂���
	switch (battle->GetStep())
	{
	case eStep::Start:
		// ���X�ɉ�ʂ̕\�����鏈��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, battle->GetCount() * 3);

		// �G
		enemy->aaaDraw();

		// �u�����h���[�h�̌㏈��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;

	case eStep::Main:
		// �����Ă����
		if (enemy->GetHP() > 0)
		{
			if (turn)
			{
				// �_���[�W�H������Ƃ�
				if (count < 60 || count % 5 == 0)
				{
					enemy->aaaDraw();
				}
			}
			else
			{
				enemy->aaaDraw();
			}
		}

		// �v���C���[�̃X�e�[�^�X
		// �X�e�[�^�X�w�i
		DrawBox(statusX, statusY, statusX + 120, statusY + 120, BLACK, true);
		DrawBox(statusX, statusY, statusX + 120, statusY + 120, WHITE, false);

		if (turn)
		{
			DrawFormatString(statusX + 24, statusY + 24, WHITE, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());
		}
		else
		{
			// �_���[�W�H������Ƃ�
			if (count > 60)
			{
				DrawFormatString(statusX + 24 + GetRand(8) - GetRand(8), statusY + 24 + GetRand(8) - GetRand(8), RED, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());
			}
			// �H����ĂȂ��Ƃ�
			else
			{
				DrawFormatString(statusX + 24, statusY + 24, WHITE, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", player->GetName().c_str(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetLV());
			}
		}
		break;

	case eStep::End:
		// Manager�ŕ\�����ׂ����̂͂Ȃ�
		break;

	default:
		// �G���[
		break;
	}

	// ���O
	// �R�}���h�I�𒆂Ȃ�\�����Ȃ�
	if (battle->GetStep() == eStep::Main&&turn&&count == 0)
	{
		battle->Draw_Command();
	}
	// ���o���Ȃ�\��
	else
	{
		// ���O�w�i
		DrawBox(logX, logY, logX + 600, logY + 150, BLACK, true);
		DrawBox(logX, logY, logX + 600, logY + 150, WHITE, false);
		// ���O�o��
		// ��y�[�W�𒴂��Ă�����
		if (log.size() > logNum)
		{
			// �\��
			for (int i = 0, n = logNum;i < n;i++)
			{
				DrawFormatString(logX + 32, logY + 32 + (i * 32), WHITE, log[i].c_str());
			}

			// �\�����ԏI���ň�y�[�W�폜
			if (count == logCount)
			{
				log.erase(log.begin(), log.begin() + 4);
			}
		}
		else
		{
			// �\��
			for (int i = 0, n = log.size();i < n;i++)
			{
				DrawFormatString(logX + 32, logY + 32 + (i * 32), WHITE, log[i].c_str());
			}

			// �\�����ԏI���ň�y�[�W�폜
			if (count == logCount)
			{
				log.clear();
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
	// �Z�[�t�G���A�̏���
	safeArea->UpDate(player->GetX(), player->GetY());

	// �v���C���[�̂����̓�����ǐՂ��Ĕ��f
	player->SetMoney(safeArea->GetMoney());

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
				if (player->BuyItem(safeArea->GetID()))
				{
					// �w������
				}
				else
				{
					// �w�����s
					safeArea->Refund();
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