/**
 * @brief 対戦結果を表示するシーンのクラス
 * @author 畑祐輔
 *
 */
#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__

#include "cocos2d.h"

class ResultScene : public cocos2d::CCLayer
{
private:
    
    static const int WIN = 0;
    static const int LOSE = 1;
    static const int DRAW = 2;
    
    static const int NUM_WIDTH = 28;
    static const int NUM_HEIGHT = 35;
    static const int LABEL_WIDTH = 200;
    static const int LABEL_HEIGHT = 33;
    static const int SUM_WIDTH = 200;
    static const int SUM_HEIGHT = 46;

    static const int WIN_BONUS = 0;
    static const int TIME_BONUS = 1;
    static const int TROUBLE_BONUS = 2;
    static const int PATH_BONUS = 3;
    static const int SUM_SCORE = 4;
    
    cocos2d::CCDictionary* m_scores;
    
    
    /**
     * スコアを計算
     */
    void calcScore();
    
    /**
     * 背景の描画
     */
    void makeBackGround();
    
    /**
     * スコアの背景を描画
     */
    void makeScoreBoard();
    
    /**
     * スコアのラベルを秒が
     * @param scoreTexture スコアのラベルの画像が含まれるテクスチャ
     */
    void makeLabel(cocos2d::CCTexture2D* scoreTexture);
    
    /**
     * ボタンの作成
     */
    void makeButtons();
    
    /**
     * リトライボタンの作成
     * @param buttonTexture リトライボタンの画像が含まれるテクスチャ
     * @param buttonWidth ボタンの横幅
     * @param buttonHeight ボタンの縦幅
     */
    void makeRetryButton(cocos2d::CCTexture2D* buttonTexture,float buttonWidth,float buttonHeight);
    
    /**
     * タイトルボタンの作成
     * @param buttonTexture タイトルボタンの画像が含まれるテクスチャ
     * @param buttonWidth ボタンの横幅
     * @param buttonHeight ボタンの縦幅
     */
    void makeTitleButton(cocos2d::CCTexture2D* buttonTexture,float buttonWidth,float buttonHeight);
    
    /**
     * WIN,DRAW,LOSEの画像を表示
     */
    void makeWin();
    
    /*
     *リトライボタンが押された場合の処理
     */
    void clickedRetry();
    
    /*
     *タイトルボタンが押された場合の処理
     */
    void clickedTitle();
    
    /*
     * 指定された番号の画像をテクスチャから切り取って返す
     * @param numTexture 番号の画像が含まれるテクスチャ
     * @param textureRecrt テクスチャの大きさ
     * @param num 切り取りたい番号
     * @return 番号のスプライト
     */
    cocos2d::CCSprite* getNumSprite(cocos2d::CCTexture2D* numTexture,cocos2d::CCRect textureRect,int num);
    
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(ResultScene);
};

#endif 
