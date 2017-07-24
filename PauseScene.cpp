//
//  PauseScene.cpp
//  test
//
//  Created by pjpjpj on 2017/7/20.
//
//

#include "PauseScene.hpp"
#include "HelloWorldScene.h"
#include "BeginScene.hpp"


Scene* PauseScene::createScene()
{
    return PauseScene::create();
}

bool PauseScene::init() {
    
    if (!Scene::init()) {
        return false;
    }
    
    
    Size visible = Director::getInstance()->getWinSize();
    
    Sprite* sprScreenshot = PauseScene::createScreenshotSprite();
    sprScreenshot->setPosition(visible / 2);
    this->addChild(sprScreenshot, 0);
    
    auto bgLayer = LayerColor::create(Color4B(0, 0, 0, 255 * 0.3), visible.width, visible.height);
    addChild(bgLayer);
    
    auto contentLayer = LayerColor::create(Color4B(38, 38, 38, 255), visible.width, visible.height * 0.5);
    contentLayer->setPosition(Vec2(0, visible.height / 4));
    addChild(contentLayer);
    
    auto pauseBtn = Button::create();
    pauseBtn->setTitleText("游戏暂停");
    pauseBtn->setTitleFontSize(78);
    contentLayer->addChild(pauseBtn);
    pauseBtn->setPosition(Vec2(visible.width / 2, contentLayer->getContentSize().height - 68));
    
    auto backBtn = Button::create();
    backBtn->setTitleText("继续游戏");
    backBtn->setTitleFontSize(48);
    contentLayer->addChild(backBtn);
    backBtn->setPosition(Vec2(visible.width / 2, pauseBtn->getPosition().y - pauseBtn->getContentSize().height - 48));
    backBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::backBtnClick, this));
    
    auto restartBtn = Button::create();
    restartBtn->setTitleText("重新开始");
    restartBtn->setTitleFontSize(48);
    contentLayer->addChild(restartBtn);
    restartBtn->setPosition(Vec2(visible.width / 2, backBtn->getPosition().y - backBtn->getContentSize().height - 48));
    restartBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::restartBtnClick, this));
    
    auto homeBtn = Button::create();
    homeBtn->setTitleText("回到菜单");
    homeBtn->setTitleFontSize(48);
    contentLayer->addChild(homeBtn);
    homeBtn->setPosition(Vec2(visible.width / 2, restartBtn->getPosition().y - restartBtn->getContentSize().height - 48));
    homeBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::homeBtnClick, this));
    
    return true;
}

void PauseScene::backBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->popScene();
    }
}

void PauseScene::restartBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->replaceScene(TransitionFlipX::create(0.4, HelloWorld::createScene()));
    }
}

void PauseScene::homeBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->replaceScene(TransitionMoveInT::create(0.4, BeginScene::createScene()));
    }
}

// 获取当前屏幕截图
Sprite* PauseScene::createScreenshotSprite()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
    
    renderTexture->begin();
    Director::getInstance()->getRunningScene()->visit();
    renderTexture->end();
    
    Texture2D* texture = renderTexture->getSprite()->getTexture();
    Sprite* sprScreenshot = Sprite::createWithTexture(texture);
    sprScreenshot->setFlippedY(true);
    return sprScreenshot;
}
