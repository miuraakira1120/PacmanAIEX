#include "PlayScene.h"
#include "Stage.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "Akabei.h"
#include "Aosuke.h"
#include "Pinky.h"
#include "Guzuta.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<Akabei>(this);
	Instantiate<Aosuke>(this);
	Instantiate<Pinky>(this);
	Instantiate<Guzuta>(this);
}


//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}