#include "snake.h"
#include "logger.h"

Snake::Snake(){
    this->food_counter = 0;
}

Snake::~Snake(){
    Log::instance()->info("Destructor", "snake class", CYAN_BLACK);
    for(int i=0;i<body.size();i++){
        delete body[i];
    }
    body.clear();
}
void Snake::init(int** map){
    body.push_back(new Body(5,10, RIGHT));
    body.push_back(new Body(4,10, RIGHT));
    body.push_back(new Body(3,10, RIGHT));
    map[5][10] = SNAKE_TILE;
    map[4][10] = SNAKE_TILE;
    map[3][10] = SNAKE_TILE;

    this->prev_head_dir = this->body.front()->direction;
    this->direction_changed = false;
}

bool Snake::move(int** map){
    for(int i=body.size()-1; i >=1; i--){
        if(i==1 && body[i-1]->direction != NO && this->direction_changed){
            body[i]->direction = this->prev_head_dir;
            this->direction_changed = false;
        }
        else body[i]->direction = body[i-1]->direction;
    }

    for(int i=0; i < body.size(); i++){
        int old_x = body[i]->x;
        int old_y = body[i]->y;
        switch(body[i]->direction){
            case UP:
                body[i]->y -= 1;
                break;
            case DOWN:
                body[i]->y += 1;
                break;
            case LEFT:
                body[i]->x -= 1;
                break;
            case RIGHT:
                body[i]->x += 1;
                break;
            case NO:
                break;
        }
        int nx = body[i]->x;
        int ny = body[i]->y;

        if(nx < WIDTH && nx >=0 && ny < HEIGHT && ny >= 0 && (map[nx][ny] == WALL_TILE || map[nx][ny] == SNAKE_TILE)){
            return false;
        }
        if( body[i]->x < 0 )    body[i]->x = WIDTH - 1;
        else if( body[i]->x > WIDTH-1 )   body[i]->x = 0;
        if( body[i]->y < 0 )    body[i]->y = HEIGHT - 1;
        else if( body[i]->y > HEIGHT-1 )   body[i]->y = 0;

        map[old_x][old_y] = BLANK_TILE;
        map[body[i]->x][body[i]->y] = SNAKE_TILE;
    }
    return true;
}

void Snake::add_new_body(int** map, COORD pos){
    if(!this->can_add_new_body) return;

    Body* back = this->body.back();

    if(back->direction == LEFT && back->y == pos.y && back->x == pos.x-1){
        this->body.push_back(new Body(pos.x, pos.y, LEFT));
        map[pos.x][pos.y] = SNAKE_TILE;
        this->can_add_new_body = false;
    }
    else if(back->direction == RIGHT && back->y == pos.y && back->x == pos.x+1){
        this->body.push_back(new Body(pos.x, pos.y, RIGHT));
        map[pos.x][pos.y] = SNAKE_TILE;
        this->can_add_new_body = false;
    }
    else if(back->direction == UP && back->x == pos.x && back->y == pos.y-1){
        this->body.push_back(new Body(pos.x, pos.y, UP));
        map[pos.x][pos.y] = SNAKE_TILE;
        this->can_add_new_body = false;
    }
    else if(back->direction == DOWN && back->x == pos.x && back->y == pos.y + 1){
        this->body.push_back(new Body(pos.x, pos.y,DOWN));
        map[pos.x][pos.y] = SNAKE_TILE;
        this->can_add_new_body = false;
    }
}

void Snake::handle_events(int key){
    Body* head = body.front();

    this->prev_head_dir = head->direction;
    switch(key){
        case KEY_UP:
            if(head->direction == DOWN) return;
            head->direction = UP;
            this->direction_changed = true;
            break;
        case KEY_DOWN:
            if(head->direction == UP) return;
            head->direction = DOWN;
            this->direction_changed = true;
            break;
        case KEY_LEFT:
            if(head->direction == RIGHT) return;
            head->direction = LEFT;
            this->direction_changed = true;
            break;
        case KEY_RIGHT:
            if(head->direction == LEFT) return;
            head->direction = RIGHT;
            this->direction_changed = true;
            break;
    }
}

bool Snake::food_catched(Food* food){
    Body* head = body.front();

    if(head->x == food->x && head->y == food->y){
        this->food_counter++;
        return true;
    }
    return false;
}

bool Snake::superfood_catched(SuperFood* superfood){
    Body* head = body.front();

    if(head->x == superfood->x && head->y == superfood->y && superfood->enabled){
        return true;
    }
    return false;
}
