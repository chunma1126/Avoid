#pragma once

#include "cocos2d.h"



class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void update(float dt);
    CREATE_FUNC(GameScene);

    void setPhysicsWorld(cocos2d::PhysicsWorld* world) { physicsWorld = world; }
private:
    cocos2d::PhysicsWorld* physicsWorld;

};

