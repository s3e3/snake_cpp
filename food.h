#ifndef FOOD_H_
#define FOOD_H_

#include "utils.h"
#include "game.h"
#include "square.h"

class Food: public Square{
    public:
        Food(int x, int y): Square(x, y){
            this->tile = FOOD_TILE;
        };
        Food(int x, int y, int tile): Square(x, y){
            this->tile = tile;
        }
        Food(int tile){
            this->tile = tile;
        }
        Food(){
            this->tile = FOOD_TILE;
        };

        void set_random_pos(int** map);

        int tile;
};

class SuperFood: public Food{
    public:
        SuperFood(int x, int y): Food(x, y, SUPER_FOOD_TILE){
            this->enabled = false;
        };
        SuperFood(): Food(SUPER_FOOD_TILE){
            this->enabled = false;
        };

        bool enabled;
        int time_counter;

        void start_counter();
        void enable();
        bool should_disable();
        void disable(int** map);
        void show_timer(Game*);

    private:
        int start_time;
};
#endif
