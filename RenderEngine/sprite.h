//
// Created by Alex on 18-Feb-17.
//

#ifndef RENDERINGENGINE_SPRITE_H
#define RENDERINGENGINE_SPRITE_H

class sprite
{
    friend class canvas;
private:
    char* sprite2D;
    Vector2 size, pos;
    unsigned area, pos_z;
    canvas* parent;
protected:
    // constructor
    sprite(Vector2 size, Vector2 pos, const char* initSprite);

public:
    bool hidden;

    // 'pixel' level calls - actually a char but lets not get technical
    char getPixel(unsigned x, unsigned y);
    void setPixel(unsigned x, unsigned y, char c);

    // data about the sprite
    Vector2 spriteDim();
    char* spriteData();
    void spriteData(char* newSprite);

    // transform the sprite
    Vector2 getPosition();
    void setPosition(unsigned x, unsigned y);
    bool translate(int x, int y);
    void rotateCW();
    void rotateCCW();
};

#endif //RENDERINGENGINE_SPRITE_H
