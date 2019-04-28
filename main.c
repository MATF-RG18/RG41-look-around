#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player_data_and_movemeant.h"
#include "terrain.h"
//#include "player_data_and_movement.c"

#define SPACEBAR 32

#define A_PRESS 0
#define D_PRESS 1
#define JUMP_PRESS 3
bool pressed_keys[3];


double acc;

extern struct player_data player;
extern bool PLAYER_AND_TERRAIN_COLLISION;

int timer_active = 0;

static void on_display(void);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void on_keyboard(unsigned char key, int x, int y);
static void on_keyboard_up(unsigned char key, int x, int y);



void draw_debug_coosys(void);

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreira se prozor. */
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_keyboard_up);
    glutTimerFunc(10, on_timer, 0);

    glClearColor(0.1, 0.1, 0.1, 1);
    glEnable(GL_DEPTH_TEST);

    initialize_player();
    calcCuboidVertices(1,1,1,1,2, terrainOjbectVertices[0]);

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    


    glPushMatrix();

        move_player_by(player.vp_left_right, player.vp_up_down);
        player.vp_up_down -= acc;
        glTranslatef(player.center_x, player.center_y, player.center_z);
        glColor3f(1, 0.5, 0);
       // drawCuboid(1,1,1, 1, 2 );
        

 

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, terrainOjbectVertices[0]);

    glDrawArrays( GL_QUADS, 0, 24 );
    
    glDisableClientState( GL_VERTEX_ARRAY );



       // glutSolidCube(1);
    glPopMatrix();


    calcCuboidVertices(4,1,1, 1, 2, terrainOjbectVertices[1]);


        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, terrainOjbectVertices[1]);

    glDrawArrays( GL_QUADS, 0, 24 );
    
    glDisableClientState( GL_VERTEX_ARRAY );


        draw_debug_coosys();

        glutSwapBuffers();
}




void draw_debug_coosys()
{
         glDisable(GL_LIGHTING);
         glBegin(GL_LINES);
         glColor3f (1, 0, 0);
         glVertex3f(1000, 0, 0);
         glVertex3f(0, 0, 0);

         glColor3f (0, 1, 0);
         glVertex3f(0, 1000, 0);
         glVertex3f(0, 0, 0);

         glColor3f (0, 0, 1);
         glVertex3f(0, 0, 1000);
         glVertex3f(0, 0, 0);
         glEnd();
         glEnable(GL_LIGHTING);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    
    switch(key){
        case 'd':
        case 'D':
            player.vp_left_right = player.move_speed;   
            pressed_keys[D_PRESS] = true; 
           // glutPostRedisplay();
            glutTimerFunc(10, on_timer, 0);
            break;
        case 'a':
        case 'A':
            player.vp_left_right = -(player.move_speed);
            pressed_keys[A_PRESS] = true;

            //glutPostRedisplay();
            glutTimerFunc(10, on_timer, 0);
            break;
        case SPACEBAR:
            if(!player.jump_active){    
                pressed_keys[JUMP_PRESS] = true;
                player.jump_active = true;
                player.jump_target = player.center_y + 10;
                player.vp_up_down = 0.4;
                //pROMENI KADA DODJE KOLIZIJA
                acc = 0.02;

            }
            glutTimerFunc(10, on_timer, 0);
            //glutPostRedisplay();
            break;
        case 'q':
        case 'Q':
        case 'r':
        case 'R':
            change_plane(key);
            break;


        default:
            break;
    }

}

static void on_keyboard_up(unsigned char key, int x, int y)
{
    switch(key){
        case 'd':
        case 'D':
            pressed_keys[D_PRESS] = false;
            if(!pressed_keys[A_PRESS]){
                player.vp_left_right = 0;
            }
            else {
                player.vp_left_right = -player.move_speed;
            }
            break;
        case 'a':
        case 'A':
            pressed_keys[A_PRESS] = false;
            if(!pressed_keys[D_PRESS]){
                player.vp_left_right = 0;
            }
            else{
                player.vp_left_right = player.move_speed;
            }
            glutPostRedisplay();
            break;
        case SPACEBAR:
            player.vp_up_down = 0;
            glutPostRedisplay();
            break;
        default:
            break;
        
    }


}



static void on_timer(int value)
{
   

   //Ubaciti ovde check za koliziju
    
   
        if(player.jump_active) {
            if(player.center_z+1 > player.jump_target){
                player.vp_up_down = -0.2;
            }
        }



    glutPostRedisplay();
    glutTimerFunc(10, on_timer, 0);

}

static void on_reshape(int width, int height)
{
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1, 1500);
   // glOrtho(-20.0, 20.0, -20.0, 20.0, -10.5, 30.5);
    //Podesi lepo perspektivu, ovo neka bude placeholder
}
