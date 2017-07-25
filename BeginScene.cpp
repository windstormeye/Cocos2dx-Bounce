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
    
    auto bgLayer = Layer::create();
    addChild(bgLayer);
    bgLayer->setContentSize(Size(visible.width, visible.height));
    bgLayer->setPosition(Vec2(0, 0));
    
    auto bgImg = Sprite::create("res/bg.png");
    bgImg->setContentSize(Size(bgLayer->getContentSize().width, bgLayer->getContentSize().height));
    bgImg->setPosition(Vec2(bgLayer->getContentSize().width / 2, bgLayer->getContentSize().height / 2));
    bgLayer->addChild(bgImg);
    
    auto homeBtnBGLayer = LayerColor::create(Color4B(235, 69, 57, 255), visible.width * 0.6, visible.height * 0.1);
    auto beginLogo = Sprite::create("res/begin_game.png");
    homeBtnBGLayer->addChild(beginLogo);
    beginLogo->setContentSize(Size(visible.height * 0.1 - 20, visible.height * 0.1 - 20));
    beginLogo->setPosition(Vec2(beginLogo->getContentSize().width / 2 + 10, (homeBtnBGLayer->getContentSize().height - 20) / 2 + 10));
    
    auto homeBtn = Button::create();
    homeBtn->setTitleText("开始 PLAY");
    homeBtn->setTitleFontSize(50);
    homeBtnBGLayer->addChild(homeBtn);
    homeBtn->setPosition(Vec2(beginLogo->getContentSize().width * 2 + beginLogo->getPosition().x, homeBtnBGLayer->getContentSize().height / 2));
    homeBtn->addTouchEventListener(CC_CALLBACK_2(BeginScene::beginBtnClick, this));
    
    auto homeBtnClipNode = createRoundedRectMaskNode(Size(visible.width * 0.6, visible.height * 0.1), 60, 1.0f, 50);
    homeBtnClipNode->addChild(homeBtnBGLayer);
    homeBtnClipNode->setPosition((visible.width - visible.width * 0.6) / 2, visible.height / 2);
    bgLayer->addChild(homeBtnClipNode);
    
    return true;
}

void BeginScene::beginBtnClick(cocos2d::Ref *pSender, Widget::TouchEventType type) {
    // 从右向左切换场景到游戏主场景中
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->replaceScene(TransitionSlideInB::create(0.4, HelloWorld::createScene()));
    }
}

void BeginScene::appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments)
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

Node* BeginScene::createRoundedRectMaskNode(Size size, float radius, float borderWidth, int cornerSegments)
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
