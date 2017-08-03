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

// 记录是否加过速
static bool isSpeedUp;
// 当前小球是否处于活跃状态
static bool isActivity;
// 加速按钮点击间隔
int speedInterval;

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
    
    isSpeedUp = false;
    isActivity = false;
    speedInterval = 0;
    
    Size visible = Director::getInstance()->getWinSize();
    
    auto bgLayer = LayerColor::create(Color4B(131, 131, 131, 255),visible.width, 128);
    addChild(bgLayer, 0);
    
    auto pauseBtn = Button::create("res/pause.png");
    pauseBtn->setScaleZ(0.5);
    pauseBtn->setPosition(Vec2(50, 128 - 64));
    pauseBtn->addTouchEventListener(CC_CALLBACK_2(HeadLayer::pauseBtnClick, this));
    this->addChild(pauseBtn);
    
    levelLabel = Label::createWithTTF("BEST", "fonts/arial.ttf", 22);
    levelLabel->setPosition(Vec2(pauseBtn->getPosition().x + pauseBtn->getContentSize().width * 1.5, 98));
    addChild(levelLabel);
    
    bestLevelLabel = Label::createWithTTF("0", "fonts/arial.ttf", 58);
    bestLevelLabel->setPosition(Vec2(levelLabel->getPosition().x, 113 - bestLevelLabel->getContentSize().height));
    addChild(bestLevelLabel);
    
    currentLevelLabel = Label::createWithTTF("0", "fonts/arial.ttf", 78);
    currentLevelLabel->setPosition(Vec2(visible.width / 2, bestLevelLabel->getPosition().y + 10));
    addChild(currentLevelLabel);
    
    speedBtn = Button::create("res/speed.png");
    addChild(speedBtn);
    speedBtn->setVisible(false);
    speedBtn->setPosition(Vec2(visible.width - 40, 128 / 2));
    speedBtn->addTouchEventListener(CC_CALLBACK_2(HeadLayer::speedBtnClick, this));
    
    auto ballLabel = Label::create();
    ballLabel->setString("BALLS");
    ballLabel->setSystemFontSize(22);
    ballLabel->setPosition(Vec2(visible.width * 0.8, 98));
    addChild(ballLabel);
    
    currentBallLabel = Label::create();
    currentBallLabel->setString("1");
    addChild(currentBallLabel);
    currentBallLabel->setPosition(Vec2(ballLabel->getPosition().x, ballLabel->getPosition().y - ballLabel->getContentSize().height * 2));
    currentBallLabel->setSystemFontSize(58);
    
    updateBestLevelLabelText();
    
    return true;
}

// 加速效果
void HeadLayer::speedBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (!isSpeedUp && isActivity) {
        int isAllBallOut = 0;
        for (int i = 0; i < (int)ballVec->size(); i ++) {
            auto ball = ballVec->at(i);
            if (ball->getName() == "yes" && ball->getPosition().y > Director::getInstance()->getWinSize().height * 0.2 + 16) {
                isAllBallOut ++;
            } else {
                return;
            }
        }
        
        if (isAllBallOut == (int)ballVec->size()) {
            for (int j = 0; j < (int)ballVec->size(); j++) {
                auto ball = ballVec->at(j);
                auto vvv = ball->getPhysicsBody()->getVelocity();
                ball->getPhysicsBody()->setVelocity(Vec2(vvv.x * 2, vvv.y * 2));
            }
            Director::getInstance()->getScheduler()->setTimeScale(2.0f);
            isSpeedUp = true;
            speedBtn->setVisible(false);
        }
    }
}

void HeadLayer::pauseBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        // 以淡出的方式出现暂停场景
        Director::getInstance()->pushScene(TransitionCrossFade::create(0.4, PauseScene::createScene()));
        //        Director::getInstance()->pushScene(TransitionCrossFade::create(0.4, GameOverScene::createScene()));
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

void HeadLayer::showSpeedBtn() {
    speedBtn->setVisible(true);
}
