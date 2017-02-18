//
// Created by Alex on 18-Feb-17.
//

#include "sprite.h"
#include "RenderEngine.h"

sprite::sprite(Vector2 size, Vector2 pos, const char* initSprite)
        : size(size), pos(pos), hidden(false), area(size.x*size.y)
{
    sprite2D = new char[area+1];
    memset(sprite2D, ' ', area);
    strcpy(sprite2D, initSprite);
}

char sprite::getPixel(unsigned x, unsigned y){
    return sprite2D[x+y*size.x];
}

char* sprite::spriteData(){
    return sprite2D;
}

Vector2 sprite::spriteDim(){
    return size;
}

void sprite::spriteData(char* newSprite){
    strcpy(sprite2D, newSprite);
}

Vector2 sprite::getPosition(){
    return pos;
}

void sprite::setPosition(unsigned x, unsigned y){
    if (x >= size.x)
        x = size.x;

    if (y >= size.y)
        y = size.y;

    pos = {x,y};
};

bool sprite::translate(int x, int y){
    Vector2 newPos = {x + pos.x, y + pos.y};

    // check if position is outside canvas
    if(newPos.y < parent->size.y && newPos.x < parent->size.x && parent->checkValid(this->sprite2D, newPos, this->size)) {
        pos = newPos;
        return true;
    }
    else
        return false;
}

void sprite::rotateCW(){
    char* tempSprite = new char[area+1];
    Vector2 newSize = {size.y, size.x};
    memset(tempSprite, ' ', area);
    for(int y=0; y<size.y; ++y){
        for(int x=0; x<size.x; ++x){
            tempSprite[(newSize.x-y-1)+x*(newSize.x)] = sprite2D[x+y*size.x];
        }
    }

    //Vector2 newPos = {size.x-1-pos.y, pos.x};
    if (parent->checkValid(tempSprite,this->pos,newSize)){
        strcpy(sprite2D, tempSprite);
        //this->pos = newPos;
        this->size = newSize;
    }
    delete[] tempSprite;
}

void sprite::rotateCCW(){
    char* tempSprite = new char[area+1];
    Vector2 newSize = {size.y, size.x};
    memset(tempSprite, ' ', area);
    for(int y=0; y<size.y; ++y){
        for(int x=0; x<size.x; ++x){
            tempSprite[y+(size.x-x-1)*newSize.x] = sprite2D[x+y*size.x];
        }
    }

    //Vector2 newPos = {pos.y, size.x-1-pos.x};
    if (parent->checkValid(tempSprite,this->pos,newSize)){
        strcpy(sprite2D, tempSprite);
        //this->pos = newPos;
        this->size = newSize;
    }
    delete[] tempSprite;
}
