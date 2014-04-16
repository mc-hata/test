/**
 * @brief CPUとプレイヤーが対戦するシーンのクラス
 * @author 畑祐輔
 *
 */

#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Sound.h"
#include "Koma.h"
#include "TimeManager.h"
#include "Grid.h"

class PlayScene : public cocos2d::CCLayer
{
private:
    
    static const int WIN = 0;
    static const int LOSE = 1;
    static const int DRAW = 2;
    
    TimeManager* m_timeManager;
    
    bool m_isVibration;
    
    //盤面の状態の配列
    int** m_gridState;
    //ターン
    int m_turn;
    //パス回数
    int m_passCount;
    
    /**
     * サウンドの初期化処理
     */
    void initSound();
    
    /**
     * 背景画像の描画
     */
    void drawBackGround();
    
    /**
     * 盤面の初期化処理
     */
    void initGrid();
    
    /**
     * CPUのターンの処理
     */
    void cpuTurn();
    
    /**
     * ゲーム終了の判定
     * @return 終了フラグ
     */
    bool isGameEnd();
    
    /**
     * ゲーム終了時の処理
     */
    void gameEnd();
    
    /**
     * 現在のターンのプレイヤーの駒の色を返す
     * @return 駒の色 
     */
    int getTurn();
    
    
    
public:
    
    cocos2d::CCSpriteBatchNode* m_blackNode;
    cocos2d::CCSpriteBatchNode* m_whiteNode;
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(PlayScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch,cocos2d::CCEvent* pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    
};



#endif
