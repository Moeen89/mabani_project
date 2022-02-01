
#include "other_functions.h"
int menu_button(int x, int y,int current){
    if(x <1100 && x>800){
        if(y<130 && y>80){
            return 1;
        }if(y<200 && y>150){
            return 2;
        }if(y<270 && y>220){
            return 3;
        }
        if(y<650 && y>600){
            return 4;
        }
    }
    return current;
}
int custom_game_button(int x,int y){
    if (y<680 && y>630 && x>965 && x<1240 ){
        return 0;// cancel
    } else if(y<620 && y>570 && x>965 && x<1240){
        return 1; // start
    } else if(y<490 && y>450 && x<1210 && x>905){
        return 5;// random map
    } else if( x<350 && x>70 && y>290 && y<320) {
        return 11;//night elf
    }else if( x<350 && x>70 && y>262 && y<288) {
        return 10;//orc
    }else if( x<350 && x>70 && y>322 && y<352) {
        return 12;//undead
    } else if(x<720 && x>320 && y>50 && y<65){
        return 6;// map1
    }else if(x<720 && x>320 && y>65 && y<90){
        return 7;//map2
    }else if(x<720 && x>320 && y>90&& y<110){
        return 8;//map3
    }
    return -1;
}