#include "Sound.h"

using namespace CocosDenshion;
using namespace cocos2d;

void Sound::setSEVolume(float volume)
{
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

void Sound::preloadSE(CCString* seName)
{
    SimpleAudioEngine::sharedEngine()->preloadEffect(seName->getCString());
   
}

void Sound::playSE(CCString* seName)
{
    
    SimpleAudioEngine::sharedEngine()->playEffect(seName->getCString());
}

void Sound::setMusicVolume(float volume)
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

void Sound::preloadMusic(CCString* musicName)
{
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(musicName->getCString());
  
}

void Sound::playMusic(CCString* musicName,bool loop)
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(musicName->getCString(), loop);
    
}

void Sound::stopMusic()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void Sound::pauseMusic()
{
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void Sound::resumeMusic()
{
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}