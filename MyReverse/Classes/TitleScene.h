/**
 * @brief タイトルシーンのクラス
 * @author 畑祐輔
 *
 */


#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
#include "HttpConnect.h"

class TitleScene : public cocos2d::CCLayer
{
private:
   
    cocos2d::CCMenu* startMenu;
    cocos2d::CCMenu* helpMenu;
    cocos2d::CCMenu* optionMenu;
    cocos2d::CCMenu* moreMenu;
    
    /**
     * ボタンの作成
     */
    void makeButtons();
    
    /**
     * スタートボタンの作成
     * @param pTexture スタートボタンの画像が含まれているテクスチャ
     * @param buttonWidth ボタンの横幅
     * @param buttonHeight ボタンの縦幅
     */
    void makeStartButton(cocos2d::CCTexture2D* pTexture,float buttonWidth,float buttonHeight);
    
    /**
     * ヘルプボタンの作成
     * @param pTexture ヘルプボタンの画像が含まれているテクスチャ
     * @param buttonWidth ボタンの横幅
     * @param buttonHeight ボタンの縦幅
     */
    void makeHelpButton(cocos2d::CCTexture2D* pTexture,float buttonWidth,float buttonHeight);
    
    /**
     * オプションボタンの作成
     * @param pTexture オプションボタンの画像が含まれているテクスチャ
     * @param buttonWidth ボタンの横幅
     * @param buttonHeight ボタンの縦幅
     */
    void makeOptionButton(cocos2d::CCTexture2D* pTexture,float buttonWidth,float buttonHeight);
    
    /**
     * moreボタンの作成
     * @param pTexture moreボタンの画像が含まれているテクスチャ
     * @param buttonWidth ボタンの横幅
     * @param buttonHeight ボタンの縦幅
     */
    void makeMoreButton(cocos2d::CCTexture2D* pTexture,float buttonWidth,float buttonHeight);
    
    /**
     * 背景の描画
     */
    void makeBackGround();
    
    /**
     * ロゴの描画
     */
    void makeLogo();
    
    /**
     * スタートボタンがタッチされた際の処理
     * @param pSender
     */
    void clickedStart(CCObject* pSender);
    
    /**
     * ヘルプボタンがタッチされた際の処理
     * @param pSender 
     */
    void clickedHelp(CCObject* pSender);
    
    /**
     * オプションボタンがタッチされた際の処理
     * @param pSender
     */
    void clickedOption(CCObject* pSender);
    
    /**
     * サーバーからのリクエスト返ってきた際の処理
     */
    void onRequestCompleted(cocos2d::extension::CCHttpClient *client, cocos2d::extension::CCHttpResponse *response);
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(TitleScene);
};


#endif 
