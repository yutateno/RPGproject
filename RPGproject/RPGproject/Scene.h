#pragma once
#include "Manager.h"

// �V�[���̗�
enum class eScene : __int8 {
	S_Title,	// �^�C�g��
	S_Field,	// �t�B�[���h
	S_Battle,	// �퓬
	S_SafeArea,	// ���Ƃ��̋��_
	S_Dungeon,	// �_���W����
	S_GameClear,// �Q�[���N���A
	S_GameOver,	// �Q�[���I�[�o�[
	S_End		// �Q�[���I��
};

// �V�[�����̒i�K
enum class eStep : __int8 { Start, Main, End};

class SuperScene {
protected:
	bool endFlag;	// �V�[���I���t���O true�ŏI��

	eScene nextScene;	// ���̃V�[���y�󂯓n���p�z

	eStep step;		// 0:�J�n	1:���C��	2:�I��
	int startCount;	// �J�n��ʂ̃J�E���g
	int endCount;	// �I����ʂ̃J�E���g
	
public:
	SuperScene();
	~SuperScene();

	virtual void UpDate() = 0;	// �A�b�v�f�[�g
	void UpDate_Start() {};	// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main() {};	// ���C����ʃA�b�v�f�[�g
	void UpDate_End() {};	// �I����ʃA�b�v�f�[�g

	virtual void Draw() = 0;// �`��
	void Draw_Start() {};	// �J�n��ʕ`��
	void Draw_Main() {};	// ���C����ʕ`��
	void Draw_End() {};		// �I����ʕ`��

	bool GetEndFlag();
	eScene GetNextScene();
};