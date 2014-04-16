

#include "Koma.h"

USING_NS_CC;

CCPoint Koma::getKomaPoint(int gridX,int gridY)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    int beginX = winSize.width * 0.5 - KOMA_WIDTH * Grid::GRID_WIDTH * 0.5;
    int beginY = winSize.height * 0.5 + KOMA_HEIGHT * Grid::GRID_HEIGHT * 0.5;
    
    int x = beginX + gridX * KOMA_WIDTH + KOMA_WIDTH * 0.5;
    int y = beginY - gridY * KOMA_HEIGHT - KOMA_HEIGHT * 0.5;
    
    CCPoint komaPoint = ccp(x,y);
    
    return komaPoint;
}

void Koma::dropKoma(CCLayer* layer,int turn,CCPoint komaPoint)
{
    CCSprite* koma;

    if(turn == Grid::BLACK){
        koma = CCSprite::create("koma_black@2x.png");
    }else{
        koma = CCSprite::create("koma_white@2x.png");
    }
    
    koma->setPosition(komaPoint);
    layer->addChild(koma);
    
}

int Koma::getBlackNum(int **gridState)
{
    int num = 0;
    for(int gridY = 0; gridY < Grid::GRID_HEIGHT; gridY++)
    {
        for(int gridX = 0; gridX < Grid::GRID_WIDTH; gridX++)
        {
            if(gridState[gridX][gridY] == Grid::BLACK)
            {
                num++;
            }
        }
    }
    
    return num;
}

int Koma::getWhiteNum(int **gridState)
{
    int num = 0;
    for(int gridY = 0; gridY < Grid::GRID_HEIGHT; gridY++)
    {
        for(int gridX = 0; gridX < Grid::GRID_WIDTH; gridX++)
        {
            if(gridState[gridX][gridY] == Grid::WHITE)
            {
                num++;
            }
        }
    }
    
    return num;
}

int Koma::getAllNum(int **gridState)
{
    int num = 0;
    for(int gridY = 0; gridY < Grid::GRID_HEIGHT; gridY++)
    {
        for(int gridX = 0; gridX < Grid::GRID_WIDTH; gridX++)
        {
            if(gridState[gridX][gridY] == Grid::WHITE || gridState[gridX][gridY] == Grid::BLACK)
            {
                num++;
            }
        }
    }
    
    return num;
}



void Koma::refreshKomaNum(CCLayer* layer,int blackNum, int whiteNum)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* numSprite = (CCSprite*)layer->getChildByTag(NUM_TAG);
    while(numSprite != NULL)
    {
        layer->removeChildByTag(NUM_TAG);
        numSprite = (CCSprite*)layer->getChildByTag(NUM_TAG);
    }
    
    int komaNum,onesPlace,tensPlace,x;
    CCSprite *onesSprite,*tensSprite;
    
    //黒駒の個数
    komaNum = blackNum;
    onesPlace = komaNum / 1 % 10;
    tensPlace = komaNum / 10 % 10;
    x = 44;
    onesSprite = getNumSprite(onesPlace);
    onesSprite->setTag(NUM_TAG);
    tensSprite = getNumSprite(tensPlace);
    tensSprite->setTag(NUM_TAG);
    onesSprite->setPosition(ccp(x + 44,49));
    layer->addChild(onesSprite);
    tensSprite->setPosition(ccp(x,49));
    layer->addChild(tensSprite);
    
    
    //白駒の個数
    komaNum = whiteNum;
    onesPlace = komaNum / 1 % 10;
    tensPlace = komaNum / 10 % 10;
    x = winSize.width - 44 * 2;
    onesSprite = getNumSprite(onesPlace);
    onesSprite->setTag(NUM_TAG);
    tensSprite = getNumSprite(tensPlace);
    tensSprite->setTag(NUM_TAG);
    onesSprite->setPosition(ccp(x + 44,49));
    layer->addChild(onesSprite);
    tensSprite->setPosition(ccp(x,49));
    layer->addChild(tensSprite);
}

CCSprite* Koma::getNumSprite(int num)
{
    CCTexture2D* numTexture = CCTextureCache::sharedTextureCache()->addImage("game_number@2x.png");
    CCRect textureRect = CCRectZero;
    textureRect.size = numTexture->getContentSize();
    
    float width = 48;
    
    CCRect numRect = CCRectMake(width * num , 0 , width , 52);
    CCSprite* numSprite = CCSprite::createWithTexture(numTexture,numRect);
    numSprite->setTag(NUM_TAG);
    
    return numSprite;
}

CCRect Koma::getKomaRect(int gridX, int gridY)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();
    
    int beginX = winSize.width * 0.5 - KOMA_WIDTH * Grid::GRID_WIDTH * 0.5;
    int beginY = winSize.height * 0.5 + KOMA_HEIGHT * Grid::GRID_HEIGHT * 0.5 -KOMA_HEIGHT;
    
    int x = beginX + gridX * KOMA_WIDTH;
    int y = beginY - gridY * KOMA_HEIGHT;
    
    CCRect komaRect = CCRectMake(x, y , KOMA_WIDTH, KOMA_HEIGHT);
    
    return komaRect;
}












