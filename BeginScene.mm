//
//  BeginScene.cpp
//  test
//
//  Created by pjpjpj on 2017/7/18.
//
//

#include "BeginScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene* BeginScene::createScene()
{
    return BeginScene::create();
}

bool BeginScene::init() {
    
    if (!Scene::init()) {
        return false;
    }
    cocos2d::Size visible = Director::getInstance()->getWinSize();
    
    auto bgLayer = Layer::create();
    addChild(bgLayer);
    bgLayer->setContentSize(cocos2d::Size(visible.width, visible.height));
    bgLayer->setPosition(Vec2(0, 0));
    
    auto bgImg = Sprite::create("res/bg.png");
    bgImg->setContentSize(cocos2d::Size(bgLayer->getContentSize().width, bgLayer->getContentSize().height));
    bgImg->setPosition(Vec2(bgLayer->getContentSize().width / 2, bgLayer->getContentSize().height / 2));
    bgLayer->addChild(bgImg);
    
    auto logoSprite = Sprite::create("res/logo.png");
    addChild(logoSprite, 2);
    logoSprite->setPosition(Vec2(visible.width / 2, visible.height * 0.7));
    logoSprite->setScale(0.7, 0.7);
    
    auto logoRotationSprite = Sprite::create("res/logo_ratation.png");
    addChild(logoRotationSprite, 1);
    logoRotationSprite->setPosition(Vec2(visible.width / 2 + 162, logoSprite->getPosition().y - logoSprite->getContentSize().height / 3.3));
    logoRotationSprite->setContentSize(cocos2d::Size(90, 90));
    ActionInterval * rotateto = RotateBy::create(0.5, -300);
    logoRotationSprite->runAction(RepeatForever::create(Sequence::create(rotateto,NULL)));
    
    auto beginSprite = Sprite::create("res/redBG.png");
    addChild(beginSprite);
    beginSprite->setContentSize(cocos2d::Size(visible.width * 0.6, visible.height * 0.1));
    beginSprite->setPosition(Vec2(visible.width / 2, visible.height / 2));
    
    auto beginLogo = Sprite::create("res/begin_game.png");
    beginSprite->addChild(beginLogo);
    beginLogo->setContentSize(cocos2d::Size(visible.height * 0.1 - 20, visible.height * 0.1 - 20));
    beginLogo->setPosition(Vec2(beginLogo->getContentSize().width / 2 + 10, (beginSprite->getContentSize().height - 20) / 2 + 10));
    
    auto beginBtn = Button::create();
    beginBtn->setTitleText("开始 PLAY");
    beginBtn->setTitleFontSize(50);
    beginSprite->addChild(beginBtn);
    beginBtn->setPosition(Vec2(beginLogo->getContentSize().width * 2 + beginLogo->getPosition().x, beginLogo->getContentSize().height / 1.7));
    beginBtn->addTouchEventListener(CC_CALLBACK_2(BeginScene::beginBtnClick, this));
    
    auto hintSprite = Sprite::create("res/grayBG.png");
    addChild(hintSprite);
    hintSprite->setPosition(Vec2(visible.width / 2, visible.height * 0.35));
    hintSprite->setContentSize(cocos2d::Size(visible.width * 0.6, visible.height * 0.1));
    
    auto hintLogo = Sprite::create("res/hint.png");
    hintSprite->addChild(hintLogo);
    hintLogo->setContentSize(cocos2d::Size(visible.height * 0.1 - 20, visible.height * 0.1 - 20));
    hintLogo->setPosition(Vec2(hintLogo->getContentSize().width / 2 + 10, (hintSprite->getContentSize().height - 20) / 2 + 10));
    
    auto hintBtn = Button::create();
    hintBtn->setTitleText("提示 HINT");
    hintBtn->setTitleFontSize(50);
    hintSprite->addChild(hintBtn);
    hintBtn->setPosition(Vec2(beginLogo->getContentSize().width * 2 + beginLogo->getPosition().x, beginLogo->getContentSize().height / 1.7));
    hintBtn->addTouchEventListener(CC_CALLBACK_2(BeginScene::hintBtnClick, this));
    
    return true;
}

void BeginScene::hintBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        if (UserDefault::getInstance()->getBoolForKey("isMusic")) {
            SimpleAudioEngine::getInstance()->playEffect("music/BtnClick.caf");
        }
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"https://www.baidu.com"]];
    }
}

void BeginScene::beginBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        
        if (UserDefault::getInstance()->getBoolForKey("isMusic")) {
            SimpleAudioEngine::getInstance()->playEffect("music/BtnClick.caf");
        }
        
        UserDefault::getInstance()->setBoolForKey("isResurgence", false);
        UserDefault::getInstance()->flush();
        UserDefault::getInstance()->setBoolForKey("isResurgenceed", false);
        UserDefault::getInstance()->flush();
        
        if (UserDefault::getInstance()->getBoolForKey("isMusic", true)) {
            UserDefault::getInstance()->setBoolForKey("isMusic", true);
            UserDefault::getInstance()->flush();
        }
        
        Director::getInstance()->replaceScene(TransitionSlideInB::create(0.4, HelloWorld::createScene()));
    }
}
