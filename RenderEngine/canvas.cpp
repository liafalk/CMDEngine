#include "canvas.h"
#include "sprite.h"
#include "RenderEngine.h"
#include <algorithm>

canvas::canvas(Vector2 size)
        : size(size),
          area(size.x*size.y),
          canvas2D(size.x*size.y, ' ')
{}

char canvas::getPixel(unsigned x, unsigned y){
    return canvas2D[x+y*size.x];
}

std::vector<char> canvas::getPixel(unsigned x, unsigned y, size_t n){
    std::vector<char>::iterator b = canvas2D.begin() + (x+y*size.x);
    std::vector<char> frame(b, b+n);
    return frame;
}

void canvas::setPixel(unsigned x, unsigned y, char c){
    canvas2D[x+y*size.x] = c;
}

void canvas::setPixel(Vector2 s_pos, std::vector<char> s_c, Vector2 s_size, bool ignoreSpaces){
    for(int y=0; y < s_size.y; ++y){
        for(int x=0; x < s_size.x; ++x){
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

std::vector<char> canvas::generateFrame(){
    std::vector<char> frame(canvas2D);

    // draw sprites
    for (sprite *s: spriteVec) {
        if (s->hidden)
            continue;
        Vector2 start = s->getPosition();

        for (int y = 0; y < s->getSize().y; ++y) {
            for (int x = 0; x < s->getSize().x; ++x) {
                if (s->getPixel(x, y) != ' '
                    && start.x + x < size.x && start.x + x >= 0
                    && start.y + y < size.y && start.y + y >= 0) {
                    frame[(start.x + x) + size.x * (start.y + y)] = s->getPixel(x, y);
                }
            }
        }

    }

    return frame;
}

void canvas::drawCanvas(){
    RenderEngine::clearScreen();
    std::vector<char> frame = generateFrame();
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
}

sprite* canvas::createNewSprite(Vector2 size, Vector2 pos, const char* s){
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

bool canvas::checkValid(std::vector<char> s_c, Vector2 s_pos, Vector2 s_size){
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

std::vector<char> canvas::getCanvasFrame(){
    return this->canvas2D;
}