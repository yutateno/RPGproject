#pragma once

#include <string>

using std::string;

class Item
{
private:
	int ID;				// �Ǘ��ԍ�
	string name;		// ���O

public:
	Item();
	Item(int ID);
	~Item();

	string SearchName(int ID);		// �Ǘ��ԍ����疼�O����������֐�

	// �Q�b�^�[�Z�b�^�[
	string GetName();
};