#ifndef TERRAIN_
#define TERRAIN_


#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include "player_data_and_movemeant.h"



#define TERRAIN_OBJ_NUM 1


#define FRONT_FACE 0
#define BACK_FACE 1
#define LEFT_FACE 2
#define RIGHT_FACE 3
#define TOP_FACE 4
#define BOT_FACE 5


//Vertices index
#define TOP_LEFT_V 0
#define BOT_LEFT_V 1
#define BOT_RIGHT_V 2
#define TOP_RIGHT_V 3

#define X_COORD 0
#define Y_COORD 1
#define Z_COORD 2

// f * (4*3) + v*3 + c


extern struct player_data player;


// 24 vertices * x,y,z = 24*3 = 72
GLfloat terrainOjbectVertices[2][72];


/*TODO: Add normals for every vertex
  TODO: Decide what the drawCuboid function should return.How you should save the data so it can be used for collision detection
*/

bool isColliding(GLfloat terrainObjArr[]);



void calcCuboidVertices(float center_x, float center_y, float center_z, float height, float length, GLfloat resVertices[]);



#endif