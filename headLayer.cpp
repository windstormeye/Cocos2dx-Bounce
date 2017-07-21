//
//  headLayer.cpp
//  test
//
//  Created by pjpjpj on 2017/7/18.
//
//

#include "headLayer.hpp"
#include "PauseScene.hpp"
#include "gameOverScene.hpp"


USING_NS_CC;


Layer* HeadLayer::createLayer()
{
    return HeadLayer::create();
}

bool HeadLayer::init() {
    if ( !Layer::init() )
    {
        return false;
    }
    Size visible = Director::getInstance()->getWinSize();
    
    auto bgLayer = LayerColor::create(Color4B(38, 38, 38, 255),visible.width, 128);
    addChild(bgLayer, 0);
    
    levelLabel = Label::createWithTTF("BEST", "fonts/arial.ttf", 22);
    levelLabel->setPosition(Vec2(visible.width - 70, 98));
    addChild(levelLabel);
    
    bestLevelLabel = Label::createWithTTF("399", "fonts/arial.ttf", 58);
    bestLevelLabel->setPosition(Vec2(levelLabel->getPosition().x, 113 - bestLevelLabel->getContentSize().height));
    addChild(bestLevelLabel);
    
    auto pauseBtn = Button::create("res/pause.png");
    this->addChild(pauseBtn);
    pauseBtn->setPosition(Vec2(50, 128 - 64));
    pauseBtn->addTouchEventListener(CC_CALLBACK_2(HeadLayer::pauseBtnClick, this));
    
    currentLevelLabel = Label::createWithTTF("0", "fonts/arial.ttf", 78);
    currentLevelLabel->setPosition(Vec2(visible.width / 2, bestLevelLabel->getPosition().y + 10));
    addChild(currentLevelLabel);
    
    updateBestLevelLabelText();
    
    return true;
}

void HeadLayer::pauseBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        // 以淡出的方式出现暂停场景
        Director::getInstance()->pushScene(TransitionCrossFade::create(0.4, PauseScene::createScene()));
    }
}

void HeadLayer::changeCurrentLevelLabelText(const std::string &text) {
    currentLevelLabel->setString(text);
}

void HeadLayer::updateBestLevelLabelText() {
    bestLevelLabel->setString(UserDefault::getInstance()->getStringForKey("BestLevel"));
}

