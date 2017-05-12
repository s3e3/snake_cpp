#include "settingstate.h"
#include "logger.h"
#include "square.h"

bool SettingState::instanceFlag = false;
SettingState* SettingState::instanceObj = NULL;

SettingState::SettingState(){
    menu_title      = "===>------ Settings ------<===";
    selected_menu_option = 0;

    map_values[0] = NO_WALLS;
    map_values[1] = MAP_1;
    map_values[2] = MAP_2;

    snake_color_values[0] = RED;
    snake_color_values[1] = WHITE;
    snake_color_values[2] = MAGENTA;
    snake_color_values[3] = YELLOW;
}

void SettingState::init(Game* game){
    Log::instance()->info("initializing:", "settingstate");

    for(int i=0;i<3;i++){
        if(game->map == map_values[i]){
            this->selected_map_value = i;
            break;
        }
    }
    for(int i=0;i<4;i++){
        if(game->snake_color == snake_color_values[i]){
            this->selected_color_value = i;
            break;
        }
    }
    draw(game);
}

SettingState* SettingState::instance(){
    if(instanceFlag)    return instanceObj;

    instanceFlag = true;
    instanceObj = new SettingState();
    return instanceObj;
}

void SettingState::draw(Game* game){

    wclear(game->window);
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT; j++){
            if(i==0 || i==WIDTH-1 || j==0 || j==HEIGHT-1){
                Square sqr(i,j, RED);
                sqr.draw(game->window);
            }
        }
    }
    menu_options_str[0] = "Map";
    menu_options_str[1] = "Speed";
    menu_options_str[2] = "Color";
    menu_options[0] = Utils::get_map_value(game->map);
    menu_options[1] = std::to_string(game->speed);
    menu_options[2] = Utils::get_color_value(game->snake_color);

    Utils::drawstr(game->window, (2*WIDTH - menu_title.length())/2, 5, menu_title, RED_BLACK);
    for(int i=0;i<SETTING_MENU_SIZE;i++){
        COLOR color = WHITE_BLACK;
        if(selected_menu_option == i)   color = RED_BLACK;
        std::string main_str = Utils::left_alligned_str(menu_options_str[i], 25) + "<" + Utils::mid_alligned_str(menu_options[i], 12) + ">";
        Utils::drawstr(game->window, 20, 6+i, main_str, color);
    }

    std::string note = "* Press BACKSPACE to return to the Main Menu *";
    Utils::drawstr(game->window, (2*WIDTH - note.length())/2, 14, note.c_str(), WHITE_BLACK);
}

void SettingState::cleanup(){
}

void SettingState::pause(Game* game){
}

void SettingState::resume(Game* game){
}

void SettingState::handle_events(Game* game, int key){
    switch(key){
        case BACKSPACE:
            game->pop_state();
            return;
        case KEY_UP:
            if(selected_menu_option <= 0) return;
            selected_menu_option--;
            draw(game);
            return;
        case KEY_DOWN:
            if(selected_menu_option >= SETTING_MENU_SIZE - 1) return;
            selected_menu_option++;
            draw(game);
            return;
        case KEY_LEFT:
           decrease_settings_value(game);
            draw(game);
           return;
        case KEY_RIGHT:
           increase_settings_value(game);
            draw(game);
           return;
    }
    if(key == BACKSPACE){
        game->pop_state();
    }
}

void SettingState::increase_settings_value(Game* game){
    if(selected_menu_option == 0 && selected_map_value < 2){
        selected_map_value++;
        game->map = map_values[selected_map_value];
    }
    if(selected_menu_option == 1){
        game->increase_gamespeed();
    }
    if(selected_menu_option == 2 && selected_color_value < 2){
        selected_color_value++;
        game->snake_color = snake_color_values[selected_color_value];
    }
}
void SettingState::decrease_settings_value(Game* game){
    if(selected_menu_option == 0 && selected_map_value > 0 ){
        selected_map_value--;
        game->map = map_values[selected_map_value];
    }
    if(selected_menu_option == 1){
        game->decrease_gamespeed();
    }
    if(selected_menu_option == 2 && selected_color_value > 0){
        selected_color_value--;
        game->snake_color = snake_color_values[selected_color_value];
    }
}
void SettingState::update(Game* game){
}

void SettingState::render(Game* game){
}
