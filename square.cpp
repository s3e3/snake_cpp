#include "square.h"

Square::Square(int x, int y, COLOR color){
    this->x = x;
    this->y = y;
    this->color = color;
}

Square::Square(int x, int y){
    this->x = x;
    this->y = y;
}

COLOR Square::getColor(){
    return this->color;
}

void Square::setColor(COLOR _color){
    this->color = _color;
}

void Square::draw(WINDOW* win){
    int org_x = this->x * 2;
    wattron(win, COLOR_PAIR(this->color));
    mvwaddch(win, this->y, org_x, ' ');
    mvwaddch(win, this->y, org_x + 1, ' ');
    wattroff(win, COLOR_PAIR(this->color));
}
