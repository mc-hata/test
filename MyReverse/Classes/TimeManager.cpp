
#include "TimeManager.h"

USING_NS_CC;

CCLayer* TimeManager::time()
{
    TimeManager* layer = TimeManager::create();
    
    return layer;
}

bool TimeManager::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* beginSprite = getNumSprite(0);
    beginSprite->setPosition(ccp(winSize.width * 0.5 + 44 + 44 * 0.5,winSize.height * 0.5 + 390));
    this->addChild(beginSprite);
    
    
    this->schedule(schedule_selector(TimeManager::timer),1);
    
    return true;
}

void TimeManager::timer()
{
    m_time++;
    refreshTimeLabel();
    
}

void TimeManager::stopTimer()
{
    this->unschedule(schedule_selector(TimeManager::timer));
}

int TimeManager::getTime()
{
    return m_time;
}

void TimeManager::refreshTimeLabel()
{
    int time = (int)m_time;
    
    int onesPlace = time / 1 % 10;
    int tensPlace = time / 10 % 10;
    int hundredsPlace = time / 100 % 10;
    int thousandsPlace = time / 1000 % 10;
    
    CCSprite* tmpSprite = (CCSprite*)this->getChildByTag(TIME_TAG);
    while(tmpSprite != NULL)
    {
        this->removeChildByTag(TIME_TAG);
        tmpSprite = (CCSprite*)this->getChildByTag(TIME_TAG);
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int height = 390;
    
    CCSprite* onesSprite = getNumSprite(onesPlace);
    onesSprite->setPosition(ccp(winSize.width * 0.5 + 44 + 44 * 0.5,winSize.height * 0.5 + height));
    this->addChild(onesSprite);
    
    if(time < 10){
        return;
    }
    CCSprite* tensSprite = getNumSprite(tensPlace);
    tensSprite->setPosition(ccp(winSize.width * 0.5 + 44 - 44 * 0.5,winSize.height * 0.5 + height));
    this->addChild(tensSprite);
    
    if(time < 100)
        return;
    CCSprite* hundredsSprite = getNumSprite(hundredsPlace);
    hundredsSprite->setPosition(ccp(winSize.width * 0.5 - 44 + 44 * 0.5,winSize.height * 0.5 + height));
    this->addChild(hundredsSprite);
    
    if(time < 1000)
        return;
    CCSprite* thousandsSprite = getNumSprite(thousandsPlace);
    thousandsSprite->setPosition(ccp(winSize.width * 0.5 - 44 * 2 + 44 * 0.5,winSize.height * 0.5 + height));
    this->addChild(thousandsSprite);
    
}

CCSprite* TimeManager::getNumSprite(int num)
{
    CCTexture2D* numTexture = CCTextureCache::sharedTextureCache()->addImage("game_number@2x.png");
    CCRect textureRect = CCRectZero;
    textureRect.size = numTexture->getContentSize();
    
    float width = 48;
    
    CCRect numRect = CCRectMake(width * num , 0 , width , 52);
    CCSprite* numSprite = CCSprite::createWithTexture(numTexture,numRect);
    numSprite->setTag(TIME_TAG);
    
    return numSprite;
}
