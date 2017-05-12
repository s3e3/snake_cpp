#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "game.h"

class GameState{
    public:
        virtual void init(Game*) = 0;
        virtual void cleanup() = 0;

        virtual void pause(Game*) = 0;
        virtual void resume(Game*) = 0;

        virtual void handle_events(Game* game,int key) = 0;
        virtual void update(Game* game) = 0;
        virtual void render(Game* game) = 0;

        void change_state(Game* game, GameState* state){
            game->change_state(state);
        }

};

#endif
