#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "game.h"
#include "menustate.h"
#include "logger.h"
using namespace std;


const int TICKS_PER_SECOND = 8;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 10;

int main(){
    Game game;
    game.init();
    Log::instance()->enable();
    Log::instance()->info("game initialized..");

    game.change_state(MenuState::instance());

    int ch;
    int next_game_tick = Utils::getMilliCount();
    int loops;

    while( game.is_running ){
        ch = wgetch(game.window);
        game.handle_events(ch);

        loops = 0;
        while( Utils::getMilliCount() > next_game_tick && loops < MAX_FRAMESKIP) {
            game.update();
            next_game_tick += (1000/game.speed);
            loops++;
        }
        game.render();
    }
    game.cleanup();
    Log::instance()->disable();
    sleep(2);

    endwin();
}
