/**
 * @brief シークバーを表示するクラス
 * @author 畑祐輔
 *
 */

#ifndef __SEEK_BAR_H__
#define __SEEK_BAR_H__

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
    
    /**
     * シークバーの再描画
     * @param touchPoint タッチを行った座標
     * @return シークバーのメモリ位置(0 ~ 1.0)
     */
    float redrawSeekBar(cocos2d::CCPoint touchPoint);
    
    int m_listenerTag;

public:
    virtual bool init();
    static cocos2d::CCLayer* seekBar();
    CREATE_FUNC(SeekBar);
    
    /**
     * シークバーの作成
     * @param frontResource シークバーの前面
     * @param backResource シークバーの背景
     * @param point シークバーを描画する座標
     * @param progress シークバーのメモリ位置(0 ~ 1.0)
     */
    void createSeekBar(char* frontResource,char* backResource,cocos2d::CCPoint point,float progress);
    
    /**
     * シークバーの位置を返すリスナーの登録
     * @param listener リスナー
     * @param tag シークバーのタグ
     */
    void setSeekBarListener(SeekBarListener* listener,int tag);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

};

#endif 
