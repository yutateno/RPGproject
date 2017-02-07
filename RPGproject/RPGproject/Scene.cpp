#include "Manager.h"

SuperScene::SuperScene() {

}
SuperScene::~SuperScene() {

}

bool SuperScene::GetEndFlag(){
	return this->endFlag;
}

eScene SuperScene::GetNextScene() {
	return this->nextScene;
}