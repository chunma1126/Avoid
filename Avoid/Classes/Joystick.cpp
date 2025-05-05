//
//  Joystick.cpp
//  modules
//
//  Created by Bilal Mirza on 02/01/2018.
//
//

#include "Joystick.h"

USING_NS_CC;

namespace{
    const float BOUNDARY_DISTANCE = 50;
}
Joystick* Joystick::create(Point pos)
{
    Joystick *node = new (std::nothrow)Joystick();
    if(node )
    {
        node->_mainPosition = pos;
        node->init();
        node->autorelease();
        return node;
    }
    
    CC_SAFE_DELETE(node);
    return nullptr;
}


bool Joystick::init()
{

    setJoystickRadius(400);
    _joystickSprite = Sprite::create("dpadmid.png");
    this->addChild(_joystickSprite);
    _joystickSprite->setVisible(false);
    _joystickSprite->setPosition(_mainPosition);
    
    
    _bgSprite = Sprite::create("dpadbase.png");
    this->addChild(_bgSprite);
    _bgSprite->setPosition(_mainPosition);
    
    
    auto listener = EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
    listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    
    
    return true;
}

void Joystick::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    for(int i = 0 ; i < touches.size(); i ++)
    {
        if(touches.at(i)->getLocation().distanceSquared(_mainPosition) < _radiusSq)
        {
            _touchToTrack = i;
            _joystickSprite->setVisible(true);
            _bgSprite->setVisible(true);
            setIsActive(true);

        }
    }

}

void Joystick::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    
    for(int i = 0 ; i < touches.size(); i ++)
    {
        if(touches.at(i)->getLocation().distanceSquared(_mainPosition) < _radiusSq)
        {
            _touchToTrack = i;
            _joystickSprite->setPosition(touches.at(i)->getLocation());
            joystickBoundaryUpdate();
        }
    }
}

void Joystick::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for(int i = 0 ; i < touches.size(); i ++)
    {
        if(touches.at(i)->getLocation().distanceSquared(_mainPosition) < _radiusSq)
        {
            _joystickSprite->setPosition(_mainPosition);
            /*_joystickSprite->setVisible(false);
            _bgSprite->setVisible(false);
            setIsActive(false);*/
        }
    }
}

void Joystick::setIsActive(bool active)
{
    _isActive = active;
    if(_didSetChangeCommand)
    {
        _onActiveChange();
    }
}

void Joystick::setOnActiveChange(const std::function<void()> &func)
{
    _onActiveChange = func;
    _didSetChangeCommand = true;
}

void Joystick::joystickBoundaryUpdate()
{
    if(_joystickSprite->getPosition().distance(_mainPosition) > BOUNDARY_DISTANCE)
    {
        float angle = -(_joystickSprite->getPosition() - _mainPosition).getAngle() + CC_DEGREES_TO_RADIANS(90);
        _joystickSprite->setPosition(Point(_mainPosition.x  + BOUNDARY_DISTANCE*sinf((angle )), _mainPosition.y + BOUNDARY_DISTANCE *cosf((angle  ))));
    }
}


float Joystick::getDirection() const
{
    if(_isActive)
    {
        return  180 - CC_RADIANS_TO_DEGREES( (-_joystickSprite->getPosition() + _mainPosition).getAngle());
    }
    else{
        return 0.0f;
    }
}

void Joystick::setJoystickRadius(float radius)
{
    _radiusSq = radius * radius;
}

bool Joystick::getIsActive() const
{
    return _isActive;
}

float Joystick::getIntensity()
{
    if(_isActive)
    {
        
        return (_joystickSprite->getPosition().distance(_mainPosition)/BOUNDARY_DISTANCE) * 100;
    }
    else
        
    {
        return 0.0f;
    }
    
}
