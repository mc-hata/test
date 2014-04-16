

#include "PlayCpuScene.h"
#include "ResultScene.h"
#include "Vibrate.h"

USING_NS_CC;

CCScene* PlayCpuScene::scene()
{
    CCScene* scene = CCScene::create();
    PlayCpuScene* layer = PlayCpuScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool PlayCpuScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    m_blackNode = CCSpriteBatchNode::create("koma_black@2x.png", 0);
    this->addChild(m_blackNode);
    m_whiteNode = CCSpriteBatchNode::create("koma_white@2x.png", 0);
    this->addChild(m_whiteNode);
    
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    m_isVibration = userDefault->getBoolForKey("VIBRATION",true);
    
    initSound();
    drawBackGround();
    initGrid();
    
    Koma::refreshKomaNum(this, Koma::getBlackNum(m_gridState), Koma::getWhiteNum(m_gridState));
    
    m_timeManager = (TimeManager*)TimeManager::time();
    this->addChild(m_timeManager);
    
    this->schedule(schedule_selector(PlayCpuScene::turn), 1.0);
    
    return true;
}

void PlayCpuScene::initSound()
{
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    
    float seVolume = userDefault->getFloatForKey("SE_VOLUME", 1.0);
    float bgmVolume = userDefault->getFloatForKey("BGM_VOLUME",1.0);
    
    Sound::setSEVolume(seVolume);
    Sound::setMusicVolume(bgmVolume);
    
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    
    CCString* dropSound;
    if(platform == kTargetIphone || platform == kTargetIpad){
        dropSound = CCString::create("SE_001B.caf");
    }else if(platform == kTargetAndroid){
        dropSound = CCString::create("se_001.ogg");
    }
        
    Sound::preloadSE(dropSound);
    
    CCString* bgm = CCString::create("BGM_002B.mp4");
    Sound::preloadMusic(bgm);
    Sound::playMusic(bgm, true);
}

void PlayCpuScene::drawBackGround()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* bg = CCSprite::create("game_bg@2x.png");
    bg->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.5));
    this->addChild(bg);
}

void PlayCpuScene::initGrid()
{
    m_gridState = new int*[Grid::GRID_WIDTH];
    
    for(int i = 0; i < Grid::GRID_HEIGHT; i++){
        m_gridState[i] = new int[Grid::GRID_HEIGHT];
    }
    for(int gridY = 0; gridY < Grid::GRID_HEIGHT; gridY++){
        for(int gridX = 0; gridX < Grid::GRID_WIDTH; gridX++){
            m_gridState[gridY][gridX] = Grid::NONE;
        }
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //左下黒[3,4]
    CCSprite* blackKoma1 = CCSprite::createWithTexture(m_blackNode->getTexture());
    blackKoma1->setPosition(ccp(winSize.width * 0.5 - Koma::KOMA_WIDTH * 0.5 ,winSize.height * 0.5 - Koma::KOMA_HEIGHT * 0.5 ));
    this->addChild(blackKoma1);
    m_gridState[3][4] = Grid::BLACK;
    //m_komaNum++;
    
    //右上黒[3,4]
    CCSprite* blackKoma2 = CCSprite::createWithTexture(m_blackNode->getTexture());
    blackKoma2->setPosition(ccp(winSize.width * 0.5 + Koma::KOMA_WIDTH * 0.5 ,winSize.height * 0.5 + Koma::KOMA_HEIGHT * 0.5 ));
    this->addChild(blackKoma2);
    m_gridState[4][3] = Grid::BLACK;
    
    //右下白[4,4]
    CCSprite* whiteKoma1 = CCSprite::createWithTexture(m_whiteNode->getTexture());
    whiteKoma1->setPosition(ccp(winSize.width * 0.5 + Koma::KOMA_WIDTH * 0.5,winSize.height * 0.5 - Koma::KOMA_HEIGHT * 0.5 ));
    this->addChild(whiteKoma1);
    m_gridState[4][4] = Grid::WHITE;
    
    //左上白[3,3]
    CCSprite* whiteKoma2 = CCSprite::createWithTexture(m_whiteNode->getTexture());
    whiteKoma2->setPosition(ccp(winSize.width * 0.5 - Koma::KOMA_WIDTH * 0.5, winSize.height * 0.5 + Koma::KOMA_HEIGHT * 0.5));
    this->addChild(whiteKoma2);
    m_gridState[3][3] = Grid::WHITE;
}

void PlayCpuScene::turn()
{
    this->unschedule(schedule_selector(PlayCpuScene::turn));
    
    if(isGameEnd())
    {
        gameEnd();
        return;
    }
    
    //置ける場所があるか調べる　ないなら相手のターン。
    if(!Grid::canDropGrid(getTurn(), m_gridState))
    {
        CCLog("not mass");
        m_passCount++;
        m_turn++;
        this->schedule(schedule_selector(PlayCpuScene::turn), 1.0);
        return;
    }
    
    m_passCount = 0;
    
    for(int gridY = 0; gridY < Grid::GRID_HEIGHT; gridY++)
    {
        for(int gridX = 0;gridX < Grid::GRID_WIDTH; gridX++)
        {
            if(!Grid::isKoma(m_gridState,gridX,gridY))
            {
                if(Grid::canDropMass(this, getTurn(), m_gridState, gridX, gridY))
                {
                    CCPoint komaPoint = Koma::getKomaPoint(gridX,gridY);
                    Koma::dropKoma(this, getTurn(), komaPoint);
                    m_gridState[gridX][gridY] = getTurn();
                    m_turn++;
                    
                    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
                    if(platform == kTargetIphone || platform == kTargetIpad){
                        Sound::playSE(CCString::create("SE_001B.caf"));

                    }else if(platform == kTargetAndroid){
                        Sound::playSE(CCString::create("se_001.ogg"));
                    }
                    
                    if(m_isVibration){
                        Vibrate::vibrate();
                    }
                    
                    int blackNum = Koma::getBlackNum(m_gridState);
                    int whiteNum = Koma::getWhiteNum(m_gridState);
                    Koma::refreshKomaNum(this, blackNum, whiteNum);
                    
                    this->schedule(schedule_selector(PlayCpuScene::turn), 1.0);
                    return;
                }
            }
        }
    }

    
}

bool PlayCpuScene::isGameEnd()
{
    int komaNum = Koma::getAllNum(m_gridState);
    
    if(komaNum >= Grid::GRID_NUM)
    {
        return true;
    }
    
    if(m_passCount >= 2)
    {
        return true;
    }
    
    return false;
}

void PlayCpuScene::gameEnd()
{
    m_timeManager->stopTimer();
    Sound::stopMusic();
    
    int time = m_timeManager->getTime();
    
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    userDefault->setIntegerForKey("time", time);
    
    int blackNum = Koma::getBlackNum(m_gridState);
    int whiteNum = Koma::getWhiteNum(m_gridState);
    
    int winState;
    
    if(blackNum > whiteNum)
    {
        winState = WIN;
    }else if(blackNum == whiteNum){
        winState = DRAW;
    }else{
        winState = LOSE;
    }
   
    userDefault->setIntegerForKey("winState", winState);
    
    CCScene* pScene = ResultScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

int PlayCpuScene::getTurn()
{
    if(m_turn % 2 == 0)
    {
        return Grid::BLACK;
    }else{
        return Grid::WHITE;
    }
    
    return NULL;
}

