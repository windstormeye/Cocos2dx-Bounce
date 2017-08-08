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
#include "SimpleAudioEngine.h"

// 记录是否加过速
static bool isSpeedUp;
// 当前小球是否处于活跃状态
static bool isActivity;
// 加速按钮点击间隔
int oldTime;

USING_NS_CC;
using namespace CocosDenshion;


Layer* HeadLayer::createLayer()
{
    return HeadLayer::create();
}

bool HeadLayer::init() {
    if ( !Layer::init() )
    {
        return false;
    }
    
    isSpeedUp = false;
    isActivity = false;
    oldTime = 0;
    
    Size visible = Director::getInstance()->getWinSize();
    
    auto bgLayer = LayerColor::create(Color4B(131, 131, 131, 255),visible.width, 128);
    addChild(bgLayer, 0);
    
    auto pauseBtn = Button::create("res/pause.png");
    pauseBtn->setScaleZ(0.5);
    pauseBtn->setPosition(Vec2(50, 128 - 64));
    pauseBtn->addTouchEventListener(CC_CALLBACK_2(HeadLayer::pauseBtnClick, this));
    this->addChild(pauseBtn);
    
    levelLabel = Label::createWithTTF("BEST", "fonts/chinese.ttf", 22);
    levelLabel->setPosition(Vec2(pauseBtn->getPosition().x + pauseBtn->getContentSize().width * 1.5, 98));
    addChild(levelLabel);
    
    bestLevelLabel = Label::createWithTTF("0", "fonts/chinese.ttf", 58);
    bestLevelLabel->setPosition(Vec2(levelLabel->getPosition().x, levelLabel->getPosition().y - levelLabel->getContentSize().height * 1.5));
    addChild(bestLevelLabel);
    
    currentLevelLabel = Label::createWithTTF("0", "fonts/chinese.ttf", 78);
    currentLevelLabel->setPosition(Vec2(visible.width / 2, bestLevelLabel->getPosition().y + 10));
    addChild(currentLevelLabel);
    
    speedBtn = Button::create("res/speed_no.png");
    addChild(speedBtn);
    speedBtn->setName("res/speed_no.png");
    speedBtn->setPosition(Vec2(visible.width - 40, 128 / 2));
    speedBtn->addTouchEventListener(CC_CALLBACK_2(HeadLayer::speedBtnClick, this));
    
    auto ballLabel = Label::createWithTTF("BALLS", "fonts/chinese.ttf", 22);
    ballLabel->setPosition(Vec2(visible.width * 0.8, 98));
    addChild(ballLabel);
    
    currentBallLabel = Label::create();
    currentBallLabel->setString("1");
    addChild(currentBallLabel);
    currentBallLabel->setPosition(Vec2(ballLabel->getPosition().x, ballLabel->getPosition().y - ballLabel->getContentSize().height * 1.5));
    currentBallLabel->setSystemFontSize(58);
    
    updateBestLevelLabelText();
    
    return true;
}

// 加速效果
void HeadLayer::speedBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        if (isActivity && speedBtn->getName() == "res/speed.png") {
            for (int j = 0; j < (int)ballVec->size(); j++) {
                auto ball = ballVec->at(j);
                auto vvv = ball->getPhysicsBody()->getVelocity();
                if (vvv.y < 70 && ball->getName() != "no") {
                    ball->getPhysicsBody()->setVelocity(Vec2(vvv.x * 2, vvv.y * 2 + 100));
                } else {
                    ball->getPhysicsBody()->setVelocity(Vec2(vvv.x * 2, vvv.y * 2));
                }
            }
            Director::getInstance()->getScheduler()->setTimeScale(2.0);
            speedBtn->loadTextureNormal("res/speed_no.png");
            speedBtn->setName("res/speed_no.png");
            isSpeedUp = true;
        }
    }
}

void HeadLayer::pauseBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        
        if (UserDefault::getInstance()->getBoolForKey("isMusic")) {
            SimpleAudioEngine::getInstance()->playEffect("music/BtnClick.caf");
        }
        
        // 以淡出的方式出现暂停场景
        Director::getInstance()->pushScene(PauseScene::createScene());
    }
}

void HeadLayer::updateBallVec(std::shared_ptr<Vector<Sprite *>> b) {
    ballVec = b;
}

void HeadLayer::changeCurrentLevelLabelText(const std::string &text) {
    currentLevelLabel->setString(text);
}

void HeadLayer::changeCurrnetBallLabelText(const std::string &text) {
    currentBallLabel->setString(text);
}

void HeadLayer::updateBestLevelLabelText() {
    bestLevelLabel->setString(UserDefault::getInstance()->getStringForKey("BestLevel"));
    UserDefault::getInstance()->flush();
}

void HeadLayer::updateSpeedStatus(bool isS, bool isA) {
    isSpeedUp = isS;
    isActivity = isA;
}

void HeadLayer::showSpeedBtn(bool isShow) {
    if (isShow) {
        //        speedBtn->setVisible(true);
        speedBtn->loadTextureNormal("res/speed.png");
        speedBtn->setName("res/speed.png");
    } else {
        //        speedBtn->setVisible(false);
        speedBtn->loadTextureNormal("res/speed_no.png");
        speedBtn->setName("res/speed_no.png");
    }
}
