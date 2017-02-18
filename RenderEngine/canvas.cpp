#include "canvas.h"
#include "RenderEngine.h"

canvas::canvas(Vector2 size)
        : size(size), area(size.x*size.y)
{
    canvas2D = new char[area+1];
    memset(canvas2D, ' ', area);
}

void canvas::clearScreen(){
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };
    CONSOLE_CURSOR_INFO         cursorInfo;

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR) ' ',
            cellCount,
            homeCoords,
            &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );

    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
}

char canvas::getPixel(unsigned x, unsigned y){
    return canvas2D[x+y*size.x];
}

char* canvas::getPixel(unsigned x, unsigned y, size_t n){
    char* frame = new char[n+1];
    memcpy(frame, &canvas2D[x+y*size.x], n);
    frame[n] = '\0';
    return frame;
}

void canvas::setPixel(unsigned x, unsigned y, char c){
    canvas2D[x+y*size.x] = c;
}

void canvas::setPixel(Vector2 s_pos, char* s_c, Vector2 s_size, bool ignoreSpaces){
    for(unsigned y=0; y < s_size.y; ++y){
        for(unsigned x=0; x < s_size.x; ++x){
            char c = s_c[x+y*s_size.x];
            Vector2 globalPos = {x+s_pos.x, y+s_pos.y};
            if (!ignoreSpaces || c != ' '){
                if (globalPos.x < size.x && globalPos.y < size.y){
                    this->setPixel(globalPos.x, globalPos.y, c);
                }
            }
        }
    }
}

char* canvas::generateFrame(){
    char* frame = new char[area+1];
    strcpy(frame, canvas2D);
    for (sprite *s: spriteVec) {
        if (!s->hidden) {
            Vector2 start = s->getPosition();
            Vector2 dim = s->spriteDim();
            for (int y = 0; y < dim.y; ++y) {
                for (int x = 0; x < dim.x; ++x) {
                    if (s->getPixel(x, y) != ' ') {
                        frame[(start.x + x) + size.x * (start.y + y)] = s->getPixel(x, y);
                    }
                }
            }
        }
    }
    return frame;
}

void canvas::drawCanvas(){
    clearScreen();
    char* frame = generateFrame();
    for(int x=0; x<size.x+2; ++x){
        std::cout << "- ";
    }
    std::cout << "\n";
    for(int y=0; y<size.y; ++y){
        std::cout << "| ";
        for(int x=0; x<size.x; ++x){
            std::cout << frame[x+y*size.x] << " ";
        }
        std::cout << "|\n";
    }
    for(int x=0; x<size.x+2; ++x){
        std::cout << "- ";
    }
    delete[] frame;
}

canvas::sprite* canvas::createNewSprite(Vector2 size, Vector2 pos, const char* s){
    sprite* newSprite = new sprite(size,pos,s);
    spriteVec.push_back(newSprite);
    newSprite->parent = this;
    return newSprite;
}

void canvas::deleteSprite(sprite* s){
    auto it = std::find(spriteVec.begin(), spriteVec.end(), s);
    spriteVec.erase(it);
    delete s;
}

bool canvas::checkValid(char* s_c, Vector2 s_pos, Vector2 s_size){
    for(unsigned y=0; y < s_size.y; ++y){
        for(unsigned x=0; x < s_size.x; ++x){
            char c = s_c[x+y*s_size.x];
            if (c != ' '){
                if (x+s_pos.x > size.x-1 || y+s_pos.y > size.y-1){
                    return false;
                }
                if (this->getPixel(x+s_pos.x,y+s_pos.y) != ' ' ){
                    return false;
                }
            }
        }
    }
    return true;
}

Vector2 canvas::getCanvasSize(){
    return this->size;
}

char* canvas::getCanvasFrame(){
    return this->canvas2D;
}