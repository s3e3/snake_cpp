#include "map.h"
#include "square.h"

Map::Map(){
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT; j++){
            if(i==0 || i==WIDTH-1 || j==0 || j==HEIGHT-1){
                this->map[i][j] = 1;
            }
            else{
                this->map[i][j] = 0;
            }
        }
    }
}

void Map::draw(Game* game){
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT;j++){
            if(this->map[i][j] == 1){
                Square sqr(i,j, RED);
                sqr.draw(game->window);
            }
            else{
                Square sqr(i,j, BLACK);
                sqr.draw(game->window);
            }
        }
    }
}
