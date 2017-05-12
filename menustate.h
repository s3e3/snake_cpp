#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include<string>
#include "gamestate.h"
#include "square.h"
#include "utils.h"

#define MENU_SIZE 4

enum STATE {MAIN_MENU, SETTINGS, HIGHSCORE, CREDITS};

class MenuState: public GameState{
    public:
        void init(Game*);
        void cleanup();

        void pause(Game*);
        void resume(Game*);

        void handle_events(Game* game, int key);
        void update(Game* game);
        void render(Game* game);
        static MenuState* instance();


    private:

        MenuState();

        STATE current_state;
        std::string menu_title;
        std::string menu_options[MENU_SIZE];
        int selected_menu_option;
        static bool instanceFlag;
        static MenuState* instanceObj;

        void draw_menu(WINDOW*);
        void draw_highscore(WINDOW*);
        void draw_settings(WINDOW*);
        void draw_credits(WINDOW*);

        void handle_events_menu(Game* game, int key);
        void handle_events_highscore(Game*, int);
        void handle_events_settings(Game*, int);
        void handle_events_credits(Game*, int);
        void goto_main_menu();


};
#endif
