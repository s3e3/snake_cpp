#include "utils.h"

class Log{
    public:
        void init();

        void info(std::string str, COLOR color=WHITE_BLACK);
        void info(std::string title, std::string msg, COLOR color=WHITE_BLACK);
        void error(std::string str);
        void enable();
        void disable();

        static Log* instance();

    private:
        Log(){
            y = 1;
            x = 1;
        }
        static bool instanceFlag;
        static Log* instanceObj;
        void draw();

        bool logging;
        int y;
        int x;
        WINDOW* window;
};
