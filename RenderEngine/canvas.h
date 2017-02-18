//
// Created by Alex on 18-Feb-17.
//

#ifndef RENDERINGENGINE_CANVAS_H
#define RENDERINGENGINE_CANVAS_H

class canvas
{
public:
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


#endif //RENDERINGENGINE_CANVAS_H
