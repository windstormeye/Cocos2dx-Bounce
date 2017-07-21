#include "HelloWorldScene.h"
#include "iostream"
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include "gameOverScene.hpp"

using namespace std;
USING_NS_CC;

// 是否为第一次触摸
static bool isBegin;
// 是否碰撞过格子
static bool isBoom;
// 当前小球是否处于活跃状态
static bool isActivity;
// 开始触摸时的Y值
static Vec2 touchBegin;
// 球链是否在显示
static bool isShow;
// 是否有小球发射出去
static bool isShoot;

// 当前成绩
int currentLevelNum;
Vec2 currentBall;

// 当前球链放大倍数
float ballLinkScale;

Scene* HelloWorld::createScene()
{
    isBegin = true;
    isBoom = false;
    isActivity = false;
    isShoot = false;
    isShow = false;
    currentLevelNum = 1;
    touchBegin = Vec2(0, 0);
    currentBall = Vec2(0, 0);
    //创建有物理空间的场景
    Scene* scene=Scene::createWithPhysics();
    //设置Debug模式
//  x  scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    HelloWorld* layer=HelloWorld::create();
    //把空间保持我们创建的层中，就是上面所说m_world的作用，方便后面设置空间的参数
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

void int2str(const int &int_temp,std::string &string_temp)
{
    std::stringstream stream;
    stream<<int_temp;
    string_temp=stream.str();   //此处也可以用 stream>>string_temp
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    Size visibleSize=Director::getInstance()->getWinSize();
    
    headLayer = HeadLayer::create();
    this->addChild(headLayer, 10);
    headLayer->setPosition(Vec2(0, visibleSize.height - 128));
    headLayer->setContentSize(Size(visibleSize.width, 128));
    string levelString = "";
    int2str(currentLevelNum, levelString);
    headLayer->changeCurrentLevelLabelText(levelString);
    // 设定滑动距离为1
    moveDistance = 1;
    
    // Scene背景
    auto cclayer = LayerColor::create(Color4B(28, 28, 28, 255));
    this->addChild(cclayer);
    
    this->scheduleUpdate();
    
    // 初始化格子
    birthBlock();
    // 初始化小球
    birthBall();
    
    // 创建球链
    ballLink = Sprite::create("res/bababa.png");
    this->addChild(ballLink, 2000);
    // 设置锚点
    ballLink->setAnchorPoint(Vec2(0.5, 0.05));
    ballLink->setVisible(false);
    
    //创建一个盒子，用来碰撞
    edgeSpace = Sprite::create();
    edgeSpace->setContentSize(Size(visibleSize.width, visibleSize.height * 0.8 - 128));
    edgeSpace->setPosition(Vec2(0, visibleSize.height * 0.2));
    PhysicsBody* boundBody=PhysicsBody::createEdgeBox(Size(edgeSpace->getContentSize().width, edgeSpace->getContentSize().height + 10),PhysicsMaterial(1.0f,1.0f,0.0f), 5, Vec2(edgeSpace->getContentSize().width / 2,edgeSpace->getContentSize().height / 2));
    boundBody->setCategoryBitmask(0x0001);
    boundBody->setCollisionBitmask(0x0001);
    boundBody->setContactTestBitmask(0x0001);
    edgeSpace->setPhysicsBody(boundBody);
    this->addChild(edgeSpace);
    edgeSpace->setTag(2000);
    
    // 创建地面层
    auto groundLayer = LayerColor::create(Color4B(38, 38, 38, 255), visibleSize.width, visibleSize.height * 0.2);
    this->addChild(groundLayer);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    // 给整个页面设置监听
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    auto warningLabel = Label::create();
    warningLabel->setString("遇到异常情况，请重新开始");
    warningLabel->setColor(Color3B(68, 68, 68));
    warningLabel->setSystemFontSize(28);
    warningLabel->setPosition(Vec2(visibleSize.width / 2, 28));
    groundLayer->addChild(warningLabel);
    
    return true;
}

void HelloWorld::birthBall() {
    Size visibleSize=Director::getInstance()->getWinSize();
    
    // 创建小球
    auto ball = Sprite::create("res/ball.png");
    // 球为16像素
    if (tempballVec->size() != 0) {
        auto tempBall = tempballVec->at(0);
        ball->setPosition(tempBall->getPosition().x, tempBall->getPosition().y);
    } else {
        ball->setPosition(visibleSize.width/2, visibleSize.height * 0.2 + 16);
    }
    //创建物体，并且物体的形状为圆形，第一参数为半径，第二个参数为物体材质
    //第三个参数为边的厚度,就是在Debug模式下看到的物体外面线条的厚度，默认为0
    PhysicsBody* ballBodyOne=PhysicsBody::createCircle(ball->getContentSize().width/2);
    //是否设置物体为静态
    ballBodyOne->setDynamic(false);
    //设置物体的恢复力
    ballBodyOne->getShape(0)->setRestitution(1.0f);
    //设置物体的摩擦力
    ballBodyOne->getShape(0)->setFriction(0.0f);
    //设置物体密度
    ballBodyOne->getShape(0)->setDensity(1.0f);
    //设置物体是否受重力系数影响
    ballBodyOne->setGravityEnable(false);
    // 设置相关掩码
    ballBodyOne->setCategoryBitmask(0x0001);
    ballBodyOne->setCollisionBitmask(0x0001);
    ballBodyOne->setContactTestBitmask(0x0001);
    //把物体添加到精灵中
    ball->setPhysicsBody(ballBodyOne);
    // no为小球未发射出去，yes为发射出去
    ball->setName("no");
    ballVec->pushBack(ball);
    //设置标志
    ball->setTag(1000);
    this->addChild(ball);
}

void HelloWorld::dropBall(Vec2 vec) {
    Size visibleSize=Director::getInstance()->getWinSize();
    auto ball = Sprite::create("res/greenBall.png");
    ball->setPosition(vec.x, vec.y);
    // no为小球未发射出去，yes为发射出去
    ball->setName("no");
    dropTempballVec->pushBack(ball);
    ball->setTag(1000);
    this->addChild(ball);
    // 先不给小球设置物理身体
    ActionInterval *forward = MoveTo::create(0.7, Vec2(vec.x, visibleSize.height * 0.2 + 16));
    ball->runAction(forward);
}

void HelloWorld::birthCircle(Vec2 vec) {
    Sprite *block = Sprite::create("res/circle1.png");
    block->setName("res/circle1.png");
    blockVec->pushBack(block);
    block->setPosition(vec.x, vec.y);
    // 设置Wie盒子
//    PhysicsBody *blockBody = PhysicsBody::createBox(Size(85, 85));
    PhysicsBody *blockBody = PhysicsBody::createCircle(block->getContentSize().width / 2);
    //是否设置物体为静态
    blockBody->setDynamic(false);
    //设置物体的恢复力
    blockBody->getShape(0)->setRestitution(1.0f);
    //设置物体的摩擦力
    blockBody->getShape(0)->setFriction(0.0f);
    //设置物体密度
    blockBody->getShape(0)->setDensity(1.0f);
    // 设置相关掩码
    blockBody->setCategoryBitmask(0x0001);
    blockBody->setCollisionBitmask(0x0001);
    blockBody->setContactTestBitmask(0x0001);
    //把物体添加到精灵中
    block->setPhysicsBody(blockBody);
    //设置标志
    block->setTag((int)blockVec->getIndex(block));
    this->addChild(block);
    
    auto animation = Animation::create();
    for(int i = 1;i <= 5;i++)
    {
        string str = "res/circle";
        string tempStr = "";
        int2str(i, tempStr);
        str = str + tempStr + ".png";
        animation->addSpriteFrameWithFile(str);
    }
    animation->setDelayPerUnit(1.0f/15.0f);         // 1秒内实现10帧的播放
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);
    auto animate = Animate::create(animation);
    block->runAction(RepeatForever::create(Sequence::create(animate,NULL)));
}

void HelloWorld::birthBlock() {
    // 设置开始的格子列未出现过白圈
    times = 1;
    
    // 先把格子Y值整体下移
    for (int i = 0; i < blockVec->size(); i++) {
        auto block = blockVec->at(i);
        block->setPosition(Vec2(block->getPosition().x, block->getPosition().y - 95));
        // 如果当前格子位于地板之下
        if (block->getPosition().y < Director::getInstance()->getWinSize().height * 0.2 + 85) {
            restartGame();
            return ;
        }
    }
    
    // 判断当前的位置上是否已经存在了格子
    vector<int> vec;
    vector<int>::iterator it;
    
    float x = (Director::getInstance()->getWinSize().width - 85 * 8) / 2 + 8;
    
    int aaa = arc4random() % 8;

    if (aaa == 0) {
        aaa = 1;
    }
    
    for (int i = 0; i < aaa; i ++) {
        // 通过随机数的方式给格子确定位置
        int num = arc4random() % 8;
        // 确实该位置上为圆圈还是格子
        int isCicle = arc4random() % 2;
        
        it=find(vec.begin(),vec.end(),num);
        if (it!=vec.end()) {
            //vec中存在value值
            while (true) {
                num = arc4random() % 8;
                it=find(vec.begin(),vec.end(),num);
                if (it!=vec.end()) {
                    continue;
                } else {
                    vec.push_back(num);
                    break;
                }
            }
        } else {
            //vec中不存在value值
            vec.push_back(num);
        }
        
        auto delayTime = DelayTime::create(0.2f);
        auto func = CallFunc::create([this, num, x, isCicle, i]() mutable {
            if (isCicle && times && blockVec->size() != 0) {
                this->birthCircle(Vec2(x + 95 * num, Director::getInstance()->getWinSize().height - 255));
                this->times = 0;
            } else {
                // 随机生成格子的图片
                int k = arc4random() % 5;
                
                std::string str = "res/";
                std::string fileStr = "";
                int2str(k, fileStr);
                fileStr.append(".png");
                str.append(fileStr);
                const char* cstring = str.c_str();
                
                Sprite *block = Sprite::create(cstring);
                blockVec->pushBack(block);
                block->setPosition(x + 95 * num, Director::getInstance()->getWinSize().height - 255);
                PhysicsBody *blockBody = PhysicsBody::createBox(Size(85, 85));
                //是否设置物体为静态
                blockBody->setDynamic(false);
                //设置物体的恢复力
                blockBody->getShape(0)->setRestitution(1.0f);
                //设置物体的摩擦力
                blockBody->getShape(0)->setFriction(0.0f);
                //设置物体密度
                blockBody->getShape(0)->setDensity(1.0f);
                // 设置相关掩码
                blockBody->setCategoryBitmask(0x0001);
                blockBody->setCollisionBitmask(0x0001);
                blockBody->setContactTestBitmask(0x0001);
                //把物体添加到精灵中
                block->setPhysicsBody(blockBody);
                //设置标志
                block->setTag((int)blockVec->getIndex(block));
                std::string nameStr = "";
                int2str(k, nameStr);
                block->setName(nameStr);
                this->addChild(block);
                
            }
        });
        auto seq = Sequence::create(delayTime, func, nullptr);
        this->runAction(seq);
    }
}

void HelloWorld::onEnter()
{
    Scene::onEnter();
    //添加监听器
    auto contactListener=EventListenerPhysicsContact::create();
    //设置监听器的碰撞开始函数
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    //添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void HelloWorld::update(float dt){
    Size visibleSize=Director::getInstance()->getWinSize();
    for (int i = 0; i < ballVec->size(); i ++) {
        auto ball = ballVec->at(i);
        if (ball->getName() == "yes" && isBegin) {
            if (ball->getPosition().y < visibleSize.height * 0.2 + 21) {
                ball->getPhysicsBody()->setDynamic(false);
                // 如果容器内放的一个球以上
                if (tempballVec->size() != 0) {
                    auto tempBall = tempballVec->at(0);
                    ball->setPosition(ball->getPosition().x, visibleSize.height * 0.2 + 16);
                    // 让触底的小球回到第一个触底的小球所处的位置上
                    ActionInterval *forward = MoveTo::create(0.15, Vec2(tempBall->getPosition().x, tempBall->getPosition().y));
                    ball->runAction(forward);
                } else {
                    // 加了else，解决多个触底小球回不到第一个触底小球位置的问题
                    ball->setPosition(ball->getPosition().x, visibleSize.height * 0.2 + 16);
                }
                // 解决因为帧数太快导致多次添加小球的问题
                if (tempballVec->size() == 0) {
                    tempballVec->pushBack(ball);
                    // 一旦触底则立马设置为no
                    ball->setName("no");
                } else {
                    // 记录该ball是否已经存在
                    int isBall = 0;
                    for (int i = 0; i < tempballVec->size(); i ++) {
                        if (tempballVec->at(i) != ball) {
                            isBall ++;
                        } else {
                            // break，解决多个触底小球会在某些时候回到第一次触底小球位置时错位问题
                            // 因为isBall计算得不够准确的原因
                            break;
                        }
                    }
                    if (isBall == tempballVec->size()) {
                        tempballVec->pushBack(ball);
                        // 一旦触底则立马设置为no
                        ball->setName("no");
                    }
                }
                
                
             
                if (tempballVec->size() == ballVec->size()) {
                    auto tempBall = tempballVec->at(0);
                    for (int i = 0; i < dropTempballVec->size(); i++) {
                        auto greenball = dropTempballVec->at(i);
                        // 给掉下的小球添加物理身体
                        PhysicsBody* ballBodyOne=PhysicsBody::createCircle(ball->getContentSize().width/2);
                        ballBodyOne->setDynamic(false);
                        ballBodyOne->getShape(0)->setRestitution(1.0f);
                        ballBodyOne->getShape(0)->setFriction(0.0f);
                        ballBodyOne->getShape(0)->setDensity(1.0f);
                        ballBodyOne->setGravityEnable(false);
                        ballBodyOne->setCategoryBitmask(0x0001);
                        ballBodyOne->setCollisionBitmask(0x0001);
                        ballBodyOne->setContactTestBitmask(0x0001);
                        greenball->setPhysicsBody(ballBodyOne);
                        
                        ActionInterval *forward = MoveTo::create(0.15, Vec2(tempBall->getPosition().x, tempBall->getPosition().y));
                        greenball->runAction(forward);
                     
                        auto delayTime = DelayTime::create(i * 0.15f);
                        auto func = CallFunc::create([this, greenball]()
                        {
                            Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("res/ball.png");
                            greenball->setTexture(texture);
                        });
                        auto seq = Sequence::create(delayTime, func, nullptr);
                        this->runAction(seq);
                        ballVec->pushBack(greenball);
                    }
                    birthBlock();
                    
                    currentLevelNum ++;
                    string levelString = "";
                    int2str(currentLevelNum, levelString);
                    headLayer->changeCurrentLevelLabelText(levelString);
                    
                    // 更新历史最好成绩
                    string oldLevelString = UserDefault::getInstance()->getStringForKey("BestLevel");
                    int oldLevelNum = atoi(oldLevelString.c_str());
                    if (currentLevelNum > oldLevelNum) {
                        string bestLevelString = "";
                        int2str(currentLevelNum, bestLevelString);
                        UserDefault::getInstance()->setStringForKey("BestLevel", bestLevelString);
                        headLayer->updateBestLevelLabelText();
                    }
                    
                    isActivity = false;
                    isBegin = false;
                    dropTempballVec->clear();
                    tempballVec->clear();
                }
            }
        }
    }
}

void HelloWorld::showParticle(Vec2 vec) {
    ParticleSystem* particleSystem = ParticleSun::create();
    particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("res/boom.png"));
    this->addChild(particleSystem, 500);
    particleSystem->setPosition(vec);
    particleSystem->setSpeed(300);
    particleSystem->setScale(0.5);
    particleSystem->setLife(0.05);
    particleSystem->setDuration(0.05);
    particleSystem->setStartSize(16);
    particleSystem->setEndSize(32);
    particleSystem->setStartColor(Color4F(238, 221, 130, 255));
    particleSystem->setEndColor(Color4F(238, 221, 130, 255));
    
    // 给粒子效果设置定时器
    auto delayTime = DelayTime::create(0.5f);
    auto func = CallFunc::create([this, particleSystem]()
                                 {
                                     particleSystem->removeFromParent();
                                 });
    auto seq = Sequence::create(delayTime, func, nullptr);
    this->runAction(seq);
}

void HelloWorld::showDropBallParticle(Vec2 vec) {
    ParticleSystem* particleSystem = ParticleSun::create();
    particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("res/blockBoom.png"));
    this->addChild(particleSystem, 500);
    particleSystem->setPosition(vec);
    particleSystem->setSpeed(300);
    particleSystem->setScale(0.5);
    particleSystem->setLife(0.05);
    particleSystem->setDuration(0.05);
    particleSystem->setStartSize(16);
    particleSystem->setEndSize(32);
    particleSystem->setStartColor(Color4F(58, 177, 86, 255));
    particleSystem->setEndColor(Color4F(58, 177, 86, 255));
    
    // 给粒子效果设置定时器
    auto delayTime = DelayTime::create(0.5f);
    auto func = CallFunc::create([this, particleSystem]()
                                 {
                                     particleSystem->removeFromParent();
                                 });
    auto seq = Sequence::create(delayTime, func, nullptr);
    this->runAction(seq);
}

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
    Sprite* spriteA=(Sprite*)contact.getShapeA()->getBody()->getNode();
    Sprite* spriteB=(Sprite*)contact.getShapeB()->getBody()->getNode();
    
    // 解决两个小球争夺一个格子
    if (spriteB == NULL) {
        return false;
    }
    
    int tagA=spriteA->getTag();
    int tagB=spriteB->getTag();
    
    // 判断小球撞上的是不是白圈，spriteA和spriteB都要进行判断
    if (spriteA->getTag() == 1000 && spriteB->getName() == "res/circle1.png") {
        currentBall = spriteB->getPosition();
        blockVec->erase(spriteB->getTag());
        for (int i = 0; i < blockVec->size(); i++) {
            auto block = blockVec->at(i);
            block->setTag((int)blockVec->getIndex(block));
        }
        showDropBallParticle(currentBall);
        spriteB->removeFromParent();
        // 解决小球撞击白圈后生成的绿色小球坐标因为延时的关系导致坐标混乱
        auto delayTime = DelayTime::create(0.1f);
        auto func = CallFunc::create([this]()
                                     {
                                         dropBall(currentBall);
                                     });
        auto seq = Sequence::create(delayTime, func, nullptr);
        this->runAction(seq);
        return false;
    }
    
    if (spriteB->getTag() == 1000 && spriteA->getName() == "res/circle1.png") {
        currentBall = spriteA->getPosition();
        blockVec->erase(spriteA->getTag());
        for (int i = 0; i < blockVec->size(); i++) {
            auto block = blockVec->at(i);
            block->setTag((int)blockVec->getIndex(block));
        }
        showDropBallParticle(currentBall);
        spriteA->removeFromParent();
        // 解决小球撞击白圈后生成的绿色小球坐标因为延时的关系导致坐标混乱
        auto delayTime = DelayTime::create(0.1f);
        auto func = CallFunc::create([this]()
                                     {
                                         dropBall(currentBall);
                                     });
        auto seq = Sequence::create(delayTime, func, nullptr);
        this->runAction(seq);
        return false;
    }
    
    // 解决小球相碰
    if (tagA == 1000 && tagB == 1000) {
        return false;
    }
    
    if(tagA == 1000) {
        spriteA->setName("yes");
        isBegin = true;
        
        int index = atoi(spriteB->getName().c_str());
        // 保证删除掉的spriteB一点是方格，而不是小球
        if (index == 0 && spriteB->getTag() < 1000) {
            showParticle(spriteB->getPosition());
            blockVec->erase(spriteB->getTag());
            spriteB->removeFromParent();
            // 删除vector里的元素后，其余剩下元素都往前移动，需要重新给剩下的元素重新赋值tag
            for (int i = 0; i < blockVec->size(); i++) {
                auto block = blockVec->at(i);
                block->setTag((int)blockVec->getIndex(block));
            }
        } else {
            // 增加tagB != 2000解决小球碰撞盒子后打印找不到对应图片的垃圾log
            if (tagB != 2000) {
                std::string str = "res/";
                std::string fileStr = "";
                int2str(--index, fileStr);
                fileStr.append(".png");
                str.append(fileStr);
                const char* cstring = str.c_str();
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(cstring);
                spriteB->setTexture(texture);
                std::string nameStr = "";
                int2str(index, nameStr);
                spriteB->setName(nameStr);
            }
        }
    }
    return true;
}

bool HelloWorld::onTouchBegan(Touch* tTouch,Event* eEvent){
    if (this->getBoundingBox().containsPoint(tTouch->getLocation())){//判断触摸点是否在目标的范围内
        
        touchBegin = Vec2(tTouch->getPreviousLocation().x, tTouch->getPreviousLocation().y);
        
        return true;
    }
    return false;
}

void HelloWorld::onTouchMoved(Touch* tTouch,Event* eEvent){
    if (!isActivity) {
        auto ball = ballVec->at(0);
        ballLink->setVisible(true);
        ballLink->setPosition(Vec2(ball->getPosition().x, ball->getPosition().y + 4));
        ballLink->setRotation(-tTouch->getPreviousLocation().x * 0.5);
        if (ballLink->getRotation() < -270 || ballLink->getRotation() > -90) {
            ballLink->setVisible(false);
            isShow = false;
            return ;
        }
        
        auto sub = Vec2(touchBegin, tTouch->getPreviousLocation());
        float scale = 0;
        //上滑
        if (sub.y > moveDistance) {
            // 球链上滑操作暂不需要操作
            // 上滑就让球链消失
            ballLink->setVisible(false);
        } else
            //下滑
            if (sub.y < -moveDistance){
                // 设置最大滑动距离，当超过这个距离后固定放大倍数
                if (sub.y > -200) {
                    scale = (int)sub.y % 200 * 0.01;
                    // 固定最小放大倍数为本身大小
                    if (scale > -1) {
                        scale = -1;
                    }
                    // 固定最大放大倍数为本身三倍
                } else {
                    scale = -2;
                }
            }
        ballLink->setScale(scale, scale);
        ballLinkScale = scale;
    }
}

void HelloWorld::onTouchEnded(Touch* tTouch,Event* eEvent){
    if (!isActivity && ballLink->isVisible()) {
        ballLink->setVisible(false);
        
        int angle = 0;
        if (-ballLink->getRotation() > 180) {
            angle = (int)(-ballLink->getRotation() - 90);
        } else {
            angle = (int)(-ballLink->getRotation() - 90);
        }
        
        int toX = 300 * cos(CC_DEGREES_TO_RADIANS(angle));
        int toY = 300 * sin(CC_DEGREES_TO_RADIANS(angle));
        
        for (int i = 0; i < (int)ballVec->size(); i ++) {
            auto ball = ballVec->at(i);
            // 给小球的发射时间根据i值变化
            auto delayTime = DelayTime::create(i * 0.1f);
            auto func = CallFunc::create([this,ball, toX, toY]() {
                ball->getPhysicsBody()->setDynamic(true);
                ball->getPhysicsBody()->setVelocity(Vect(toX * 4, toY * 4));
                
            });
            auto seq = Sequence::create(delayTime, func, nullptr);
            this->runAction(seq);
        }
        
        isActivity = true;
    }
}

void HelloWorld::restartGame() {
    // 更新历史最好成绩
    string oldLevelString = UserDefault::getInstance()->getStringForKey("BestLevel");
    int oldLevelNum = atoi(oldLevelString.c_str());
    string bestLevelString = "";
    int2str(currentLevelNum, bestLevelString);
    if (currentLevelNum > oldLevelNum) {
        UserDefault::getInstance()->setStringForKey("BestLevel", bestLevelString);
        headLayer->updateBestLevelLabelText();
    }
    
    auto gameScene = GameOverScene::create();
    gameScene->setCurrentLevelNum(bestLevelString);
    Director::getInstance()->replaceScene(TransitionMoveInB::create(0.4, gameScene));
}
