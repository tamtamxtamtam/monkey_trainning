/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe() {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(cocos2d::Layer *layer) {    
    auto topPipe = Sprite::create("Resources/iphonehd/Pipe.png");
    auto bottomPipe = Sprite::create("Resources/iphonehd/Pipe.png");
    
    auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
    auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());
    
    auto random = CCRANDOM_0_1();
    
    if(random < LOWER_SCREEN_PIPE_THRESHOLD) {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    } else if(random > UPPER_SCREEN_PIPE_THRESHOLD){
        random = UPPER_SCREEN_PIPE_THRESHOLD;
    }
    
    auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height/2);
    topPipeBody->setDynamic(false);
    bottomPipeBody->setDynamic(false);
    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    bottomPipeBody->setContactTestBitmask(true);
    
    topPipe->setPhysicsBody(topPipeBody);
    bottomPipe->setPhysicsBody(bottomPipeBody);
    
    topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition));
    bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - Sprite::create( "Resources/iphonehd/Ball.png")->getContentSize().height * PIPE_GAP- topPipe->getContentSize().height));
    
    layer->addChild(topPipe);
    layer->addChild(bottomPipe);
    
    auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5 , 0));
    auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5 , 0));
    
    topPipe->runAction(topPipeAction);
    bottomPipe->runAction(bottomPipeAction);
    
    auto pointNode = Node::create();
    auto pointBody = PhysicsBody::createBox(Size(1, Sprite::create("Resources/iphonehd/Ball.png")->getContentSize().height * PIPE_GAP));
    pointBody->setDynamic(false);
    pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
    pointBody->setContactTestBitmask(true);
    
    pointNode->setPhysicsBody(pointBody);
    pointNode->setPosition(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe->getContentSize().height/2 ) - (Sprite::create("Resources/iphonehd/Ball.png")->getContentSize().height * PIPE_GAP)/2);
    layer->addChild(pointNode);
    
    auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));
    pointNode->runAction(pointNodeAction);
    
}
