
#include "SeekBar.h"

USING_NS_CC;

CCLayer* SeekBar::seekBar()
{
    SeekBar* layer = SeekBar::create();
    
    return layer;
}

bool SeekBar::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    m_touchSeekBar = false;
    
    return true;
}

void SeekBar::createSeekBar(char* frontResource,char* backResource,CCPoint point)
{
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    m_resourece = frontResource;
    
    CCSprite* backBar = CCSprite::create(backResource);
    backBar->setPosition(point);
    this->addChild(backBar);

    
    CCSprite* frontBar = CCSprite::create(frontResource);
    frontBar->setTag(TAG_SEEK_BAR);
    frontBar->setPosition(point);
    this->addChild(frontBar);
    
    CCSize seekBarSize = frontBar->getContentSize();
    
    m_seekBarRect = CCRectMake(point.x - seekBarSize.width * 0.5, point.y - seekBarSize.height * 0.5, seekBarSize.width, seekBarSize.height);
}

float SeekBar::redrawSeekBar(CCPoint touchPoint)
{
    
    float SeekBarWidth = m_seekBarRect.size.width;
    float SeekBarHeight = m_seekBarRect.size.height;
    
    float diffX = touchPoint.x - m_seekBarRect.getMinX();
    float raito = diffX / SeekBarWidth;
    if(raito > 1.0)
    {
        raito = 1.0;
        diffX = SeekBarWidth;
    }
    else if(raito < 0)
    {
        raito = 0;
        diffX = 0;
    }
    
    this->removeChildByTag(TAG_SEEK_BAR);
    
    CCRect newSeekBarRect = CCRectMake(0,0, SeekBarWidth * raito, SeekBarHeight);
    CCSprite* seekBar = CCSprite::create(m_resourece,newSeekBarRect);
    seekBar->setPosition(ccp(m_seekBarRect.getMidX() - (SeekBarWidth - diffX) * 0.5,m_seekBarRect.getMidY()));
    seekBar->setTag(TAG_SEEK_BAR);
    this->addChild(seekBar);
    
    return raito;
}

void SeekBar::setSeekBarListener(SeekBarListener *listener)
{
    m_listener = listener;
}

bool SeekBar::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());
    
    if(m_seekBarRect.containsPoint(touchPoint))
    {
        m_touchSeekBar = true;
        float progress = redrawSeekBar(touchPoint);
        
        if(m_listener != NULL)
        {
            m_listener->SeekStart(progress);
        }

        return true;
    }
    
    return false;
}

void SeekBar::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_touchSeekBar)
    {
        return;
    }
    
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());
    float progress = redrawSeekBar(touchPoint);
    
    if(m_listener != NULL)
    {
        m_listener->SeekMove(progress);
    }

}

void SeekBar::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_touchSeekBar = false;
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());
    float progress = redrawSeekBar(touchPoint);
    
    if(m_listener != NULL)
    {
        m_listener->SeekEnd(progress);
    }
}