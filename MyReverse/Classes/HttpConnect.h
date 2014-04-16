/**
 * @brief サーバーとの通信を行うクラス
 * @author 畑祐輔
 *
 */

#ifndef __HTTP_CONNECT_H__
#define __HTTP_CONNECT_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class HttpConnect
{
public:
    /**
     * サーバーに通信を行う
     * @param url サーバーのURL
     * @param target 通信の完了を知らせるクラス
     * @param selector 通信の完了を知らせる関数
     */
    static void getRequest(char* url,cocos2d::CCObject* target,cocos2d::SEL_CallFuncND selector);
};

#endif 
