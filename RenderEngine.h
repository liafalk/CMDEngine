//
// Created by Polar on 16-Feb-17.
//

#ifndef RENDERINGENGINE_RENDERENGINE_H
#define RENDERINGENGINE_RENDERENGINE_H

#include <iostream>
#include <vector>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <algorithm>

typedef struct Vector2{
    unsigned x;
    unsigned y;
}Vector2;

class canvas
{
public:
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
    Vector2 getCanvasSize();
    char* getCanvasFrame();
    void clearScreen();
    canvas(Vector2 size);
    char getPixel(unsigned x, unsigned y);
    char* getPixel(unsigned x, unsigned y, size_t n);
    void setPixel(unsigned x, unsigned y, char c);
    void setPixel(Vector2 s_pos, char* s_c, Vector2 s_size, bool ignoreSpaces=true);
    char* generateFrame();
    void drawCanvas();
    canvas::sprite* createNewSprite(Vector2 size, Vector2 pos, const char* s);
    void deleteSprite(sprite* s);
    bool checkValid(char* s_c, Vector2 s_pos, Vector2 s_size);
    unsigned area;
private:

    char* canvas2D;
    Vector2 size;
    std::vector<sprite*> spriteVec;
};

#endif //RENDERINGENGINE_RENDERENGINE_H
