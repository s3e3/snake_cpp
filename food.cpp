#include <stdlib.h>
#include <time.h>
#include "food.h"
#include "logger.h"

void Food::set_random_pos(int** map){
    if(this->tile == FOOD_TILE)
        Log::instance()->info("placing new food", YELLOW_BLACK);
    else
        Log::instance()->info("placing new food", CYAN_BLACK);

    int _x = 0;
    int _y = 0;

    while(map[_x][_y] != BLANK_TILE){
        _x = rand()%WIDTH;
        _y = rand()%HEIGHT;
    }

    this->x = _x;
    this->y = _y;

    map[this->x][this->y] = this->tile;
}

void SuperFood::enable(){
    Log::instance()->info("enabling super food", CYAN_BLACK);
    this->enabled = true;
    this->time_counter = SUPER_FOOD_VISIBLE_LIMIT;
    this->start_time = Utils::getMilliCount();
}

void SuperFood::disable(int** map){
    Log::instance()->info("disabling super food", CYAN_BLACK);
    this->enabled = false;
    map[this->x][this->y] = BLANK_TILE;
}

void SuperFood::start_counter(){
    if(Utils::getMilliCount() - this->start_time >= 1000){
        this->time_counter--;
        this->start_time = Utils::getMilliCount();
        Log::instance()->info("time elapsed", std::to_string(this->time_counter));
    }
}

bool SuperFood::should_disable(){
    return this->time_counter <= 0;
}

void SuperFood::show_timer(Game* game){
    if(this->enabled){
        std::string sstr = "";
        for(int i=0;i<this->time_counter;i++) sstr += "=";
        for(int i=this->time_counter;i<SUPER_FOOD_VISIBLE_LIMIT;i++) sstr += " ";
        Utils::drawstr(game->window, 0, HEIGHT, sstr, RED_BLACK);
    }
    else{
        std::string sstr = "";
        for(int i=0;i<SUPER_FOOD_VISIBLE_LIMIT;i++) sstr += " ";
        Utils::drawstr(game->window, 0, HEIGHT, sstr, BLACK);
    }
}
