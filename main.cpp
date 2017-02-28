#define _WIN32_WINNT 0x0500
#include "RenderEngine/RenderEngine.h"
#include <string>
#include <winbase.h>
#include <random>
#include <conio.h>
#include <algorithm>
#include <chrono>

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
    std::vector<char> frame = canv->getPixel(0,0,canv->area);
    Vector2 c_size = canv->getCanvasSize();
    int rowCount = 0;
    std::string testStr = std::string(c_size.x, '+');
    std::vector<char>::iterator rowBegin = frame.begin();
    for (int i=0; i<c_size.y; ++i){
        rowBegin += c_size.x;
        std::string compStr = std::string(rowBegin, rowBegin+c_size.x);
        if(!compStr.compare(testStr)){
            std::move(frame.begin(), rowBegin, frame.begin()+c_size.x);
            rowCount++;
        }
    }
    canv->setPixel({0,0}, frame, c_size, false);
    return rowCount;
}

bool hasLost(canvas* canv){
    unsigned width = canv->getCanvasSize().x;
    std::vector<char> firstRow = canv->getPixel(0,0,width);
    std::string test = std::string(width, ' ');
    std::string compStr = std::string(firstRow.begin(), firstRow.end());
    if(compStr.compare(test)){
        return true;
    }
    return false;
}

sprite* spawnRandomTetromino(canvas* canv, int randomVal){
    switch(randomVal){
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

    std::mt19937 randGen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0,6);

    sprite* tetromino = spawnRandomTetromino(tetris, dist(randGen));
    tetris->drawCanvas();

    while(loop){

        if(interrupt){
            interrupt = false;
            if (!tetromino->translate(0,1, true)){
                if(snagCount++ > 2){
                    tetris->setPixel(tetromino->getPosition(),tetromino->getSprite(),tetromino->getSize());
                    tetris->deleteSprite(tetromino);
                    removeCompleteRows(tetris);
                    if(hasLost(tetris)){
                        loop = false;
                    }
                    else {
                        tetromino = spawnRandomTetromino(tetris, dist(randGen));
                        snagCount = 0;
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
                    tetromino->translate(0, 1, true);
                    break;
                case KEY_LEFT:
                    tetromino->translate(-1, 0, true);
                    break;
                case KEY_RIGHT:
                    tetromino->translate(1, 0, true);
                    break;
                case 'z':
                    tetromino->rotate(1, true);
                    break;
                case 'x':
                    tetromino->rotate(-1, true);
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