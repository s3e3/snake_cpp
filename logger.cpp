#include "logger.h"

bool Log::instanceFlag = false;
Log* Log::instanceObj = NULL;

Log* Log::instance(){
    if(instanceFlag)    return instanceObj;

    instanceFlag = true;
    instanceObj = new Log();
    return instanceObj;
}

void Log::init(){
    int width = 15;
    int height = HEIGHT;
    window = newwin(height, 2*width, 0, 2*WIDTH);
    scrollok(window, true);
}

void Log::enable(){
    init();
    wrefresh(window);
    logging = true;
}

void Log::disable(){
    logging = false;
    delwin(window);
}

void Log::info(std::string str, COLOR color){
    if(!logging) return;

    str = ">" + str + '\n';
    wattron(window, COLOR_PAIR(color));
    wprintw(window, str.c_str());
    wattroff(window, COLOR_PAIR(color));
    wrefresh(window);
}

void Log::info(std::string title, std::string msg, COLOR color){
    if(!logging) return;

    title = ">" + title + ": ";
    wattron(window, COLOR_PAIR(color));
    wattron(window, A_BOLD);
    wprintw(window, title.c_str());
    wattroff(window, A_BOLD);
    msg += '\n';
    wprintw(window, msg.c_str());
    wattroff(window, COLOR_PAIR(color));
    wrefresh(window);
}

void Log::error(std::string str){
    info("Err", str, RED_BLACK);
}
