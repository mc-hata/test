
#ifndef _SEEK_BAR_H_
#define _SEEK_BAR_H_

#include "cocos2d.h"
#include "SeekBarListener.h"

class SeekBar : public cocos2d::CCLayer
{
private:
    static const int TAG_SEEK_BAR = 0;
    
    char* m_resourece;
    bool m_touchSeekBar;
    cocos2d::CCRect m_seekBarRect;
    cocos2d::SEL_CallFunc m_selector;
    SeekBarListener* m_listener;
    
    float redrawSeekBar(cocos2d::CCPoint touchPoint);
    
public:
    virtual bool init();
    static cocos2d::CCLayer* seekBar();
    CREATE_FUNC(SeekBar);
    
    void createSeekBar(char* frontResource,char* backResource,cocos2d::CCPoint point);
    void setSeekBarListener(SeekBarListener* delegate);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

};

#endif 
