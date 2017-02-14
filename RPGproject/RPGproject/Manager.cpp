#include "Manager.h"

Manager::Manager() {

	player = new Player();
	this->endFlag = false;
	this->NowScene = eScene::S_Title;
	this->title = new Title();
}
Manager::~Manager() {
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
		this->field->UpDate();
		player->Move();
		break;
	case eScene::S_Battle:// �퓬���
		this->battle->UpDate();
		break;
	case eScene::S_SafeArea:// ���_���
		this->safeArea->UpDate();
		break;
	case eScene::S_Dungeon://�_���W�������
		this->dungeon->UpDate();
		player->Move();
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
		// �t�B�[���h��ʂ���ڍs�������Ƃ�ۑ�
		this->battle->SetReturnScene(eScene::S_Field);
		break;
	case eScene::S_SafeArea:// ���_���
		this->safeArea = new SafeArea();
		delete this->field;	// �t�B�[���h��ʎ��̍폜
		break;
	case eScene::S_Dungeon://�_���W�������
		this->dungeon = new Dungeon();
		player->SetX(0);
		player->SetY(0);
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
	InitGraph();	// �S�O���t�B�b�N�폜
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
}

// ���_��ʂ���̃V�[���ڍs
void Manager::ChengeScene_SafeArea() {
	InitGraph();	// �S�O���t�B�b�N�폜
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
	InitGraph();	// �S�O���t�B�b�N�폜
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
	InitGraph();	// �S�O���t�B�b�N�폜
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
	InitGraph();	// �S�O���t�B�b�N�폜
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
		player->aaaDraw();
		break;
	case eScene::S_Battle:// �퓬���
		this->battle->Draw();
		break;
	case eScene::S_SafeArea:// ���_���
		this->safeArea->Draw();
		break;
	case eScene::S_Dungeon://�_���W�������
		this->dungeon->Draw();
		player->aaaDraw();
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