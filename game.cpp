#include <stdlib.h>
#include "game.h"
#include "gamestate.h"
#include "logger.h"
#include "playstate.h"

Game::Game(){
}

void Game::init(){

    srand(time(NULL));
    initscr();
    window = newwin(HEIGHT+1, 2*WIDTH, 0, 0);
    is_running = true;
    noecho();
    cbreak();
    nodelay(window,true);
    keypad(window, true);
    curs_set(false);
    start_color();

    Utils::init();

    this->speed = SNAKE_START_SPEED;
    this->snake_color = YELLOW;
    this->map = MAP_1;
}

void Game::cleanup(){
    if(!states.empty()){
        states.back()->cleanup();
        states.pop_back();
    }
    if(states.size() > 0){
        Log::instance()->error("states not empty..");
    }
    Log::instance()->info("Cleaning", "game class", GREEN_BLACK);
    wclear(window);
    delwin(window);
    Log::instance()->info("shuting down...");
}

void Game::change_state(GameState* state){
    if(!states.empty()){
        states.back()->cleanup();
        states.pop_back();
    }
    states.push_back(state);
    states.back()->init(this);
}

void Game::enter_playstate(){
    change_state(PlayState::instance());
}

void Game::push_state(GameState* state){
    if(!states.empty()){
        states.back()->pause(this);
    }
    states.push_back(state);
    states.back()->init(this);
}

void Game::pop_state(){
    if(!states.empty()){
        states.back()->cleanup();
        states.pop_back();
    }
    if(!states.empty()){
        states.back()->resume(this);
    }
}

void Game::handle_events(int key){
    if(key != ERR){
        states.back()->handle_events(this, key);
    }
}

void Game::update(){
    states.back()->update(this);
}

void Game::render(){
    if(!states.empty()){
        states.back()->render(this);
    }
    wrefresh(window);
}

void Game::increase_gamespeed(){
    if(this->speed < SNAKE_MAX_SPEED) this->speed++;
}

void Game::decrease_gamespeed(){
    if(this->speed > SNAKE_MIN_SPEED) this->speed--;
}

void Game::quit(){
    this->is_running = false;
}

int** Game::get_map(){
    int** map = new int *[WIDTH];

    if(this->map == NO_WALLS){
        for(int i=0; i<WIDTH; i++){
            map[i] = new int[HEIGHT];
            for(int j=0; j<HEIGHT; j++){
                map[i][j] = 0;
            }
        }
    }
    if(this->map == MAP_1 || this->map == MAP_2){
        for(int i=0; i<WIDTH; i++){
            map[i] = new int[HEIGHT];
            for(int j=0; j<HEIGHT; j++){
                if(i==0 || i==WIDTH-1 || j==0 || j==HEIGHT-1)
                    map[i][j] = 1;
                else
                    map[i][j] = 0;
            }
        }
    }
    return map;
}
