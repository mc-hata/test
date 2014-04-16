/**
 * @brief 数値を計算するクラス
 * @author 畑祐輔
 *
 */

#ifndef __CALCURATOR_H__
#define __CALCURATOR_H__

#include <math.h>

class Calcurator
{

public:
    /**
     * 数値の桁数を計算
     * @param num 計算する数値
     * @return 桁数
     */
    static int getIntegerLength(int num);
    
    /**
     * 桁を指定して、数値からその桁を取り出す
     * @param num 桁を取得したい数値
     * @oaram digit 取得したい桁番号 1桁目:1 2桁目:2 ....
     * @return 桁の数値
     */
    static int getIntegerDigit(int num ,int digit);
    
};

#endif 