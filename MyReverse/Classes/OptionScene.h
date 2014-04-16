/**
 * @brief オプションシーンクラス
 * @author 畑祐輔
 *
 */

#ifndef __OPTION_SCENE_H__
#define __OPTION_SCENE_H__

#include "cocos2d.h"
#include "SeekBar.h"

class OptionScene : public cocos2d::CCLayer, public SeekBarListener
{
private:
    
    static const int BAR_MAX_WIDTH = 300;
    static const int BAR_MAX_HEIGHT = 18;
    
    static const int BGM = 0;
    static const int SE = 1;
    
    /**
     * CCUserDefaultから現在の設定を読み込む
     */
    void setSetting();
    
    /**
     * CCUserdDefaultに設定を書き込む
     */
    void saveSetting();
    
    /**
     * 背景の描画
     */
    void drawBackGround();
    
    /**
     * オプションウィンドウの背景の描画
     */
    void drawOptionBackGround();
    
    /**
     * オプションの描画
     */
    void drawOptions();
    
    /**
     * BGMボリュームのオプションを描画
     */
    void drawBGMVolume();
    
    /**
     * SEボリュームのオプションを描画
     */
    void drawSEVolume();
    
    /**
     * バイブレーションのオプションを描画
     */
    void drawVibrationType();
    
    /**
     * デザインのオプションを描画
     */
    void drawOptionType();
    
    /**
     * ガイドのオプションを描画
     */
    void drawGuideType();
    
    /**
     * バイブレーションのオプションがタッチされたか確認
     * @param touchPoint タッチ座標
     * @return タッチされているかのフラグ
     */
    bool checkTouchVibration(cocos2d::CCPoint touchPoint);
    
    /**
     * デザインのオプションがタッチされたか確認
     * @param touchPoint タッチ座標
     * @return タッチされているかのフラグ
     */
    bool checkTouchDesign(cocos2d::CCPoint touchPoint);
    
    /**
     * ガイドのオプションがタッチされたか確認
     * @param touchPoint タッチ座標
     * @return タッチされているかのフラグ
     */
    bool checkTouchGuide(cocos2d::CCPoint touchPoint);
    
    float m_bgmVolume;
    float m_seVolume;
    bool m_isVibration;
    bool m_isNormal;
    bool m_isGuide;
    
    cocos2d::CCSprite* m_bgmBar;
    cocos2d::CCSprite* m_seBar;
    cocos2d::CCSprite* m_onVibrationSprite;
    cocos2d::CCSprite* m_offVibrationSprite;
    cocos2d::CCSprite* m_normalDesignSprite;
    cocos2d::CCSprite* m_catDesignSprite;
    cocos2d::CCSprite* m_onGuideSprite;
    cocos2d::CCSprite* m_offGuideSprite;
    
    cocos2d::CCRect m_bgmRect;
    cocos2d::CCRect m_seRect;
    cocos2d::CCRect m_onVibrationRect;
    cocos2d::CCRect m_offVibrationRect;
    cocos2d::CCRect m_normalDesignRect;
    cocos2d::CCRect m_catDesignRect;
    cocos2d::CCRect m_onGuideRect;
    cocos2d::CCRect m_offGuideRect;
       
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(OptionScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch,cocos2d::CCEvent* pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch,cocos2d::CCEvent* pEvent);
    
    virtual void SeekStart(float progress,int tag);
    virtual void SeekMove(float progress,int tag);
	virtual void SeekEnd(float progress,int tag);
};

#endif 
