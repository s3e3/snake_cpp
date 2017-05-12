#ifndef MAP_H_
#define MAP_H_

#include "utils.h"
#include "game.h"

class Map{
    public:
        Map();
        int map[WIDTH][HEIGHT];
        void draw(Game*);

};
#endif
