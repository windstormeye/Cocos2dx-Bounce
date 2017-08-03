//
//  headLayer.hpp
//  test
//
//  Created by pjpjpj on 2017/7/18.
//
//

#ifndef headLayer_hpp
#define headLayer_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;


class HeadLayer:public Layer {
public:
    
    // BEST Label
    Label *levelLabel;
    // 当前成绩Label
    Label *currentLevelLabel;
    // 历史最好成绩label
    Label *bestLevelLabel;
    // 加速按钮
    Button *speedBtn;
    // 当前所有小球
    Label *currentBallLabel;
    // 保存所有的格子
    std::shared_ptr<Vector<Sprite*>>  ballVec = std::make_shared<Vector<Sprite*>>();
    
    void pauseBtnClick(Ref *pSender, Widget::TouchEventType type);
    // 改变当前成绩Label显示的数字
    void changeCurrentLevelLabelText(const std::string &text);
    void changeCurrnetBallLabelText(const std::string &text);
    void updateBallVec(std::shared_ptr<Vector<Sprite*>> b);
    void updateBestLevelLabelText();
    void updateSpeedStatus(bool isS, bool isA);
    void showSpeedBtn(bool isShow);
    
    void speedBtnClick(Ref *pSender, Widget::TouchEventType type);
    
    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(HeadLayer);
};

#endif /* headLayer_hpp */
