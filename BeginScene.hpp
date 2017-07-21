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
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(BeginScene);
};

#endif /* BeginScene_hpp */
