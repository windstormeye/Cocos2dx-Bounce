//
//  gameOverScene.cpp
//  test
//
//  Created by pjpjpj on 2017/7/20.
//
//

#include "gameOverScene.hpp"
#include "HelloWorldScene.h"
#include "BeginScene.h"
#include "SimpleAudioEngine.h"

#define GAMEOVER_MUSIC "music/gameOver.caf"

using namespace CocosDenshion;


Scene *GameOverScene::createScene() {
    return GameOverScene::create();
}

bool GameOverScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    Size visible = Director::getInstance()->getWinSize();
    
    auto bgLayer = LayerColor::create(Color4B(30, 30, 30, 255), visible.width, visible.height);
    addChild(bgLayer);
    
    auto logo2Sprite = Sprite::create("res/logo2.png");
    addChild(logo2Sprite);
    logo2Sprite->setPosition(Vec2(visible.width / 2, visible.height * 0.87));
    logo2Sprite->setScale(0.7, 0.7);
    
    // gamaOver缺个O
    auto gameoverLogo = Sprite::create("res/gameover.png");
    addChild(gameoverLogo);
    gameoverLogo->setPosition(Vec2(visible.width / 2, visible.height * 0.8));
    gameoverLogo->setScale(0.65, 0.65);
    
    // 补充 O
    auto Ologo = Sprite::create("res/o.png");
    addChild(Ologo);
    Ologo->setScale(0.65, 0.65);
    Ologo->setPosition(Vec2(visible.width / 2 + Ologo->getContentSize().width / 2 - 10, visible.height * 0.8));
    ActionInterval * rotateto = RotateBy::create(0.5, 300);
    Ologo->runAction(RepeatForever::create(Sequence::create(rotateto,NULL)));
    
    levelLabel = Label::createWithTTF("0", "fonts/chinese.ttf", 200);
    levelLabel->setPosition(Vec2(visible.width / 2, gameoverLogo->getPosition().y - gameoverLogo->getContentSize().height));
    addChild(levelLabel);
    
    bestLevelLabel = Label::createWithTTF("BEST", "fonts/chinese.ttf", 23);
    bestLevelLabel->setPosition(Vec2(visible.width / 2 - 70, levelLabel->getPosition().y - levelLabel->getContentSize().height / 2));
    addChild(bestLevelLabel);
    
    auto bestLevelZHLabel = Label::create();
    addChild(bestLevelZHLabel);
    bestLevelZHLabel->setString("最佳分数");
    bestLevelZHLabel->setSystemFontSize(25);
    bestLevelZHLabel->setPosition(Vec2(visible.width / 2 - 75, bestLevelLabel->getPosition().y - bestLevelZHLabel->getContentSize().height / 2 - 25));
    
    auto bestLevelNumLable = Label::createWithTTF("0", "fonts/chinese.ttf", 88);
    bestLevelNumLable->setPosition(Vec2(visible.width / 2 + 50, bestLevelLabel->getPosition().y - bestLevelLabel->getContentSize().height / 1.5));
    addChild(bestLevelNumLable);
    bestLevelNumLable->setString(UserDefault::getInstance()->getStringForKey("BestLevel"));
    
    auto restartBtn = Button::create("res/again.png");
    restartBtn->setTitleText("再来一次 REPLAY");
    restartBtn->setTitleFontSize(68);
    restartBtn->setScale(0.7, 0.7);
    addChild(restartBtn);
    restartBtn->setPosition(Vec2(visible.width / 2, bestLevelNumLable->getPosition().y - restartBtn->getContentSize().height / 1.2));
    restartBtn->addTouchEventListener(CC_CALLBACK_2(GameOverScene::restartBtnClick, this));
    
    auto backBtn = Button::create("res/main.png");
    backBtn->setTitleText("主菜单 MAIN MENU");
    backBtn->setTitleFontSize(65);
    backBtn->setScale(0.7, 0.7);
    addChild(backBtn);
    backBtn->setPosition(Vec2(visible.width / 2, restartBtn->getPosition().y - restartBtn->getContentSize().height));
    backBtn->addTouchEventListener(CC_CALLBACK_2(GameOverScene::backBtnClick, this));
    
    auto resurgenceSprite = Sprite::create("res/resurgence.png");
    addChild(resurgenceSprite);
    resurgenceSprite->setPosition(Vec2(visible.width / 2, visible.height * 0.13));
    resurgenceSprite->setScale(0.6);
    ActionInterval * scalaBy = ScaleTo::create(0.3, 0.8);
    ActionInterval * scalaBy2 = ScaleTo::create(0.3, 0.6);
    resurgenceSprite->runAction(RepeatForever::create(Sequence::create(scalaBy, scalaBy2, NULL)));
    
    auto resurgenceBtn = Button::create("res/resurgence_white.png");
    addChild(resurgenceBtn);
    resurgenceBtn->setPosition(Vec2(visible.width / 2, visible.height * 0.13));
    resurgenceBtn->setScale(0.8);
    resurgenceBtn->addTouchEventListener(CC_CALLBACK_2(GameOverScene::resurgenceBtnClick, this));
    
    auto infoBtn = Button::create("res/info.png");
    addChild(infoBtn);
    infoBtn->setScale(0.6);
    infoBtn->setPosition(Vec2(visible.width / 2 + 200, resurgenceBtn->getPosition().y));
    
    auto tipsLabel = Label::create();
    addChild(tipsLabel);
    tipsLabel->setString("注意：复活后关卡难度+5");
    tipsLabel->setSystemFontSize(20);
    tipsLabel->setColor(Color3B(78, 78, 78));
    tipsLabel->setPosition(Vec2(visible.width / 2, 28));
    
    if (UserDefault::getInstance()->getBoolForKey("isResurgenceed")) {
        resurgenceBtn->setVisible(false);
        resurgenceSprite->setVisible(false);
        infoBtn->setPosition(Vec2(visible.width / 2, infoBtn->getPosition().y));
        UserDefault::getInstance()->setBoolForKey("isResurgenceed", false);
    }
    
    // 给粒子效果设置定时器
    auto delayTime = DelayTime::create(0.2f);
    auto func = CallFunc::create([this]()
                                 {
                                     SimpleAudioEngine::getInstance()->playEffect(GAMEOVER_MUSIC);
                                 });
    auto seq = Sequence::create(delayTime, func, nullptr);
    this->runAction(seq);
    
    return true;
}

void GameOverScene::resurgenceBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        
        if (UserDefault::getInstance()->getBoolForKey("isMusic")) {
            SimpleAudioEngine::getInstance()->playEffect("music/resurgenceBtnClick.caf");
        }
        
        if (!UserDefault::getInstance()->getBoolForKey("isResurgenceed")) {
            UserDefault::getInstance()->setBoolForKey("isResurgence", true);
            UserDefault::getInstance()->flush();
        }
        Director::getInstance()->replaceScene(TransitionMoveInB::create(0.4, HelloWorld::createScene()));
    }
}

void GameOverScene::restartBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        
        if (UserDefault::getInstance()->getBoolForKey("isMusic")) {
            SimpleAudioEngine::getInstance()->playEffect("music/BtnClick.caf");
        }
        
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, HelloWorld::createScene()));
    }
}

void GameOverScene::backBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        
        if (UserDefault::getInstance()->getBoolForKey("isMusic")) {
            SimpleAudioEngine::getInstance()->playEffect("music/BtnClick.caf");
        }
        
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, BeginScene::createScene()));
    }
}

void GameOverScene::setCurrentLevelNum(const std::string &text) {
    levelLabel->setString(text);
}
