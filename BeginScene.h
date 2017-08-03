//
//  BeginScene.hpp
//  test
//
//  Created by pjpjpj on 2017/7/18.
//
//

#ifndef BeginScene_hpp
#define BeginScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"


using namespace cocos2d::ui;
USING_NS_CC;

class BeginScene:public Scene {
private:
    void beginBtnClick(Ref *pSender, Widget::TouchEventType type);
    void hintBtnClick(Ref *pSender, Widget::TouchEventType type);
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(BeginScene);
    
    void appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments);
    Node* createRoundedRectMaskNode(cocos2d::Size size, float radius, float borderWidth, int cornerSegments);
    
};

#endif /* BeginScene_hpp */
