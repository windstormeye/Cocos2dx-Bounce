//
//  PauseScene.cpp
//  test
//
//  Created by pjpjpj on 2017/7/20.
//
//

#include "PauseScene.hpp"
#include "HelloWorldScene.h"
#include "BeginScene.h"


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
    
    auto contentLayer = LayerColor::create(Color4B(227, 227, 227, 255));
    contentLayer->setContentSize(Size(visible.width, visible.height * 0.7));
    // contentLayer的剪切
    auto contentLayerClipNode = createRoundedRectMaskNode(Size(visible.width * 0.95, visible.height * 0.7), 50, 1.0f, 20);
    contentLayerClipNode->addChild(contentLayer);
    contentLayerClipNode->setPosition(visible.width * 0.05f / 2, visible.height * 0.3f / 2);
    this->addChild(contentLayerClipNode);
    
    auto layerTitle = Label::create();
    layerTitle->setString("暂停 PAUSE");
    layerTitle->setTextColor(Color4B(255, 255, 255, 255));
    layerTitle->setSystemFontSize(45);
    layerTitle->setPosition(Vec2(visible.width / 2, contentLayer->getContentSize().height - visible.height * 0.1 / 2));
    contentLayer->addChild(layerTitle);
    
    auto backBtnBGLayer = LayerColor::create(Color4B(235, 69, 57, 255), visible.width * 0.6, visible.height * 0.1);
    auto backBtn = Button::create();
    backBtn->setTitleText("继续 CONTINUE");
    backBtn->setTitleFontSize(40);
    backBtnBGLayer->addChild(backBtn);
    backBtn->setPosition(Vec2(backBtnBGLayer->getContentSize().width / 2, backBtnBGLayer->getContentSize().height / 2));
    backBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::backBtnClick, this));
    
    auto backBtnClipNode = createRoundedRectMaskNode(Size(visible.width * 0.6, visible.height * 0.1), 60, 1.0f, 50);
    backBtnClipNode->addChild(backBtnBGLayer);
    backBtnClipNode->setPosition((visible.width - visible.width * 0.6) / 2, layerTitle->getPosition().y - layerTitle->getContentSize().height - visible.height * 0.15);
    contentLayer->addChild(backBtnClipNode);
    
    auto restartBtnBGLayer = LayerColor::create(Color4B(255, 255, 255, 255), visible.width * 0.6, visible.height * 0.1);
    auto restartBtn = Button::create();
    restartBtn->setTitleText("重新开始 RESTART");
    restartBtn->setTitleFontSize(40);
    restartBtn->setTitleColor(Color3B(84, 84, 84));
    restartBtnBGLayer->addChild(restartBtn);
    restartBtn->setPosition(Vec2(restartBtnBGLayer->getContentSize().width / 2, restartBtnBGLayer->getContentSize().height / 2));
    restartBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::restartBtnClick, this));
    
    auto restartBtnClipNode = createRoundedRectMaskNode(Size(visible.width * 0.6, visible.height * 0.1), 60, 1.0f, 50);
    restartBtnClipNode->addChild(restartBtnBGLayer);
    restartBtnClipNode->setPosition((visible.width - visible.width * 0.6) / 2, backBtnClipNode->getPosition().y - visible.height * 0.15);
    contentLayer->addChild(restartBtnClipNode);
    
    auto homeBtnBGLayer = LayerColor::create(Color4B(131, 131, 131, 255), visible.width * 0.6, visible.height * 0.1);
    auto homeBtn = Button::create();
    homeBtn->setTitleText("主菜单 MAIN MENU");
    homeBtn->setTitleFontSize(40);
    homeBtn->setTitleColor(Color3B(255, 255, 255));
    homeBtnBGLayer->addChild(homeBtn);
    homeBtn->setPosition(Vec2(homeBtnBGLayer->getContentSize().width / 2, homeBtnBGLayer->getContentSize().height / 2));
    homeBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::homeBtnClick, this));
    
    auto homeBtnClipNode = createRoundedRectMaskNode(Size(visible.width * 0.6, visible.height * 0.1), 60, 1.0f, 50);
    homeBtnClipNode->addChild(homeBtnBGLayer);
    homeBtnClipNode->setPosition((visible.width - visible.width * 0.6) / 2, restartBtnClipNode->getPosition().y - visible.height * 0.15);
    contentLayer->addChild(homeBtnClipNode);
    
    musicBtn = Button::create("res/music_on.png");
    contentLayer->addChild(musicBtn);
    musicBtn->setName("res/music_on.png");
    musicBtn->setScale(0.6);
    musicBtn->setPosition(Vec2(visible.width / 2, 100));
    musicBtn->addTouchEventListener(CC_CALLBACK_2(PauseScene::musicBtnClick, this));
    
    return true;
}

void PauseScene::musicBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        if (musicBtn->getName() == "res/music_on.png") {
            musicBtn->loadTextureNormal("res/music_off.png");
            musicBtn->setName("res/music_off.png");
        } else {
            musicBtn->loadTextureNormal("res/music_on.png");
            musicBtn->setName("res/music_on.png");
        }
    }
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

// 获取圆角贝塞尔锚点
void PauseScene::appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments)
{
    float t = 0;
    for(int i = 0; i < segments; i++)
    {
        float x = powf(1 - t, 3) * from.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * to.x;
        float y = powf(1 - t, 3) * from.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * to.y;
        verts[startPoint + i] = Vec2(x,y);
        t += 1.0f / segments;
    }
}

// 获取绘制好圆角的Node
Node* PauseScene::createRoundedRectMaskNode(Size size, float radius, float borderWidth, int cornerSegments)
{
    const float kappa = 0.552228474;
    float oneMinusKappa = (1.0f-kappa);
    
    // define corner control points
    std::vector<Vec2> verts(16);
    
    verts[0] = Vec2(0, radius);
    verts[1] = Vec2(0, radius * oneMinusKappa);
    verts[2] = Vec2(radius * oneMinusKappa, 0);
    verts[3] = Vec2(radius, 0);
    
    verts[4] = Vec2(size.width - radius, 0);
    verts[5] = Vec2(size.width - radius * oneMinusKappa, 0);
    verts[6] = Vec2(size.width, radius * oneMinusKappa);
    verts[7] = Vec2(size.width, radius);
    
    verts[8] = Vec2(size.width, size.height - radius);
    verts[9] = Vec2(size.width, size.height - radius * oneMinusKappa);
    verts[10] = Vec2(size.width - radius * oneMinusKappa, size.height);
    verts[11] = Vec2(size.width - radius, size.height);
    
    verts[12] = Vec2(radius, size.height);
    verts[13] = Vec2(radius * oneMinusKappa, size.height);
    verts[14] = Vec2(0, size.height - radius * oneMinusKappa);
    verts[15] = Vec2(0, size.height - radius);
    
    // result
    std::vector<Vec2> polyVerts(4 * cornerSegments + 1);
    
    // add corner arc segments
    appendCubicBezier(0 * cornerSegments, polyVerts, verts[0], verts[1], verts[2], verts[3], cornerSegments);
    appendCubicBezier(1 * cornerSegments, polyVerts, verts[4], verts[5], verts[6], verts[7], cornerSegments);
    appendCubicBezier(2 * cornerSegments, polyVerts, verts[8], verts[9], verts[10], verts[11], cornerSegments);
    appendCubicBezier(3 * cornerSegments, polyVerts, verts[12], verts[13], verts[14], verts[15], cornerSegments);
    // close path
    polyVerts[4 * cornerSegments] = verts[0];
    
    // draw final poly into mask
    auto shapeMask = DrawNode::create();
    shapeMask->drawPolygon(&polyVerts[0], (int)polyVerts.size(), Color4F::WHITE, 0.0f, Color4F::WHITE);
    
    // create clip node with draw node as stencil (mask)
    return ClippingNode::create(shapeMask);
}
