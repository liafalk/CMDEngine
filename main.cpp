#define _WIN32_WINNT 0x0500
#include "RenderEngine.h"
#include <stdio.h>
#include <winbase.h>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27

bool interrupt = false;

void initCharArr(unsigned area, char *s){
}

VOID CALLBACK handleInterrupt(){
    interrupt = true;
}

int main() {
    // create new canvas
    canvas* tetris = new canvas( (Vector2){10,20} );
    tetris->setPixel(2,17,'x');
    tetris->setPixel(2,18,'x');
    tetris->setPixel(2,19,'x');
    tetris->setPixel(3,19,'x');
    //sprite T(3,3,1,0," + +++   ");
    //sprite L(3,3,1,0,"+  +++   ");
    //sprite Z(3,3,1,0,"++  ++   ");
    //sprite S(3,3,1,0,"++ ++    ");
    /*
    canvas::sprite* I = tetris->createNewSprite({4,4},{1,0},"+   +   +   +   ");
    tetris->drawCanvas();
    Sleep(500);

    I->hidden = false;
    tetris->drawCanvas();
    Sleep(500);
*/
    canvas::sprite* S = tetris->createNewSprite({2,3},{0,0},"+ + ++");
    tetris->drawCanvas();
    bool loop = true;
    unsigned snagCount = 0;
    HANDLE hTimer = NULL;
    //CreateTimerQueueTimer(&hTimer, NULL, (WAITORTIMERCALLBACK)handleInterrupt,NULL,500,500,0 );

    while(loop){

        if(interrupt){
            interrupt = false;
            if (!S->translate(0,1)){
                if(snagCount++ > 2){
                    tetris->setPixel(S->getPosition(),S->spriteData(),S->spriteDim());
                    tetris->deleteSprite(S);
                    canvas::sprite* S = tetris->createNewSprite({2,3},{0,0},"+ + ++");
                }
            }
            else {
                tetris->drawCanvas();
            }
        }
        if (_kbhit()) {
            switch ((_getch())) {
                case KEY_DOWN:
                    S->translate(0, 1);
                    break;
                case KEY_LEFT:
                    S->translate(-1, 0);
                    break;
                case KEY_RIGHT:
                    S->translate(1, 0);
                    break;
                case 'z':
                    S->rotateCCW();
                    break;
                case 'x':
                    S->rotateCW();
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