/**
 * @brief CPU VS CPUの対戦を行うクラス
 * @author 畑祐輔
 *
 */

#ifndef __PLAY_CPU_SCENE_H__
#define __PLAY_CPU_SCENE_H__

#include "cocos2d.h"
#include "Grid.h"
#include "Koma.h"
#include "Sound.h"
#include "TimeManager.h"

class PlayCpuScene : public cocos2d::CCLayer
{
private:
    
    static const int WIN = 0;
    static const int LOSE = 1;
    static const int DRAW = 2;
    
    bool m_isVibration;
    
    //盤面の状態の配列
    int** m_gridState;
    //ターン
    int m_turn;
    //パス回数
    int m_passCount;
    
    TimeManager* m_timeManager;
    
    /**
     * サウンドの初期化
     */
    void initSound();
    
    /**
     * 背景画像の秒が
     */
    void drawBackGround();
    
    /**
     * 盤面の初期化
     */
    void initGrid();
    
    /**
     * CPUのターンの処理
     */
    void turn();
    
    /**
     * ゲームの終了をチェック
     * @return ゲーム終了のフラグ
     */
    bool isGameEnd();
    
    /**
     * ゲーム終了の処理
     */
    void gameEnd();
    
    /**
     * 現在のターンの色を取得
     * @return  ターンの駒の色
     */
    int getTurn();
    
public:
    static cocos2d::CCScene* scene();
    virtual bool init();
    CREATE_FUNC(PlayCpuScene);
    
    cocos2d::CCSpriteBatchNode* m_blackNode;
    cocos2d::CCSpriteBatchNode* m_whiteNode;

};

#endif 
