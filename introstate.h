#ifndef INTROSTATE_H_
#define INTROSTATE_H_

#include "gamestate.h"
#include "square.h"
#include "utils.h"

class IntroState: public GameState{
    public:
        void init(Game*);
        void cleanup();

        void pause(Game*);
        void resume(Game*);

        void handle_events(Game* game, int key);
        void update(Game* game);
        void render(Game* game);
        static IntroState* instance();


    private:
        static bool instanceFlag;
        static IntroState* instanceObj;
        IntroState(){};
};
#endif
