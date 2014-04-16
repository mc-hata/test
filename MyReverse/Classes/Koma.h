/**
 * @brief 駒の動作処理を行うクラス
 * @author 畑祐輔
 *
 */

#ifndef __KOMA_H__
#define __KOMA_H__

#include "cocos2d.h"
#include "Grid.h"
#include "PlayCpuScene.h"

class Koma{
public:
    
    //駒の大きさ
    static const int KOMA_WIDTH = 76;
    static const int KOMA_HEIGHT = 76;
    
    static const int NUM_TAG = 0;
    
    /**
     * 指定したグリッドの座標を返す
     * @param gridX グリッドのX座標
     * @param gridY グリッドのY座標
     * @return 指定されたグリッドの座標
     */
    static cocos2d::CCPoint getKomaPoint(int gridX,int gridY);
    
    /**
     * 駒を描画する
     * @param layer 駒を描画したいレイヤー
     * @param turn 描画したい駒の色
     * @param komaPoint 描画する駒の位置
     */
    static void dropKoma(cocos2d::CCLayer* layer,int turn,cocos2d::CCPoint komaPoint);
    
    /**
     * 黒の駒の総数を計算
     * @param gridState 盤面の駒の状態
     * @return 黒の駒の総数
     */
    static int getBlackNum(int** gridState);
    
    /**
     * 白の駒の総数を計算
     * @param gridState 盤面の駒の状態
     * @return 白の駒の総数
     */
    static int getWhiteNum(int** gridState);
    
    /**
     * 駒の総数を計算
     * @param gridState 盤面の駒の状態
     * @return 駒の総数
     */
    static int getAllNum(int** gridState);
    
    /**
     * 駒の数を表示するラベルの更新処理
     * @param layer ラベルを表示するレイヤー
     * @param blackNum 黒の駒の総数
     * @param whiteNum 白の駒の総数
     */
    static void refreshKomaNum(cocos2d::CCLayer* layer,int blackNum,int whiteNum);
    
    /**
     * 指定したグリッドのRectを計算
     * @param gridX グリッドのX座標
     * @param gridY グリッドのY座標
     * @return グリッドのRect
     */
    static cocos2d::CCRect getKomaRect(int gridX, int gridY);
    
    /**
     * 指定した番号と対応したスプライトを返す
     * @param num 取得したい番号
     * @return 番号のスプライト
     */
    static cocos2d::CCSprite* getNumSprite(int num);
    
    
    
  
    
};

#endif 
