/**
 * @brief サウンド関連の処理を行うクラス
 * @author 畑祐輔
 *
 */

#ifndef __SOUND_H__
#define __SOUND_H__

#include <iostream>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

class Sound
{
public:
    /**
     * SEのボリュームを設定
     * @param volume 音量
     */
    static void setSEVolume(float volume);
    
    /**
     * SEのプリロードを行う
     * @param seName SEのファイル名
     */
    static void preloadSE(cocos2d::CCString* seName);
    
    /**
     * SEの再生を行う
     * @param seName SEのファイル名
     */
    static void playSE(cocos2d::CCString* seName);
    
    /**
     * BGMのボリュームを設定
     * @param volume 音量
     */
    static void setMusicVolume(float volume);
    
    /**
     * BGMのプリロードを行う
     * @param musicName BGMのファイル名
     */
    static void preloadMusic(cocos2d::CCString* musicName);
    
    /**
     * BGMの再生を行う
     * @param seName BGMのファイル名
     */
    static void playMusic(cocos2d::CCString* musicName,bool loop);
    
    /**
     * BGMの停止を行う
     */
    static void stopMusic();
    
    /**
     * BGMの一時停止を行う
     */
    static void pauseMusic();
    
    /**
     * BGMの再生の再開を行う
     */
    static void resumeMusic();
};

#endif
