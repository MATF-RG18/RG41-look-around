#include <stdio.h>
#include <stdbool.h>
#include "player_data_and_movemeant.h"

struct player_data player;

//TODO: Promeni ovo u left-right axys i salji smer iz keyboard funkcije
/*Direction of movemeant is sent by the keyboard function and passed down
  d = +left_rigt, a = -left_right
*/
void move_player_by(double left_right, double up_down)
{
    if(player_initialized) {
        if(player.player_plane == front_xy) {
            printf("xy hit: " );
             player.center_x += left_right;
             player.center_y += up_down;
        }
        else if (player.player_plane == back_xy) {
             player.center_x -= left_right;
             player.center_y += up_down;
        }
        else if (player.player_plane == left_zy) {
             player.center_z -= left_right;
             player.center_y += up_down;
        }
        else {
             player.center_z += left_right;
             player.center_y += up_down;
        }
        printf("%.3f %.3f %.3f\n", player.center_x, player.center_y, player.center_z);
    }
    else {
        printf("Player not init");
    }
}

void initialize_player()
{
    player.player_plane = front_xy;
    player.center_x = player.center_y = player.center_z = 0;
    player.vp_up_down = player.vp_left_right = 0;

    player.move_speed = 0.2;

    player.jump_active = false;
    player.jump_target = player.center_z;

  //  player_initialized = 1;
}