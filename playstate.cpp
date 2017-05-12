#include<ncurses.h>
#include "playstate.h"
#include "menustate.h"
#include "logger.h"

bool PlayState::instanceFlag = false;
PlayState* PlayState::instanceObj = NULL;

void PlayState::init(Game *game){
    Log::instance()->info("initialzing", "play state", GREEN_BLACK);

    this->paused = false;
    this->game_over = false;
    this->map = game->get_map();
    game->score = 0;
    wclear(game->window);

    snake = new Snake();
    snake->init(map);

    food = new Food();
    food->set_random_pos(map);

    superfood = new SuperFood();

    draw(game);

    std::string note = "* Use arrow keys *";
    Utils::drawstr(game->window,  (2*WIDTH - note.length())/2, 5, note.c_str(), WHITE_BLACK);
}

PlayState* PlayState::instance(){
    if(instanceFlag)    return instanceObj;

    instanceFlag = true;
    instanceObj = new PlayState();
    return instanceObj;
}

void PlayState::cleanup(){
    Log::instance()->info("cleaning", "play state", GREEN_BLACK);
    delete food;
    delete snake;

    for(int i=0;i < WIDTH; i++){
        delete [] map[i];
    }
    delete [] map;
}

void PlayState::pause(Game* game){
    Log::instance()->info("Game Paused");
    this->paused = true;
    std::string note = "* Game Paused *";
    Utils::drawstr(game->window,  (2*WIDTH - note.length())/2, 5, note, WHITE_BLACK);

    note = "* press ESCAPE to quit *";
    Utils::drawstr(game->window,  (2*WIDTH - note.length())/2, 6, note, WHITE_BLACK);

    note = "* press BACKSPACE to resume *";
    Utils::drawstr(game->window,  (2*WIDTH - note.length())/2, 7, note, WHITE_BLACK);
}

void PlayState::resume(Game* game){
    Log::instance()->info("Game Resumed");
    wclear(game->window);
    this->draw(game);
    this->paused = false;
}

void PlayState::handle_events(Game* game, int key){
    if(this->game_over){
        if(key == BACKSPACE){
            game->change_state(MenuState::instance());
        }
        return;
    }
    else if(this->paused){
        switch(key){
            case BACKSPACE:
                resume(game);
                return;
            case ESCAPE:
                game->quit();
                return;
        }
        return;
    }
    else{
        switch(key){
            case BACKSPACE:
                pause(game);
                return;
            case ESCAPE:
                game->quit();
                return;
        }
    }
    snake->handle_events(key);
}

void PlayState::update_score(Game* game){
    std::string note = "Length: " + std::to_string(snake->body.size()) + " Score: " + std::to_string(game->score);
    Utils::drawstr(game->window,  (2*WIDTH - note.length() - 5), HEIGHT, note, WHITE_BLACK);
}

void PlayState::update(Game* game){
    if(paused || game_over) return;

    snake->add_new_body(map, this->prev_food_pos);
    bool is_valid_move = snake->move(map);
    if(!is_valid_move){
        this->game_over = true;
        std::string note = "* GAME OVER *";
        Utils::drawstr(game->window,  (2*WIDTH - note.length())/2, 10, note, BLACK_RED);
        note = "* press BACKSPACE to return to the menu *";
        Utils::drawstr(game->window,  (2*WIDTH - note.length())/2, 12, note, RED_BLACK);
        return;
    }
    bool catched = snake->food_catched(food);
    if(catched){
        this->prev_food_pos.x = food->x;
        this->prev_food_pos.y = food->y;
        snake->can_add_new_body = true;

        food->set_random_pos(map);
        game->score++;
    }
    if(snake->food_counter >= SUPER_FOOD_COUNTER && !superfood->enabled){
        superfood->enable();
        superfood->set_random_pos(map);
        snake->food_counter = 0;
    }
    if(superfood->enabled){
        if(snake->superfood_catched(superfood)){
            superfood->disable(map);
            game->score += SUPER_FOOD_VALUE*superfood->time_counter;
        }
        snake->food_counter = 0;
        superfood->start_counter();
        if(superfood->should_disable()){
            superfood->disable(map);
        }
    }
}

void PlayState::render(Game* game){
    if(paused || game_over) return;

    draw(game);
}

void PlayState::draw(Game* game){
    for(int i=0;i<WIDTH; i++){
        for(int j=0; j< HEIGHT; j++){
            switch(map[i][j]){
                case BLANK_TILE:
                    Utils::drawblock(game->window, i, j, BLACK);
                    break;
                case WALL_TILE:
                    Utils::drawblock(game->window, i, j, RED);
                    break;
                case FOOD_TILE:
                    Utils::drawblock(game->window, i, j, GREEN);
                    break;
                case SNAKE_TILE:
                    Utils::drawblock(game->window, i, j, game->snake_color);
                    break;
                case SUPER_FOOD_TILE:
                    Utils::drawblock(game->window, i, j, MAGENTA);
                    break;
            }
        }
    }
    update_score(game);
    superfood->show_timer(game);
}
