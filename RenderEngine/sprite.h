//
// Created by Alex on 18-Feb-17.
//

#ifndef RENDERINGENGINE_SPRITE_H
#define RENDERINGENGINE_SPRITE_H
#include <iostream>
#include <vector>
#include "vector2.h"
#include "canvas.h"

class sprite
{
    friend class canvas;
private:
    std::vector<char> sprite2D;
    Vector2 size, pos;
    unsigned area, pos_z;
    canvas* parent;
    // constructor
    sprite(Vector2 size, Vector2 pos, const char* initSprite);
public:
    bool hidden;

    // 'pixel' level calls - actually a char but lets not get technical
    char getPixel(unsigned x, unsigned y);
    void setPixel(unsigned x, unsigned y, char c);

    // data about the sprite
    Vector2 getSize();
    std::vector<char> getSprite();
    void setSprite(const char* newSprite);

    // transform the sprite
    Vector2 getPosition();
    void setPosition(int x, int y);
    bool translate(int x, int y, bool safe);
    bool rotate(int dir, bool safe);
};

#endif //RENDERINGENGINE_SPRITE_H
