
#include "terrain.h"

//TODO: ako budes stigao, izmeni funkciju tako da direktno unosi vredonsti u niz umesto da kopira na kraju


void calcCuboidVertices(float center_x, float center_y, float center_z, float height, float length, GLfloat resVerices[])
{
    float half_length = length * 0.5;
    float half_height = height *0.5;

    GLfloat vertices[] = {
        // front-face
        center_x - half_length, center_y + half_height, center_z + half_height, //top-left
        center_x - half_length, center_y - half_height, center_z + half_height, //bot-left
        center_x + half_length, center_y - half_height, center_z + half_height, //bot-right
        center_x + half_length, center_y + half_height, center_z + half_height, //top-right

        // back-face
        center_x - half_length, center_y + half_height, center_z - half_height, //top-left
        center_x - half_length, center_y - half_height, center_z - half_height, //bot-left
        center_x + half_length, center_y - half_height, center_z - half_height, //bot-right
        center_x + half_length, center_y + half_height, center_z - half_height, //top-right

        // left-face
        center_x - half_length, center_y + half_height, center_z - half_height, //top-left
        center_x - half_length, center_y - half_height, center_z - half_height, //bot-left
        center_x - half_length, center_y - half_height, center_z + half_height, //bot-right
        center_x - half_length, center_y + half_height, center_z + half_height, //top-right

        // right-face
        center_x + half_length, center_y + half_height, center_z - half_height, //top-left
        center_x + half_length, center_y - half_height, center_z - half_height, //bot-left
        center_x + half_length, center_y - half_height, center_z + half_height, //bot-right
        center_x + half_length, center_y + half_height, center_z + half_height, //top-right

        // top-face
        center_x - half_length, center_y + half_height, center_z - half_height, //top-left
        center_x - half_length, center_y + half_height, center_z + half_height, //bot-left
        center_x + half_length, center_y + half_height, center_z + half_height, //bot-right
        center_x + half_length, center_y + half_height, center_z - half_height, //top-right

        //bot-face
        center_x - half_length, center_y - half_height, center_z - half_height, //top-left
        center_x - half_length, center_y - half_height, center_z + half_height, //bot-left
        center_x + half_length, center_y - half_height, center_z + half_height, //bot-right
        center_x + half_length, center_y - half_height, center_z - half_height  //top-right

    };

    memcpy(resVerices, vertices, 3*24*sizeof(GLfloat));

    /*glPolygonMode( GL_FRONT, GL_LINE );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices );

    glDrawArrays( GL_QUADS, 0, 24 );
    
    glDisableClientState( GL_VERTEX_ARRAY );
*/
}


bool isColliding(GLfloat terrainObjArr[])
{
    if(player.center_x > terrainObjArr[TOP_FACE * 12 + 3*BOT_LEFT_V + X_COORD] &&
       player.center_x < terrainObjArr[TOP_FACE * 12 + 3*BOT_RIGHT_V + X_COORD] &&
       
       player.center_z < terrainObjArr[TOP_FACE * 12 + 3*BOT_RIGHT_V + Z_COORD] &&
       player.center_z > terrainObjArr[TOP_FACE * 12 + 3*TOP_RIGHT_V + Z_COORD] &&
       
       player.center_y < terrainObjArr[TOP_FACE * 12 + 3*BOT_RIGHT_V + Y_COORD] &&
       player.center_y > terrainObjArr[BOT_FACE * 12 + 3*BOT_RIGHT_V + Y_COORD])
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
    
}
