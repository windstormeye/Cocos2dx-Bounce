#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "physics-nodes/CCPhysicsSprite.h"
#include "ui/CocosGUI.h"
#include "headLayer.hpp"
#include "TipsLayer.hpp"

using namespace cocos2d::ui;
USING_NS_CC;

class HelloWorld : public cocos2d::Scene {
private:
    Sprite *edgeSpace;
    Sprite *ballLink;
    
    PhysicsWorld* m_world;
    float moveDistance;
    
    HeadLayer *headLayer;
    TipsLayer *tipsLayer;
    
    // 保存所有的格子
    std::shared_ptr<Vector<Sprite*>>  blockVec = std::make_shared<Vector<Sprite*>>();
    // 保存所有的球
    std::shared_ptr<Vector<Sprite*>>  ballVec = std::make_shared<Vector<Sprite*>>();
    // 保存出去的球
    std::shared_ptr<Vector<Sprite*>>  tempballVec = std::make_shared<Vector<Sprite*>>();
    // 保存掉下的球
    std::shared_ptr<Vector<Sprite*>>  dropTempballVec = std::make_shared<Vector<Sprite*>>();
    // 保存飞出去的球
    std::shared_ptr<Vector<Sprite*>>  outTempballVec = std::make_shared<Vector<Sprite*>>();
    
    // 记录当前格子列是否出现过白圈
    int times;
    
    void setPhyWorld(PhysicsWorld* world) {m_world=world;};
    void showParticle(Vec2 vec);
    void birthBlock();
    void birthCircle(Vec2 vec);
    void birthBall();
    void dropBall(Vec2 vec);
    void showDropBallParticle(Vec2 vec);
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    virtual void onEnter();
    virtual void update(float dt);
    bool onContactBegin(const PhysicsContact& contact);
    
    void restartGame();
    void showPauseLayer();
    void updateStart(float delta);
    
    bool onTouchBegan(Touch* tTouch,Event* eEvent);//手指按下事件
    void onTouchMoved(Touch* tTouch,Event* eEvent);//手指移动事件
    void onTouchEnded(Touch* tTouch,Event* eEvent);//手指离开事件
};

#endif // __HELLOWORLD_SCENE_H__
