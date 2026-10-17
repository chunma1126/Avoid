
#pragma once

#include "cocos2d.h"


class Joystick : public cocos2d::Node
{
    
public:
    static Joystick* create(cocos2d::Point pos);
    void setOnActiveChange(const std::function<void()> &func);

    float getDirection() const;
    bool getIsActive() const;

    void setJoystickRadius(float radius);
    float getIntensity();
private:
    virtual bool init();
    
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    void setIsActive(bool active);
    
    std::function<void ()> _onActiveChange;
    
    void joystickBoundaryUpdate();
    
    cocos2d::Point _mainPosition;
    cocos2d::Sprite *_joystickSprite = nullptr;
    cocos2d::Sprite *_bgSprite = nullptr;
    
    float _radiusSq = 16000.0f;
    int _touchToTrack = 0;
    bool _isActive = false;
    bool _didSetChangeCommand = false;
};

