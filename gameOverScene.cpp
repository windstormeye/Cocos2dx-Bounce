//
//  gameOverScene.cpp
//  test
//
//  Created by pjpjpj on 2017/7/20.
//
//

#include "gameOverScene.hpp"
#include "HelloWorldScene.h"
#include "BeginScene.hpp"

Scene *GameOverScene::createScene() {
    return GameOverScene::create();
}

bool GameOverScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    Size visible = Director::getInstance()->getWinSize();
    
    auto bgLayer = LayerColor::create(Color4B(0, 0, 0, 255), visible.width, visible.height);
    addChild(bgLayer);
    
    auto contentLayer = Layer::create();
    addChild(contentLayer);
    contentLayer->setContentSize(Size(visible.width, visible.height / 2));
    contentLayer->setPosition(Vec2(0, visible.height / 4));
    
    levelLabel = Label::createWithTTF("0", "fonts/arial.ttf", 128);
    levelLabel->setPosition(Vec2(contentLayer->getContentSize().width / 2, contentLayer->getPosition().y + 128));
    contentLayer->addChild(levelLabel);
    
    auto bestLayer = Layer::create();
    contentLayer->addChild(bestLayer);
    bestLayer->setPosition(Vec2((visible.width - visible.width / 4) /2 , levelLabel->getPosition().y - 128 / 2 - 58));
    bestLayer->setContentSize(Size(visible.width / 4, 58));
    
    bestLevelLabel = Label::createWithTTF("BEST", "fonts/arial.ttf", 38);
    bestLevelLabel->setPosition(Vec2(bestLevelLabel->getContentSize().width / 1.5, bestLevelLabel->getContentSize().height / 2));
    bestLayer->addChild(bestLevelLabel);
    
    auto bestLevelNumLable = Label::createWithTTF("0", "fonts/arial.ttf", 38);
    bestLevelNumLable->setPosition(Vec2(bestLevelLabel->getPosition().x + bestLevelLabel->getContentSize().width / 2 + 38, bestLevelLabel->getPosition().y));
    bestLayer->addChild(bestLevelNumLable);
    bestLevelNumLable->setString(UserDefault::getInstance()->getStringForKey("BestLevel"));
    
    auto restartBtn = Button::create();
    restartBtn->setTitleText("重新开始");
    restartBtn->setTitleFontSize(48);
    contentLayer->addChild(restartBtn);
    restartBtn->setPosition(Vec2(contentLayer->getContentSize().width / 2, bestLayer->getPosition().y - 48 * 2));
    restartBtn->addTouchEventListener(CC_CALLBACK_2(GameOverScene::restartBtnClick, this));
    
    auto backBtn = Button::create();
    backBtn->setTitleText("回到菜单");
    backBtn->setTitleFontSize(48);
    contentLayer->addChild(backBtn);
    backBtn->setPosition(Vec2(contentLayer->getContentSize().width / 2, restartBtn->getPosition().y - restartBtn->getContentSize().height - 48 / 2));
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
