//
//  TipsLayer.hpp
//  2333
//
//  Created by pjpjpj on 2017/7/24.
//
//

#ifndef TipsLayer_hpp
#define TipsLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class TipsLayer : public Layer {
public:
    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(TipsLayer);
    
    Sprite *fingerSprite;
    Label *tipsLabel;
    Label *changeLabel;
    
    void changeShow();
};



#endif /* TipsLayer_hpp */
