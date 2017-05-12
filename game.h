#ifndef GAME_H_
#define GAME_H_

#include<ncurses.h>
#include<vector>
#include "utils.h"

class GameState;

class Game{
    public:
        Game();
        void init();
        void cleanup();
        void quit();

        void change_state(GameState* state);
        void push_state(GameState* state);
        void pop_state();
        void enter_playstate();
        void enter_menustate();
        void increase_gamespeed();
        void decrease_gamespeed();
        int** get_map();

        void handle_events(int);
        void update();
        void render();

        WINDOW* window;
        bool is_running;
        int score;


        COLOR snake_color;
        int speed;
        MAP map;

    private:
        std::vector<GameState*> states;
};
#endif
