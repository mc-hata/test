

#include "ResultScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Calcurator.h"

using namespace cocos2d;
using namespace std;

cocos2d::CCScene* ResultScene::scene()
{
    CCScene* scene = CCScene::create();
    ResultScene* layer = ResultScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool ResultScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    calcScore();
    
    makeBackGround();
    makeScoreBoard();
    makeButtons();
    makeWin();
    
    return true;
}


void ResultScene::calcScore()
{
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    int winState = userDefault->getIntegerForKey("winState",0);
    int time = userDefault->getIntegerForKey("time", 0);
    
    m_scores = CCDictionary::create();
    
    
    
    int winBonus = 0;
    switch(winState){
        case WIN : winBonus = 10000; break;
        case LOSE : winBonus = 0; break;
        case DRAW : winBonus = 5000; break;
    }
    int timeBonus = ((5000 - 100 * time) >= 0)? (5000 - 100 * time) : 0;
    int troubleBonus = 5000;
    int pathBonus = 5000;
    int sumScore = winBonus + timeBonus + troubleBonus + pathBonus;
    
    m_scores->setObject(CCInteger::create(winBonus),WIN_BONUS);
    m_scores->setObject(CCInteger::create(timeBonus),TIME_BONUS);
    m_scores->setObject(CCInteger::create(troubleBonus),TROUBLE_BONUS);
    m_scores->setObject(CCInteger::create(pathBonus),PATH_BONUS);
    m_scores->setObject(CCInteger::create(sumScore), SUM_SCORE);

}

void ResultScene::makeBackGround()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("title_bg_00@2x.png");
    bg->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.5));
    this->addChild(bg);
}

void ResultScene::makeScoreBoard()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* scoreBoard= CCSprite::create("score_bg@2x.png");
    scoreBoard->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5));
    this->addChild(scoreBoard);
    
    
    CCTexture2D* scoreTexture = CCTextureCache::sharedTextureCache()->addImage("score_number@2x.png");
    makeLabel(scoreTexture);
    
}

void ResultScene::makeLabel(CCTexture2D* scoreTexture)
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCRect scoreTextureRect = CCRectZero;
    scoreTextureRect.size = scoreTexture->getContentSize();
    
    
    for(int i = 0; i < 4; i++)
    {
        CCRect labelRect = CCRectMake(0, LABEL_HEIGHT * i, LABEL_WIDTH, LABEL_HEIGHT);
        CCSprite* labelSprite = CCSprite::createWithTexture(scoreTexture,labelRect);
        labelSprite->setPosition(ccp(winSize.width * 0.5 - 100,winSize.height * 0.5 + 100 -NUM_HEIGHT * i));
        this->addChild(labelSprite);
        
        
        int score = 0;
        
        if(i == WIN_BONUS){
            score = ((CCInteger*)m_scores->objectForKey(WIN_BONUS))->getValue();
        }else if( i == TIME_BONUS){
            score = ((CCInteger*)m_scores->objectForKey(TIME_BONUS))->getValue();
            CCLog("time %d",score);
        }else if(i == TROUBLE_BONUS){
            score = ((CCInteger*)m_scores->objectForKey(TROUBLE_BONUS))->getValue();
        }else if(i == PATH_BONUS){
            score = ((CCInteger*)m_scores->objectForKey(PATH_BONUS))->getValue();
        }

        
        int numLength = Calcurator::getIntegerLength(score);
        
        for(int j = 0; j < numLength; j++)
        {
            int keta = Calcurator::getIntegerDigit(score,j + 1);
            CCSprite* numSprite = getNumSprite(scoreTexture, scoreTextureRect, keta);
            numSprite->setPosition(ccp(winSize.width * 0.5 + 160 - NUM_WIDTH * j, winSize.height * 0.5 + 100 - NUM_HEIGHT * i));
            this->addChild(numSprite);
            
        }
        
    }   
    
    
    CCRect sumRect = CCRectMake(scoreTextureRect.size.width * 0.5 + 50, scoreTextureRect.size.height * 0.5 -50,SUM_WIDTH,SUM_HEIGHT);
    CCSprite* sumSprite = CCSprite::createWithTexture(scoreTexture,sumRect);
    sumSprite->setPosition(ccp(winSize.width * 0.5 + 150 , winSize.height * 0.5 - 40));
    this->addChild(sumSprite);
    
    CCRect underRect = CCRectMake(0, scoreTextureRect.size.height * 0.5 -2, scoreTextureRect.size.width, 4);
    CCSprite* underBarSprite = CCSprite::createWithTexture(scoreTexture,underRect);
    underBarSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5 -40 - 28));
    this->addChild(underBarSprite);
    
    
    
    int sumScore = ((CCInteger*)m_scores->objectForKey(SUM_SCORE))->getValue();
    int numLength = Calcurator::getIntegerLength(sumScore);
    
    for(int j = 0; j < numLength; j++)
    {
        
        int keta = Calcurator::getIntegerDigit(sumScore, j + 1);
        CCSprite* numSprite = getNumSprite(scoreTexture, scoreTextureRect, keta);
        numSprite->setPosition(ccp(winSize.width * 0.5 + 160 - NUM_WIDTH * j ,winSize.height * 0.5 - 40 - 28 - NUM_HEIGHT));
        this->addChild(numSprite);
    }
    
}

void ResultScene::makeButtons()
{
    CCTexture2D* buttonTexture = CCTextureCache::sharedTextureCache()->addImage("score_retry@2x.png");
    CCRect rect = CCRectZero;
    rect.size = buttonTexture->getContentSize();
    
    float buttonWidth = rect.size.width * 0.5;
    float buttonHeight = rect.size.height * 0.5;
    
    makeRetryButton(buttonTexture, buttonWidth, buttonHeight);
    makeTitleButton(buttonTexture,buttonWidth,buttonHeight);
    

}

void ResultScene::makeRetryButton(CCTexture2D* buttonTexture,float buttonWidth,float buttonHeight)
{    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCRect retryRect = CCRectMake(0,0, buttonWidth, buttonHeight);
    CCSprite* retryButton = CCSprite::createWithTexture(buttonTexture,retryRect);
    
    CCRect pressedRect = CCRectMake(buttonWidth,0,buttonWidth,buttonHeight);
    CCSprite* retryPressed = CCSprite::createWithTexture(buttonTexture,pressedRect);
    
    CCMenuItemSprite* retrySprite = CCMenuItemSprite::create(retryButton, retryPressed,this,menu_selector(ResultScene::clickedRetry));
    retrySprite->setPosition(ccp(winSize.width * 0.5,buttonHeight * 2 + buttonHeight * 0.75));
    
    CCMenu* retryMenu = CCMenu::create(retrySprite,NULL);
    retryMenu->setPosition(CCPointZero);
    this->addChild(retryMenu);

}

void ResultScene::makeTitleButton(CCTexture2D* buttonTexture,float buttonWidth,float buttonHeight)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCRect titleRect = CCRectMake(0,buttonHeight, buttonWidth, buttonHeight);
    CCSprite* titleButton = CCSprite::createWithTexture(buttonTexture, titleRect);
    
    CCRect pressedRect = CCRectMake(buttonWidth, buttonHeight, buttonWidth, buttonHeight);
    CCSprite* titlePressed = CCSprite::createWithTexture(buttonTexture, pressedRect);
    
    CCMenuItemSprite* titleSprite = CCMenuItemSprite::create(titleButton, titlePressed,this,menu_selector(ResultScene::clickedTitle));
    titleSprite->setPosition(winSize.width * 0.5 , buttonHeight + buttonHeight * 0.5);
    
    CCMenu* titleMenu = CCMenu::create(titleSprite,NULL);
    titleMenu->setPosition(CCPointZero);
    this->addChild(titleMenu);
}

void ResultScene::makeWin(){
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    int winState = userDefault->getIntegerForKey("winState",0);
    
    CCSprite* winSprite;
    
    switch(winState){
        case WIN : winSprite = CCSprite::create("win@2x.png"); break;
        case LOSE : winSprite = CCSprite::create("lose@2x.png"); break;
        case DRAW : winSprite = CCSprite::create("draw@2x.png"); break;
    }
    
    winSprite->setPosition(ccp(winSize.width * 0.5 , winSize.height - 180));
    this->addChild(winSprite);

}

CCSprite* ResultScene::getNumSprite(CCTexture2D* numTexture,CCRect textureRect,int num)
{
    CCRect numRect = CCRectMake(num * NUM_WIDTH,textureRect.size.height * 0.5 + 2,NUM_WIDTH,NUM_HEIGHT);
    CCSprite* numSprite = CCSprite::createWithTexture(numTexture,numRect);
    
    return numSprite;
}

void ResultScene::clickedRetry()
{
    CCScene* pScene = PlayScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void ResultScene::clickedTitle()
{
    CCScene* pScene = TitleScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    
}