#include "GameScene.h"
#include "Player.h"
#include "UIController.h"
#include "ArrowPattern.h"

#include "RightAndLeftPattern.h"
#include "SectorPattern.h"
#include "SquarePattern.h"
#include "ForkPattern.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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
    if (!Scene::init())
    {
        return false;
    }

    //pattern init
    {
        auto r = new RightAndLeftPattern;
        auto r1 = new SectorPattern;
        auto r2 = new SquarePattern;
        auto r3 = new ForkPattern;

        _patternQueue.push(r);
        _patternQueue.push(r1);
        _patternQueue.push(r2);
        _patternQueue.push(r3);

    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 screenCenter = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    
    //UI Controller
    UIController* uiController = UIController::create();
    uiController->setScene(this);
    addChild(uiController);
     

    //Player init
    {
        auto player = Player::create();
        player->setPosition(screenCenter);
        
        player->getHealthComponent().onDamageEvents.add([uiController]() { uiController->playBloodScreen(); });
        player->getHealthComponent().onDamageEvents.add([uiController, player]() {
            uiController->setHealthBar(player->getHealthComponent().getPercent());
            });

        player->getHealthComponent().onHealEvents.add([uiController, player]() {
            uiController->setHealthBar(player->getHealthComponent().getPercent());
            });



        addChild(player);
    }
    
    scheduleUpdate();

    return true;
}

void GameScene::update(float dt)
{

    if (_patternQueue.empty() && currentPattern == nullptr)//game clear!
    {
        CCLOG("game is over!!!");
    }
    else if (currentPattern == nullptr)//next patterb
    {
        currentPattern = _patternQueue.front();
        _patternQueue.pop();
        currentPattern->start();
    }
    else//check complete and pattern update
    {
        if (currentPattern->isCompleted())
        {
            currentPattern->reset();

            delete currentPattern;
            currentPattern = nullptr;
        }
        else {
            currentPattern->update(dt);
        }
    }

}

