#ifndef PLAYER_DATA_
#define PLAYER_DATA_

#include <stdbool.h>

#define player_initialized 1


//Plane in which the player is located and can move in
enum Position_plane
{
    front_xy,
    back_xy,
    right_zy,
    left_zy
};

//x,y,z reperesent the diff in position (where the character should move to)
void move_player_by(double left_right, double up_down);

void initialize_player();

struct player_data{
    //Plane in which the player is located and can move in
    enum Position_plane player_plane;

    double move_speed;
    double jump_target;
    bool jump_active;

    //Player postion in the coordiante system
    double  center_x,  center_y,  center_z;
    //Vek pomeraja
    double vp_left_right, vp_up_down;

};


struct player_data player;


void change_plane(char key);

void rotate_around_y_90(void);




#endif






