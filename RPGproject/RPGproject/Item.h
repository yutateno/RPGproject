#pragma once

#include <string>

using std::string;

class Item
{
private:
	int ID;						// �Ǘ��ԍ�
	string name;				// ���O
	int price;					// �l�i
	string effectText[2];		// ���ʂ̃e�L�X�g

public:
	Item();
	Item(int ID);
	~Item();

	string SearchName(int ID);			// �Ǘ��ԍ����疼�O����������֐�
	int SearchPrice(int ID);			// �Ǘ��ԍ�����l�i����������֐�
	string SearchEffectText(int ID, bool effected);	// �Ǘ��ԍ�������ʂ���������֐�

	// �Q�b�^�[�Z�b�^�[
	string GetName();
	int GetID();
	int GetPrice();
	string GetEffectText(bool effected);
};