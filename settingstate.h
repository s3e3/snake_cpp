#ifndef SETTINGSSTATE_H_
#define SETTINGSSTATE_H_

#include <string>
#include "gamestate.h"
#include "utils.h"


#define SETTING_MENU_SIZE 3

class SettingState: public GameState{
    public:
        void init(Game*);
        void cleanup();

        void pause(Game*);
        void resume(Game*);

        void handle_events(Game* game, int key);
        void update(Game* game);
        void render(Game* game);
        static SettingState* instance();


    private:
        SettingState();
        void draw(Game*);
        void decrease_settings_value(Game*);
        void increase_settings_value(Game*);
        int selected_map_value;
        int selected_color_value;
        MAP map_values[3];
        COLOR snake_color_values[4];

        std::string menu_title;
        std::string menu_options[SETTING_MENU_SIZE];
        std::string menu_options_str[SETTING_MENU_SIZE];
        int selected_menu_option;

        static bool instanceFlag;
        static SettingState* instanceObj;
};
#endif
