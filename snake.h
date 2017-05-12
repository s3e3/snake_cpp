#include <vector>
#include "food.h"

enum DIRECTION {NO, UP, DOWN, LEFT, RIGHT};

class Body: public Square{
    public:
        Body(int x, int y, DIRECTION dir): Square(x, y){
            this->direction = dir;
        }
        Body(int x, int y): Square(x, y){
            this->direction = NO;
        }
        DIRECTION direction;
};

class Snake{
    public:
        Snake();
        ~Snake();

        std::vector<Body*> body;

        void init(int** map);
        bool move(int** map);
        void handle_events(int);
        void add_new_body(int**map, COORD);
        bool food_catched(Food*);
        bool superfood_catched(SuperFood*);

        bool can_add_new_body;
        int food_counter;
    private:
        DIRECTION prev_head_dir;
        bool direction_changed;
};
