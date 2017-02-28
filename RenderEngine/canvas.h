//
// Created by Alex on 18-Feb-17.
//

#ifndef RENDERINGENGINE_CANVAS_H
#define RENDERINGENGINE_CANVAS_H
#include <iostream>
#include <vector>
#include "vector2.h"

class sprite;

class canvas
{
private:
    std::vector<char> canvas2D;
    Vector2 size;
    std::vector<sprite*> spriteVec;

public:
    unsigned area;
    // FUNCTIONALITY
    canvas(Vector2 size);
    sprite* createNewSprite(Vector2 size, Vector2 pos, const char* s);
    std::vector<char> generateFrame();
    void drawCanvas();
    bool checkValid(std::vector<char> s_c, Vector2 s_pos, Vector2 s_size);
    void deleteSprite(sprite* s);

    // GET
    Vector2 getCanvasSize();
    std::vector<char> getCanvasFrame();
    char getPixel(unsigned x, unsigned y);
    std::vector<char> getPixel(unsigned x, unsigned y, size_t n);

    // SET
    void setPixel(unsigned x, unsigned y, char c);
    void setPixel(Vector2 s_pos, std::vector<char> s_c, Vector2 s_size, bool ignoreSpaces=true);
};


#endif //RENDERINGENGINE_CANVAS_H
