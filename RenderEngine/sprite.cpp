#include "sprite.h"

// CONSTRUCTOR
sprite::sprite(Vector2 size, Vector2 pos, const char* initSprite)
        : size(size),
          pos(pos),
          hidden(false),
          area(size.x*size.y),
          sprite2D(initSprite, initSprite+(size.x*size.y))
{}

// GET
char sprite::getPixel(unsigned x, unsigned y){
    return sprite2D[x+y*size.x];
}

std::vector<char> sprite::getSprite(){
    return sprite2D;
}

Vector2 sprite::getSize(){
    return size;
}

Vector2 sprite::getPosition(){
    return pos;
}

// SET
void sprite::setPosition(int x, int y){
    pos = {x,y};
}

void sprite::setSprite(const char* newSprite){
    sprite2D = std::vector<char>(newSprite, newSprite+this->area);
}

// TRANSFORMATIONS
bool sprite::translate(int x, int y, bool safe){
    Vector2 newPos = {x + pos.x, y + pos.y};

    if (safe){
    // check if position is outside canvas
    if(newPos.y < parent->getCanvasSize().y && newPos.x < parent->getCanvasSize().x
       && parent->checkValid(this->sprite2D, newPos, this->size)) {
        pos = newPos;
        return true;
    }
    else
        return false;
    }
    else{
        pos = newPos;
        return true;
    }
}

bool sprite::rotate(int dir, bool safe){
    std::vector<char> tempSprite(area, ' ');
    Vector2 newSize = {size.y, size.x};

    //rotate clockwise
    if(dir>0) {
        for (int y = 0; y < size.y; ++y) {
            for (int x = 0; x < size.x; ++x) {
                tempSprite[(newSize.x - y - 1) + x * (newSize.x)] = sprite2D[x + y * size.x];
            }
        }
    }
    else{   //rotate counter-clockwise
        for (int y = 0; y < size.y; ++y) {
            for (int x = 0; x < size.x; ++x) {
                tempSprite[y+(size.x-x-1)*newSize.x] = sprite2D[x+y*size.x];
            }
        }
    }

    if (safe) {
        if (parent->checkValid(tempSprite, this->pos, newSize)) {
            std::swap(tempSprite, sprite2D);
            this->size = newSize;
            return true;
        }
        else
            return false;
    }
    return true;
}