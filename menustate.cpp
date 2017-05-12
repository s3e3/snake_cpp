#include<string>
#include "menustate.h"
#include "settingstate.h"
#include "utils.h"
#include "logger.h"

bool MenuState::instanceFlag = false;
MenuState* MenuState::instanceObj = NULL;

MenuState::MenuState(){
    menu_title      = ">------ MENU ------<";
    menu_options[0] = "     Start Game     ";
    menu_options[1] = "      Settings      ";
    menu_options[2] = "     Highscores     ";
    menu_options[3] = "       Credit       ";

    selected_menu_option = 0;

}

void MenuState::init(Game* game){
    Log::instance()->info("initializing: menu state");
    draw_menu(game->window);
}
void MenuState::draw_menu(WINDOW* window){
    wclear(window);
    current_state = MAIN_MENU;
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT; j++){
            if(i==0 || i==WIDTH-1 || j==0 || j==HEIGHT-1){
                Square sqr(i,j, RED);
                sqr.draw(window);
            }
        }
    }

    Utils::drawstr(window, (2*WIDTH - menu_title.length())/2, 5, menu_title, RED_BLACK);
    for(int i=0;i<MENU_SIZE;i++){
        COLOR color = RED_BLACK;
        if(selected_menu_option == i)   color = BLACK_YELLOW;
        Utils::drawstr(window, (2*WIDTH - menu_options[i].length())/2, 6+i, menu_options[i], color);
    }

    std::string note = "* Press BACKSPACE to quit the game *";
    Utils::drawstr(window, (2*WIDTH - note.length())/2, 14, note.c_str(), WHITE_BLACK);
}

void MenuState::draw_settings(WINDOW* window){
    wclear(window);
    current_state = SETTINGS;
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT; j++){
            if(i==0 || i==WIDTH-1 || j==0 || j==HEIGHT-1){
                Square sqr(i,j, RED);
                sqr.draw(window);
            }
        }
    }
    std::string note = "* Not implemented yet *";
    Utils::drawstr(window, (2*WIDTH - note.length())/2, 5, note, WHITE_BLACK);
    
    note = "* Press BACKSPACE to return to the menu *";
    Utils::drawstr(window, (2*WIDTH - note.length())/2, 14, note, WHITE_BLACK);
}

void MenuState::draw_highscore(WINDOW* window){
    Log::instance()->info("drawing highscore...");
    wclear(window);
    current_state = HIGHSCORE;
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT; j++){
            if(i==0 || i==WIDTH-1 || j==0 || j==HEIGHT-1){
                Square sqr(i,j, RED);
                sqr.draw(window);
            }
        }
    }
    std::string note = "* Not implemented yet *";
    Utils::drawstr(window, (2*WIDTH - note.length())/2, 5, note, WHITE_BLACK);
    
    note = "* Press BACKSPACE to return to the menu *";
    Utils::drawstr(window, (2*WIDTH - note.length())/2, 14, note, WHITE_BLACK);
}

void MenuState::draw_credits(WINDOW* window){
    Log::instance()->info("drawing credits...");
    wclear(window);
    current_state = CREDITS;
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT; j++){
            if(i==0 || i==WIDTH-1 || j==0 || j==HEIGHT-1){
                Square sqr(i,j, RED);
                sqr.draw(window);
            }
        }
    }
    std::string note = "* SUHAS GHULE *";
    Utils::drawstr(window,  (2*WIDTH - note.length())/2, 5, note, WHITE_BLACK);

    note = "* Press BACKSPACE to return to the menu *";
    Utils::drawstr(window, (2*WIDTH - note.length())/2, 14, note, WHITE_BLACK);
}

MenuState* MenuState::instance(){
    if(instanceFlag)    return instanceObj;

    instanceFlag = true;
    instanceObj = new MenuState();
    return instanceObj;
}

void MenuState::cleanup(){
    Log::instance()->info("cleaning", "menu class", GREEN_BLACK);
}

void MenuState::pause(Game* game){
}

void MenuState::resume(Game* game){
    draw_menu(game->window);
}

void MenuState::handle_events_settings(Game* game, int key){
    if(key == 127 || key == 27){
        draw_menu(game->window);
    }
}
void MenuState::handle_events_highscore(Game* game, int key){
    if(key == 127 || key == 27){
        draw_menu(game->window);
    }
}
void MenuState::handle_events_credits(Game* game, int key){
    if(key == 127 || key == 27){
        draw_menu(game->window);
    }
}
void MenuState::handle_events_menu(Game* game, int key){
    if(key == 127 || key == 27){
        game->is_running = false;
        return;
    }
    if(key == 10){
        switch(selected_menu_option){
            case 0:
                game->enter_playstate();
                return;
            case 1:
                game->push_state(SettingState::instance());
                return;
            case 2:
                draw_highscore(game->window);
                return;
            case 3:
                draw_credits(game->window);
                return;
        }
    }
    if(key == KEY_UP){
        if(selected_menu_option <= 0) return;

        selected_menu_option--;
        draw_menu(game->window);
    }
    if(key == KEY_DOWN){
        if(selected_menu_option >= MENU_SIZE - 1) return;

        selected_menu_option++;
        draw_menu(game->window);
    }
}
void MenuState::handle_events(Game* game, int key){
    switch(current_state){
        case MAIN_MENU:
            handle_events_menu(game, key);
            return;
        case SETTINGS:
            handle_events_settings(game, key);
            return;
        case HIGHSCORE:
            handle_events_highscore(game, key);
            return;
        case CREDITS:
            handle_events_credits(game, key);
            return;
        default:
            handle_events_menu(game, key);
            return;
    }
}

void MenuState::update(Game* game){
}

void MenuState::render(Game* game){
}
