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
    
    
    Sprite* createScreenshotSprite();
    void backBtnClick(Ref *pSender, Widget::TouchEventType type);
    void restartBtnClick(Ref *pSender, Widget::TouchEventType type);
    void homeBtnClick(Ref *pSender, Widget::TouchEventType type);
};


#endif /* PauseScene_hpp */
