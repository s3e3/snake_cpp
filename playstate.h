#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include<string>
#include "gamestate.h"
#include "square.h"
#include "utils.h"
#include "map.h"
#include "food.h"
#include "snake.h"

class PlayState: public GameState{
    public:
        void init(Game*);
        void cleanup();

        void pause(Game*);
        void resume(Game*);

        void handle_events(Game* game, int key);
        void update(Game* game);
        void render(Game* game);
        static PlayState* instance();

    private:
        PlayState(){
        };

        static bool instanceFlag;
        static PlayState* instanceObj;
        void draw(Game*);
        void update_score(Game*);

        Food *food;
        SuperFood *superfood;
        Snake *snake;
        int** map;
        bool paused;
        bool game_over;
        COORD prev_food_pos;
};
#endif
