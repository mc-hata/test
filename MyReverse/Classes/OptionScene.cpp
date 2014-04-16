
#include "OptionScene.h"
#include "TitleScene.h"
#include "Key.h"

using namespace cocos2d;

CCScene* OptionScene::scene()
{
    CCScene* scene = CCScene::create();
    OptionScene* layer = OptionScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool OptionScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    setSetting();
    drawBackGround();
    drawOptionBackGround();
    drawOptions();
    
    return true;

}

void OptionScene::setSetting()
{
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    
    m_bgmVolume = userDefault->getFloatForKey(BGM_VOLUME, 0.5);
    m_seVolume = userDefault->getFloatForKey(SE_VOLUME,0.5);
    m_isVibration = userDefault->getBoolForKey(VIBRATION,true);
    m_isNormal = userDefault->getBoolForKey(DESGIN,true);
    m_isGuide = userDefault->getBoolForKey(GUIDE,true);
}

void OptionScene::saveSetting()
{
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    
    userDefault->setFloatForKey(BGM_VOLUME, m_bgmVolume);
    userDefault->setFloatForKey(SE_VOLUME, m_seVolume);
    userDefault->setBoolForKey(VIBRATION, m_isVibration);
    userDefault->setBoolForKey(DESGIN, m_isNormal);
    userDefault->setBoolForKey(GUIDE, m_isGuide);
}

void OptionScene::drawBackGround()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("title_bg_00@2x.png");
    bg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(bg);
}

void OptionScene::drawOptionBackGround()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("option_bg@2x.png");
    bg->setPosition(ccp(winSize.width * 0.5,winSize.height*0.5));
    this->addChild(bg);
}

void OptionScene::drawOptions()
{
    drawBGMVolume();
    drawSEVolume();
    drawVibrationType();
    drawOptionType();
    drawGuideType();
}

void OptionScene::drawBGMVolume()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    SeekBar* seekBar = (SeekBar*)SeekBar::seekBar();
    seekBar->createSeekBar("option_bar@2x.png", NULL, ccp(winSize.width * 0.5 + 48 , winSize.height * 0.5 + 237),m_bgmVolume);
    seekBar->setSeekBarListener(this,BGM);
    this->addChild(seekBar);
}

void OptionScene::drawSEVolume()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    SeekBar* seekBar = (SeekBar*)SeekBar::seekBar();
    seekBar->createSeekBar("option_bar@2x.png", NULL, ccp(winSize.width * 0.5 + 48 , winSize.height * 0.5 + 172),m_seVolume);
    seekBar->setSeekBarListener(this,SE);
    this->addChild(seekBar);
}

void OptionScene::drawVibrationType()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCTexture2D* onOffTexture = CCTextureCache::sharedTextureCache()->addImage("option_onoff@2x.png");
    CCRect onOffRect = CCRectZero;
    onOffRect.size = onOffTexture->getContentSize();
    
    float width = onOffRect.size.width * 0.5;
    float height = onOffRect.size.height;
    
    CCRect onRect = CCRectMake(0, 0, width, height);
    m_onVibrationSprite = CCSprite::createWithTexture(onOffTexture,onRect);
    m_onVibrationSprite->setPosition(ccp(winSize.width * 0.5 - width +18, winSize.height * 0.5 + 35));
    this->addChild(m_onVibrationSprite);
    if(!m_isVibration){
        m_onVibrationSprite->setVisible(false);
    }
    m_onVibrationRect = CCRectMake(winSize.width * 0.5 - width +18 - width * 0.5, winSize.height * 0.5 + 35 - height * 0.5, width, height);
    
    CCRect offRect = CCRectMake(width, 0, width, height);
    m_offVibrationSprite = CCSprite::createWithTexture(onOffTexture,offRect);
    m_offVibrationSprite->setPosition(ccp(winSize.width * 0.5 + width -18, winSize.height * 0.5 + 35));
    this->addChild(m_offVibrationSprite);
    if(m_isVibration){
        m_offVibrationSprite->setVisible(false);
    }
    m_offVibrationRect = CCRectMake(winSize.width * 0.5 + width -18 -width * 0.5, winSize.height * 0.5 + 35 - height * 0.5, width, height);

}

void OptionScene::drawOptionType()
{
    CCTexture2D* typeTexture = CCTextureCache::sharedTextureCache()->addImage("option_type@2x.png");
    CCRect typeRect = CCRectZero;
    typeRect.size = typeTexture->getContentSize();
    
    float width = typeRect.size.width * 0.5;
    float height = typeRect.size.height;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCRect normalRect = CCRectMake(0,0,width,height);
    m_normalDesignSprite = CCSprite::createWithTexture(typeTexture,normalRect);
    m_normalDesignSprite->setPosition(ccp(winSize.width * 0.5 - 250 + 56 + width * 0.5,410 - height * 0.5));
    this->addChild(m_normalDesignSprite);
    if(!m_isNormal){
        m_normalDesignSprite->setVisible(false);
    }
    m_normalDesignRect = CCRectMake(winSize.width * 0.5 - 250 + 56 + width * 0.5 - width * 0.5, 410 - height * 0.5 - width * 0.5, width, height);
    
    CCRect catRect = CCRectMake(width, 0, width, height);
    m_catDesignSprite = CCSprite::createWithTexture(typeTexture,catRect);
    m_catDesignSprite->setPosition(ccp(winSize.width * 0.5 + 250 - 56 - width * 0.5,410 - height * 0.5));
    this->addChild(m_catDesignSprite);
    if(m_isNormal){
        m_catDesignSprite->setVisible(false);
    }
    m_catDesignRect = CCRectMake(winSize.width * 0.5 + 250 - 56 - width * 0.5 - width * 0.5, 410 - height * 0.5 - height * 0.5, width, height);
}

void OptionScene::drawGuideType()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCTexture2D* onOffTexture = CCTextureCache::sharedTextureCache()->addImage("option_onoff@2x.png");
    CCRect onOffRect = CCRectZero;
    onOffRect.size = onOffTexture->getContentSize();
    
    float width = onOffRect.size.width * 0.5;
    float height = onOffRect.size.height;
    
    CCRect onRect = CCRectMake(0, 0, width, height);
    m_onGuideSprite = CCSprite::createWithTexture(onOffTexture,onRect);
    m_onGuideSprite->setPosition(ccp(winSize.width * 0.5 - width +18, winSize.height * 0.5 - 283));
    this->addChild(m_onGuideSprite);
    if(!m_isGuide){
        m_onGuideSprite->setVisible(false);
    }
    m_onGuideRect = CCRectMake(winSize.width * 0.5 - width +18 - width * 0.5, winSize.height * 0.5 - 283 - height * 0.5, width, height);
    
    CCRect offRect = CCRectMake(width, 0, width, height);
    m_offGuideSprite = CCSprite::createWithTexture(onOffTexture,offRect);
    m_offGuideSprite->setPosition(ccp(winSize.width * 0.5 + width -18, winSize.height * 0.5 - 283));
    this->addChild(m_offGuideSprite);
    if(m_isGuide){
        m_offGuideSprite->setVisible(false);
    }
    m_offGuideRect = CCRectMake(winSize.width * 0.5 + width -18 - width + 0.5, winSize.height * 0.5 - 283 - height * 0.5, width, height);
}

bool OptionScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void OptionScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    if( !checkTouchVibration(touchPoint) && !checkTouchDesign(touchPoint) && !checkTouchGuide(touchPoint))
    {
        CCScene* pScene = TitleScene::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

bool OptionScene::checkTouchVibration(CCPoint touchPoint)
{
    if(m_onVibrationRect.containsPoint(touchPoint) && !m_isVibration)
    {
        m_isVibration = true;
        m_onVibrationSprite->setVisible(true);
        m_offVibrationSprite->setVisible(false);
        saveSetting();
        return true;
    }
    else if(m_offVibrationRect.containsPoint(touchPoint) && m_isVibration)
    {
        m_isVibration = false;
        m_onVibrationSprite->setVisible(false);
        m_offVibrationSprite->setVisible(true);
        saveSetting();
        return true;
    }
    return false;
}

bool OptionScene::checkTouchDesign(CCPoint touchPoint)
{
    if(m_normalDesignRect.containsPoint(touchPoint) && !m_isNormal)
    {
        m_isNormal = true;
        m_normalDesignSprite->setVisible(true);
        m_catDesignSprite->setVisible(false);
        saveSetting();
        return true;
    }
    else if(m_catDesignRect.containsPoint(touchPoint) && m_isNormal)
    {
        m_isNormal = false;
        m_normalDesignSprite->setVisible(false);
        m_catDesignSprite->setVisible(true);
        saveSetting();
        return true;
    }
    return false;
}

bool OptionScene::checkTouchGuide(CCPoint touchPoint)
{
    if(m_onGuideRect.containsPoint(touchPoint) && !m_isGuide)
    {
        m_isGuide = true;
        m_onGuideSprite->setVisible(true);
        m_offGuideSprite->setVisible(false);
        saveSetting();
        return true;
    }
    else if(m_offGuideRect.containsPoint(touchPoint) && m_isGuide)
    {
        m_isGuide = false;
        m_onGuideSprite->setVisible(false);
        m_offGuideSprite->setVisible(true);
        saveSetting();
        return true;
    }
    return false;
}

void OptionScene::SeekStart(float progress,int tag)
{
    
}

void OptionScene::SeekMove(float progress,int tag)
{
    
}

void OptionScene::SeekEnd(float progress,int tag)
{
    if(tag == BGM)
    {
        m_bgmVolume = progress;
        saveSetting();
        
        CCLog("bgm progress : %f" , progress);
    }
    else if(tag == SE)
    {
        m_seVolume = progress;
        saveSetting();
        
        CCLog("se progress : %f" , progress);
    }
}



