

#include "Vibrate.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>


#define CLASS_NAME "com/mcraft/test/MyReverse"

using namespace std;
using namespace cocos2d;


void Vibrate::vibrate()
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "func1", "()V")) {
    
        t.env->CallStaticVoidMethod(t.classID, t.methodID);

        t.env->DeleteLocalRef(t.classID);
    }
}