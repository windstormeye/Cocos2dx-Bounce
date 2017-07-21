//
//  BeginScene.cpp
//  test
//
//  Created by pjpjpj on 2017/7/18.
//
//

#include "BeginScene.hpp"
#include "HelloWorldScene.h"

Scene* BeginScene::createScene()
{
    return BeginScene::create();
}

bool BeginScene::init() {
    
    if (!Scene::init()) {
        return false;
    }
    Size visible = Director::getInstance()->getWinSize();

    auto bgLayer = LayerColor::create(Color4B(0, 0, 0, 255), visible.width, visible.height);
    addChild(bgLayer);
    
    auto beginBtn = Button::create("res/begin.png");
    addChild(beginBtn);
    beginBtn->setPosition(Vec2(visible.width / 2, visible.height / 2));
    beginBtn->addTouchEventListener(CC_CALLBACK_2(BeginScene::beginBtnClick, this));

//    bestLevelLabel = Label::createWithTTF("399", "fonts/arial.ttf", 58);
//    bestLevelLabel->setPosition(Vec2(levelLabel->getPosition().x, 113 - bestLevelLabel->getContentSize().height));
//    addChild(bestLevelLabel);

    auto titleLabel = Label::createWithTTF("I want sleep", "fonts/arial.ttf", 48);
    titleLabel->setPosition(visible.width / 2, beginBtn->getPosition().y - beginBtn->getContentSize().height);
    addChild(titleLabel);
    
    
    return true;
}

void BeginScene::beginBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    // 从右向左切换场景到游戏主场景中
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->replaceScene(TransitionSlideInB::create(0.4, HelloWorld::createScene()));
    }
}
