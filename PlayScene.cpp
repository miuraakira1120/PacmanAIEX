#include "PlayScene.h"
#include "Stage.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "Akabei.h"
#include "Aosuke.h"
#include "Pinky.h"
#include "Guzuta.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<Akabei>(this);
	Instantiate<Aosuke>(this);
	Instantiate<Pinky>(this);
	Instantiate<Guzuta>(this);
}


//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}