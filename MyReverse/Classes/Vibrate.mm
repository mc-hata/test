
#include "Vibrate.h"
#include "cocos2d.h"
#import <AudioToolbox/AudioToolbox.h>

USING_NS_CC;

void Vibrate::vibrate()
{
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}