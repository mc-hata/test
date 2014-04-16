
#include "Grid.h"

USING_NS_CC;

bool Grid::canDropGrid(int turn,int** gridState)
{
    for(int gridY = 0; gridY < GRID_HEIGHT; gridY++)
    {
        for(int gridX = 0; gridX < GRID_WIDTH; gridX++)
        {
            if(!isKoma(gridState,gridX, gridY))
            {
                if(canDropKoma(turn,gridState,gridX,gridY,-1,-1)){return true;}
                if(canDropKoma(turn,gridState,gridX,gridY,0,-1)){return true;}
                if(canDropKoma(turn,gridState,gridX,gridY,1,-1)){return true;}
                if(canDropKoma(turn,gridState,gridX,gridY,1,0)){return true;}
                if(canDropKoma(turn,gridState,gridX,gridY,1,1)){return true;}
                if(canDropKoma(turn,gridState,gridX,gridY,0,1)){return true;}
                if(canDropKoma(turn,gridState,gridX,gridY,-1,1)){return true;}
                if(canDropKoma(turn,gridState,gridX,gridY,-1,0)){return true;}
            }
        }
    }
    
    return false;
}

bool Grid::isKoma(int **gridState, int gridX, int gridY)
{
    if(gridState[gridX][gridY] == NONE)
    {
        return false;
    }
    
    return true;
}

bool Grid::canDropMass(CCLayer* layer,int turn, int **gridState,int gridX,int gridY)
{
    int canDrop = 0;
    
    if(canDropKoma(turn,gridState,gridX,gridY,-1,-1)){refreshKoma(layer,turn,gridState,gridX,gridY,-1,-1);canDrop++;}
    if(canDropKoma(turn,gridState,gridX,gridY,0,-1)){refreshKoma(layer,turn,gridState,gridX,gridY,0,-1);canDrop++;}
    if(canDropKoma(turn,gridState,gridX,gridY,1,-1)){refreshKoma(layer,turn,gridState,gridX,gridY,1,-1);canDrop++;}
    if(canDropKoma(turn,gridState,gridX,gridY,1,0)){refreshKoma(layer,turn,gridState,gridX,gridY,1,0);canDrop++;}
    if(canDropKoma(turn,gridState,gridX,gridY,1,1)){refreshKoma(layer,turn,gridState,gridX,gridY,1,1);canDrop++;}
    if(canDropKoma(turn,gridState,gridX,gridY,0,1)){refreshKoma(layer,turn,gridState,gridX,gridY,0,1);canDrop++;}
    if(canDropKoma(turn,gridState,gridX,gridY,-1,1)){refreshKoma(layer,turn,gridState,gridX,gridY,-1,1);canDrop++;}
    if(canDropKoma(turn,gridState,gridX,gridY,-1,0)){refreshKoma(layer,turn,gridState,gridX,gridY,-1,0);canDrop++;}
    
    if(canDrop > 0){
        return true;
    }else{
        return false;
    }
}

bool Grid::canDropKoma(int turn,int** gridState,int gridX, int gridY, int vecX, int vecY)
{
    int putKoma = turn;
    
    gridX += vecX;
    gridY += vecY;
    
    if(gridX <0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT)
    {
        return false;
    }
    
    int state = gridState[gridX][gridY];
    
    if(state == putKoma || state == NONE)
    {
        return false;
    }
    
    gridX += vecX;
    gridY += vecY;
    
    while(gridX >=0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT)
    {
        int state = gridState[gridX][gridY];
        if(state == putKoma)
        {
            return true;
        }else if(state == NONE){
            return false;
        }
        gridX += vecX;
        gridY += vecY;
    }
    return false;
}

void Grid::refreshKoma(CCLayer* layer,int turn,int** gridState,int gridX,int gridY,int vecX,int vecY)
{
    int putKoma = turn;
    int refreshKoma;
    
    if(putKoma == BLACK)
    {
        refreshKoma = WHITE;
    }else{
        refreshKoma = BLACK;
    }
    
    gridX += vecX;
    gridY += vecY;
    
    while(gridX >=0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT)
    {
        int state = gridState[gridX][gridY];
        
        if(state == refreshKoma){
            CCPoint komaPoint = Koma::getKomaPoint(gridX, gridY);
            Koma::dropKoma(layer,turn,komaPoint);
            gridState[gridX][gridY] = turn;
        }else if(state == putKoma){
            return;
        }
        
        gridX += vecX;
        gridY += vecY;
    }
}
