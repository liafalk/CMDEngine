#define _WIN32_WINNT 0x0500
#include "RenderEngine.h"
#include <stdio.h>
#include <winbase.h>
#include <random>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27

const char spr_L1[] =   "+++  +";
const char spr_L2[] =   "++++  ";
const char spr_Z1[] =   " ++++ ";
const char spr_Z2[] =   "++  ++";
const char spr_T[] =    "+++ + ";
const char spr_Sq[] =   "++++";
const char spr_I[] =    "++++";

bool interrupt = false;

VOID CALLBACK handleInterrupt(){
    interrupt = true;
}

int removeCompleteRows(canvas* canv){
    char* frame = canv->getPixel(0,0,canv->area);
    Vector2 c_size = canv->getCanvasSize();
    int rowCount = 0;

    for (int i=0; i<c_size.y; ++i){
        if(memchr(&frame[i*c_size.x], ' ', c_size.x) == NULL){
            memmove(frame+c_size.x, frame, i*c_size.x);
            rowCount++;
        }
    }
    canv->setPixel({0,0}, frame, c_size, false);
    delete[] frame;
    return rowCount;
}

bool hasLost(canvas* canv){
    unsigned width = canv->getCanvasSize().x;
    char* firstRow = canv->getPixel(0,0,width);
    std::string test = std::string(width, ' ');
    if(test.compare(firstRow)){
        return true;
    }
    delete[] firstRow;
    return false;
}

canvas::sprite* spawnRandomTetromino(canvas* canv, std::default_random_engine& randGen, std::uniform_int_distribution<int>& dist){
    switch(dist(randGen)){
        case 0:
            return canv->createNewSprite({3,2},{0,0},spr_L1);
        case 1:
            return canv->createNewSprite({3,2},{0,0},spr_L2);
        case 2:
            return canv->createNewSprite({3,2},{0,0},spr_Z1);
        case 3:
            return canv->createNewSprite({3,2},{0,0},spr_Z2);
        case 4:
            return canv->createNewSprite({3,2},{0,0},spr_T);
        case 5:
            return canv->createNewSprite({2,2},{0,0},spr_Sq);
        case 6:
            return canv->createNewSprite({1,4},{0,0},spr_I);
    }
}

int main() {
    // create new canvas
    canvas* tetris = new canvas( (Vector2){10,20} );

    bool loop = true;
    unsigned snagCount = 0;
    HANDLE hTimer = NULL;
    CreateTimerQueueTimer(&hTimer, NULL, (WAITORTIMERCALLBACK)handleInterrupt,NULL,500,500,0 );

    std::default_random_engine randGen;
    std::uniform_int_distribution<int> dist(0,6);

    canvas::sprite* tetromino = spawnRandomTetromino(tetris, randGen, dist);
    tetris->drawCanvas();

    while(loop){

        if(interrupt){
            interrupt = false;
            if (!tetromino->translate(0,1)){
                if(snagCount++ > 2){
                    tetris->setPixel(tetromino->getPosition(),tetromino->spriteData(),tetromino->spriteDim());
                    tetris->deleteSprite(tetromino);
                    removeCompleteRows(tetris);
                    if(hasLost(tetris)){
                        loop = false;
                    }
                    else {
                        canvas::sprite *tetromino = spawnRandomTetromino(tetris, randGen, dist);
                        tetris->drawCanvas();
                    }
                }
            }
            else {
                tetris->drawCanvas();
            }
        }
        if (_kbhit()) {
            switch ((_getch())) {
                case KEY_DOWN:
                    tetromino->translate(0, 1);
                    break;
                case KEY_LEFT:
                    tetromino->translate(-1, 0);
                    break;
                case KEY_RIGHT:
                    tetromino->translate(1, 0);
                    break;
                case 'z':
                    tetromino->rotateCCW();
                    break;
                case 'x':
                    tetromino->rotateCW();
                    break;
                case ESC:
                    loop = false;
                    break;
                default:
                    break;
            }
            tetris->drawCanvas();
        }
    }

    return 0;
}