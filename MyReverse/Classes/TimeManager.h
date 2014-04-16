
/**
 * @brief 時間管理を行うクラス
 * @author 畑祐輔
 *
 */

#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include "cocos2d.h"

class TimeManager : public cocos2d::CCLayer
{
private:
    static const int TIME_TAG = 0;
    
    /**
     * 毎秒呼ばれ時間を加算する
     */
    void timer();
    
    /**
     *時間を表示するラベルの更新処理
     */
    void refreshTimeLabel();
    
    /**
     * 番号の画像を取得
     * @param num 番号
     * @return 指定した番号のスプライト
     */
    cocos2d::CCSprite* getNumSprite(int num);
    
    int m_time;
    
public:
    virtual bool init();
    static cocos2d::CCLayer* time();
    CREATE_FUNC(TimeManager);
    
    /**
     * 時間経過を止める
     */
    void stopTimer();
    
    /**
     * 現在の経過時間を取得
     * @return 経過時間
     */
    int getTime();
};


#endif 
