//
//  gameOverScene.hpp
//  test
//
//  Created by pjpjpj on 2017/7/20.
//
//

#ifndef gameOverScene_hpp
#define gameOverScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
USING_NS_CC;

class GameOverScene : public Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameOverScene);
    
    Label *levelLabel;
    Label *bestLevelLabel;
    
    Sprite* createScreenshotSprite();
    void restartBtnClick(Ref *pSender, Widget::TouchEventType type);
    void backBtnClick(Ref *pSender, Widget::TouchEventType type);

    void setCurrentLevelNum(const std::string &text);
};


#endif /* gameOverScene_hpp */
