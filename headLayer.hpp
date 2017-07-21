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
    
    void pauseBtnClick(Ref *pSender, Widget::TouchEventType type);
    // 改变当前成绩Label显示的数字
    void changeCurrentLevelLabelText(const std::string &text);
    void updateBestLevelLabelText();
    
    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(HeadLayer);
};

#endif /* headLayer_hpp */
