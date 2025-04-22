#include "GameScene.h"
#include "Player.h"
#include "ArrowPool.h"
#include "UIController.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 screenCenter = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);


    UIController* uiController = UIController::create();
    uiController->setScene(this);
    addChild(uiController);

    //Player init
    {
        auto  player = Player::create();
        player->setPosition(screenCenter);
        addChild(player);
    }
    
    scheduleUpdate();

    return true;
}

void GameScene::update(float dt)
{
    static float timer = 0;
    timer += dt;

    if (timer > 5)
    {
        timer = 0;

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 screenCenter = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

        ArrowPool::getInstance().Pop(screenCenter,Vec2::UNIT_X * - 1 , 400);
    }

}

