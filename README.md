Run a.out file to just play.

Didnt create the make file, so for now I have to compile all the cpp files individually.

# snake_cpp
console snake game with c++ using ncurses library

simple state machine with states:
 -- intro state
 -- menu_state
 -- play_state
 -- settings_state
 
 each state displays something new on the screen and each state has its own input handling and rendering methods.
 
 Logging:
 -- a small singlton class to just log whats going on in the game
    for e.g:
        -- new food is placed
        -- snakes length is increased
 -- to disable logging just set ENABLE_LOGGING macro as false in utils.h
 
