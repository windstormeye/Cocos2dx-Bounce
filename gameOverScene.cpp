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
    
    levelLabel = Label::createWithTTF("0", "fonts/arial.ttf", 200);
    levelLabel->setPosition(Vec2(visible.width / 2, gameoverLogo->getPosition().y - gameoverLogo->getContentSize().height));
    addChild(levelLabel);
    
    bestLevelLabel = Label::createWithTTF("BEST", "fonts/arial.ttf", 23);
    bestLevelLabel->setPosition(Vec2(visible.width / 2 - 70, levelLabel->getPosition().y - levelLabel->getContentSize().height / 2));
    addChild(bestLevelLabel);
    
    auto bestLevelZHLabel = Label::create();
    addChild(bestLevelZHLabel);
    bestLevelZHLabel->setString("最佳分数");
    bestLevelZHLabel->setSystemFontSize(25);
    bestLevelZHLabel->setPosition(Vec2(visible.width / 2 - 75, bestLevelLabel->getPosition().y - bestLevelZHLabel->getContentSize().height / 2 - 25));
    
    auto bestLevelNumLable = Label::createWithTTF("0", "fonts/arial.ttf", 88);
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
    
    return true;
}

void GameOverScene::restartBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->replaceScene(TransitionFlipX::create(0.4, HelloWorld::createScene()));
    }
}

void GameOverScene::backBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->replaceScene(TransitionMoveInT::create(0.4, BeginScene::createScene()));
    }
}

void GameOverScene::setCurrentLevelNum(const std::string &text) {
    levelLabel->setString(text);
}
