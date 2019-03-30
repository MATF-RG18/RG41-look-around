#ifndef PLAYER_DATA_
#define PLAYER_DATA_



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

    //Player postion in the coordiante system
    double  center_x,  center_y,  center_z;

};







#endif






