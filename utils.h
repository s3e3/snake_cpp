#ifndef UTILS_H_
#define UTILS_H_

#include <sys/timeb.h>
#include <string>
#include <ncurses.h>

enum COLOR {
    BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, 
    RED_BLACK, BLACK_RED, 
    YELLOW_BLACK, BLACK_YELLOW,
    CYAN_BLACK, BLACK_CYAN,
    WHITE_BLACK, BLACK_WHITE,
    GREEN_BLACK, BLACK_GREEN,
    };

enum MAP {NO_WALLS, MAP_1, MAP_2, MAP_3};

#define WIDTH   40
#define HEIGHT  25

#define BACKSPACE   127
#define ESCAPE      27
#define ENTER       10

#define BLANK_TILE          0
#define WALL_TILE            1
#define SNAKE_TILE          2
#define FOOD_TILE           3
#define SUPER_FOOD_TILE     4

#define SUPER_FOOD_COUNTER          8
#define SUPER_FOOD_VISIBLE_LIMIT    10
#define SUPER_FOOD_VALUE            10

#define SNAKE_MIN_SPEED     4
#define SNAKE_START_SPEED   10
#define SNAKE_MAX_SPEED     15

struct COORD{
    int x;
    int y;
};

class Utils{
    public:
        static void init(){
            for(int i=0;i<8;i++){
                init_pair(i,i,i);
            }
            init_pair(RED_BLACK, RED, BLACK);
            init_pair(BLACK_RED, BLACK, RED);
            init_pair(BLACK_YELLOW, BLACK, YELLOW);
            init_pair(YELLOW_BLACK, YELLOW, BLACK);
            init_pair(WHITE_BLACK, WHITE, BLACK);
            init_pair(GREEN_BLACK, GREEN, BLACK);
            init_pair(BLACK_GREEN, BLACK, GREEN);
            init_pair(CYAN_BLACK, CYAN, BLACK);
            init_pair(BLACK_CYAN, BLACK, CYAN);
        }

        static void drawstr(WINDOW* win, int x, int y, std::string str, COLOR color){
            wattron(win, COLOR_PAIR(color));
            mvwaddstr(win, y, x, str.c_str());
            wattroff(win, COLOR_PAIR(color));
        }

        static void drawch(WINDOW* win, int x, int y, char ch, COLOR color){
            wattron(win, COLOR_PAIR(color));
            mvwaddch(win, y, x, ch);
            wattroff(win, COLOR_PAIR(color));
        }

        static void drawblock(WINDOW* win, int x, int y, COLOR color){
            wattron(win, COLOR_PAIR(color));
            mvwaddch(win, y, 2*x, ' ');
            mvwaddch(win, y, 2*x + 1, ' ');
            wattroff(win, COLOR_PAIR(color));
        }

        static int getMilliCount(){
            timeb tb;
            ftime( &tb );
            int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
            return nCount;
        }

        static std::string get_map_value(MAP val){
            switch(val){
                case NO_WALLS: 
                    return "No Walls";
                case MAP_1:
                    return "Map 1";
                case MAP_2:
                    return "Map 2";
                case MAP_3:
                    return "Map 3";
                default:
                    return "";
            }
        }

        static std::string get_color_value(COLOR clr){
            switch(clr){
                case BLACK:
                    return "Black";
                case RED:
                    return "Red";
                case GREEN:
                    return "Green";
                case CYAN:
                    return "Cyan";
                case YELLOW:
                    return "Yellow";
                case MAGENTA:
                    return "Magenta";
                default:
                    return "White";
            }
        }

        static std::string left_alligned_str(std::string str, int width){
            if(width <= str.length()) return str;
            std::string sstr = "";
            for(int i=0; i<=(width - str.length()); i++){
                sstr += " ";
            }
            return str+sstr;
        }
        static std::string right_alligned_str(std::string str, int width){
            if(width <= str.length()) return str;
            std::string sstr = "";
            for(int i=0;i<(width - str.length()); i++){
                sstr += " ";
            }
            sstr += str;
            return sstr;
        }
        static std::string mid_alligned_str(std::string str, int width){
            if(width <= str.length()) return str;
            std::string sstr = "";
            for(int i=0;i<(width - str.length())/2;i++){
                sstr += " ";
            }
            return sstr + str + sstr;
        }
};
#endif
