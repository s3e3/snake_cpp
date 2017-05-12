#ifndef SQUARE_H_
#define SQUARE_H_

#include<ncurses.h>
#include "utils.h"

class Square{
    private:
        COLOR color;

    public:
        Square(int x, int y, COLOR color);
        Square(int x, int y);
        Square(){};
        
        int x;
        int y;

        COLOR getColor();
        void setColor(COLOR _color);

        void draw(WINDOW*);
};
#endif
