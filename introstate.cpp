#include "introstate.h"

bool IntroState::instanceFlag = false;
IntroState* IntroState::instanceObj = NULL;

void IntroState::init(Game *){
}

IntroState* IntroState::instance(){
    if(instanceFlag)    return instanceObj;

    instanceFlag = true;
    instanceObj = new IntroState();
    return instanceObj;
}

void IntroState::cleanup(){
}

void IntroState::pause(Game* game){
}

void IntroState::resume(Game* game){
}

void IntroState::handle_events(Game* game, int key){
}

void IntroState::update(Game* game){
}

void IntroState::render(Game* game){
}
