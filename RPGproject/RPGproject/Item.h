#pragma once

#include <string>

using std::string;

class Item
{
private:
	int ID;				// �Ǘ��ԍ�
	string name;		// ���O
	int price;			// �l�i

public:
	Item();
	Item(int ID);
	~Item();

	string SearchName(int ID);		// �Ǘ��ԍ����疼�O����������֐�
	int SearchPrice(int ID);		// �Ǘ��ԍ�����l�i����������֐�

	// �Q�b�^�[�Z�b�^�[
	string GetName();
	int GetID();
};