#include "LoadingStage.h"
#include "GameStage.h"
#include "ArmatureLoader.h"
#include "PlayerAccount.h"

USING_NS_CC;

CLoadingStage::CLoadingStage(void)
{
}


CLoadingStage::~CLoadingStage(void)
{
}

CCScene* CLoadingStage::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    CLoadingStage *layer = CLoadingStage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void CLoadingStage::onEnter()
{
    CCLayer::onEnter();
    
    ArmatureLoader::GetInstance()->LoadArmatureWithFile("ani/armature.plist");
    CPlayerAccount::GetAccountInstance()->AddPlayerAccountProps(ROLEID_FIREAXE, 10);
    CPlayerAccount::GetAccountInstance()->AddPlayerAccountProps(ROLEID_ICEAXE, 10);

    CCScene *scene = CGameStage::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void CLoadingStage::onExit()
{
    CCLayer::onExit();
}