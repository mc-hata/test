/**
 * @brief グリッドの処理を行うクラス
 * @author 畑祐輔
 *
 */

#ifndef __GRID_H__
#define __GRID_H__

#include "Koma.h"
#include "cocos2d.h"

class Grid
{
public:
    //盤面の大きさ
    static const int GRID_WIDTH = 8;
    static const int GRID_HEIGHT = 8;
    static const int GRID_NUM = 64;
    //盤面の状態
    static const int NONE = 0;
    static const int BLACK = 1;
    static const int WHITE = 2;
    
    /**
     * 盤面に駒がおける場所があるか調べる
     * @param turn 現在のターンの駒の色
     * @param gridState 盤面の状態
     * @return 盤面に置ける場所があるかのフラグ
     */
    static bool canDropGrid(int turn,int** gridState);
    
    /**
     * 指定されたマスにすでに駒が存在するか調べる
     * @param gridState 盤面の状態
     * @param gridX グリッドのX座標
     * @param gridY グリッドのY座標
     * @return 駒が置けるかのフラグ
     */
    static bool isKoma(int** gridState,int gridX,int gridY);
    
    /**
     * 指定されたマスに駒が置けるか調べる
     * @param layer 駒を置くレイヤー
     * @param turn 現在のターンの駒の色
     * @param gridState 盤面の状態
     * @param gridX グリッドのX座標
     * @param gridY グリッドのY座標
     * @return 指定されたマスに駒が置けるかのフラグ
     */
    static bool canDropMass(cocos2d::CCLayer* layer,int turn, int **gridState,int gridX,int gridY);
    
    /**
     * 指定されたマスの指定方向に対して駒が置ける状態であるか調べる
     * @param gridState 盤面の状態
     * @param gridX グリッドのX座標
     * @param gridY グリッドのY座標
     * @param vecX 調べるX方向
     * @param vecY 調べるY方向
     * @return 駒が置けるかのフラグ
     */
    static bool canDropKoma(int turn,int** gridState,int gridX, int gridY, int vecX, int vecY);
    
    /**
     * 指定した方向を調べ駒を裏返す処理
     * @param layer 駒を置くレイヤー
     * @param turn 現在のターンの駒の色
     * @param gridState 盤面の状態
     * @param gridX グリッドのX座標
     * @param gridY グリッドのY座標
     * @param vecX 調べるX方向
     * @param vecY 調べるY方向
     */
    static void refreshKoma(cocos2d::CCLayer* layer,int turn,int** gridState,int gridX,int gridY,int vecX,int vecY);


};

#endif