

#include "TitleScene.h"
#include "PlayScene.h"
#include "OptionScene.h"
#include "PlayCpuScene.h"

using namespace cocos2d;
using namespace std;


CCScene* TitleScene::scene()
{
    CCScene* scene = CCScene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool TitleScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    makeBackGround();
    makeButtons();
    makeLogo();
    
    HttpConnect::getRequest("http://dns7.m-craft.com/app/recruit/connect_test2.php?p=xxx", this, callfuncND_selector(TitleScene::onRequestCompleted));
    
    return true;
}

void TitleScene::makeBackGround()
{
    CCDirector* director = CCDirector::sharedDirector();
    CCSize winSize = director->getWinSize();
    
    CCSprite* bg = CCSprite::create("title_bg_00@2x.png");
    bg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(bg);
}

void TitleScene::makeButtons()
{
    CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage("title_button00@2x.png");
    CCRect rect = CCRectZero;
    rect.size = pTexture->getContentSize();
    
    float buttonWidth = rect.size.width / 2.0f;
    float buttonHeight = rect.size.height / 4.0f;
    
    makeStartButton(pTexture,buttonWidth,buttonHeight);
    makeHelpButton(pTexture,buttonWidth,buttonHeight);
    makeOptionButton(pTexture,buttonWidth,buttonHeight);
    makeMoreButton(pTexture,buttonWidth,buttonHeight);
    
}

void TitleScene::makeStartButton(CCTexture2D* pTexture,float buttonWidth,float buttonHeight)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCRect startRect = CCRectMake(0, 0, buttonWidth, buttonHeight);
    CCSprite* startButton = CCSprite::createWithTexture(pTexture,startRect);
    
    CCRect startPressedRect = CCRectMake(buttonWidth,0,buttonWidth,buttonHeight);
    CCSprite* startPressedButton = CCSprite::createWithTexture(pTexture,startPressedRect);
    
    CCMenuItemSprite* startSprite = CCMenuItemSprite::create(startButton, startPressedButton, this,menu_selector(TitleScene::clickedStart));
    startSprite->setPosition(ccp(winSize.width/2.0f,winSize.height/2.0f));
    
    startMenu = CCMenu::create(startSprite,NULL);
    startMenu->setPosition(CCPointZero);
    this->addChild(startMenu);
    
    
}

void TitleScene::makeHelpButton(CCTexture2D* pTexture,float buttonWidth,float buttonHeight)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCRect helpRect = CCRectMake(0,buttonHeight,buttonWidth,buttonHeight);
    CCSprite* helpButton = CCSprite::createWithTexture(pTexture,helpRect);
    
    CCRect helpPressedRect = CCRectMake(buttonWidth,buttonHeight,buttonWidth,buttonHeight);
    CCSprite* helpPressedButton = CCSprite::createWithTexture(pTexture,helpPressedRect);
    
    CCMenuItemSprite* helpSprite = CCMenuItemSprite::create(helpButton, helpPressedButton,this,menu_selector(TitleScene::clickedHelp));
    helpSprite->setPosition(ccp(winSize.width/2.0f,winSize.height/2.0f - buttonHeight));
    
    helpMenu = CCMenu::create(helpSprite,NULL);
    helpMenu->setPosition(CCPointZero);
    this->addChild(helpMenu);
}

void TitleScene::makeOptionButton(CCTexture2D* pTexture,float buttonWidth,float buttonHeight)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCRect optionRect = CCRectMake(0,buttonHeight * 2,buttonWidth,buttonHeight);
    CCSprite* optionButton = CCSprite::createWithTexture(pTexture,optionRect);
    
    CCRect optionPressedRect = CCRectMake(buttonWidth,buttonHeight * 2,buttonWidth,buttonHeight);
    CCSprite* optionPressedButton = CCSprite::createWithTexture(pTexture,optionPressedRect);
    
    CCMenuItemSprite* optionSprite = CCMenuItemSprite::create(optionButton, optionPressedButton,this,menu_selector(TitleScene::clickedOption));
    optionSprite->setPosition(ccp(winSize.width/2.0f,winSize.height/2.0f - buttonHeight * 2));
    
    optionMenu = CCMenu::create(optionSprite,NULL);
    optionMenu->setPosition(CCPointZero);
    this->addChild(optionMenu);
}

void TitleScene::makeMoreButton(CCTexture2D* pTexture,float buttonWidth,float buttonHeight)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCRect moreRect = CCRectMake(0,buttonHeight * 3,buttonWidth,buttonHeight);
    CCSprite* moreButton = CCSprite::createWithTexture(pTexture,moreRect);
    
    CCRect morePressedRect = CCRectMake(buttonWidth,buttonHeight * 3,buttonWidth,buttonHeight);
    CCSprite* morePressedButton = CCSprite::createWithTexture(pTexture,morePressedRect);
    
    CCMenuItemSprite* moreSprite = CCMenuItemSprite::create(moreButton, morePressedButton,NULL);
    moreSprite->setPosition(ccp(winSize.width/2.0f,winSize.height/2.0f - buttonHeight * 3));
    
    moreMenu = CCMenu::create(moreSprite,NULL);
    moreMenu->setPosition(CCPointZero);
    this->addChild(moreMenu);
}

void TitleScene::clickedStart(cocos2d::CCObject *pSender)
{
    CCScene* pScene = PlayScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TitleScene::clickedHelp(cocos2d::CCObject *pSender)
{
    CCScene* pScene = PlayCpuScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void TitleScene::clickedOption(cocos2d::CCObject *pSender)
{
    CCScene* pScene = OptionScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}


void TitleScene::makeLogo()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* logo = CCSprite::create("title_koma@2x.png");
    logo->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.5 + winSize.height * 0.25));
    this->addChild(logo);
}

void TitleScene::onRequestCompleted(cocos2d::extension::CCHttpClient *client, cocos2d::extension::CCHttpResponse *response)
{
    std::string string;
    
    std::vector<char> *buffer = response->getResponseData();
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
        
        string += (*buffer)[i];
    }
    printf("\n");
    
    const char* str = string.c_str();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* responseLabel = CCLabelTTF::create(str, "arial", 48);
    responseLabel->setPosition(ccp(winSize.width * 0.5,50));
    this->addChild(responseLabel);
}

  







