//
//  PauseScene.hpp
//  test
//
//  Created by pjpjpj on 2017/7/20.
//
//

#ifndef PauseScene_hpp
#define PauseScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocos2d::ui;

class PauseScene : public Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PauseScene);
    
    Button *musicBtn;
    
    Sprite* createScreenshotSprite();
    void backBtnClick(Ref *pSender, Widget::TouchEventType type);
    void restartBtnClick(Ref *pSender, Widget::TouchEventType type);
    void homeBtnClick(Ref *pSender, Widget::TouchEventType type);
    void musicBtnClick(Ref *pSender, Widget::TouchEventType type);
    void appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments);
    Node* createRoundedRectMaskNode(Size size, float radius, float borderWidth, int cornerSegments);
};


#endif /* PauseScene_hpp */
