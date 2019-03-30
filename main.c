#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "player_data_and_movemeant.h"
//#include "player_data_and_movement.c"


#define a_press 0
#define d_press 1

extern struct player_data player;

int timer_active = 0;


static void on_display(void);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void on_keyboard(unsigned char key, int x, int y);

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
    glutKeyboardFunc(on_keyboard);
    //glutTimerFunc(30, on_timer, 0);

    glClearColor(0.1, 0.1, 0.1, 1);
    glEnable(GL_DEPTH_TEST);

    initialize_player();
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-0.3, 10, 3, 0, 0, 0, 0, 1, 0);


    glPushMatrix();
        glTranslatef(player.center_x, player.center_y, player.center_z);
        glColor3f(1, 0.5, 0);
        glutSolidCube(1);
        glColor3f(1, 0.5, 0);

    glPopMatrix();
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
            printf("Detected d\n");
            move_player_by(0.2, 0);
            glutPostRedisplay();
            //glutTimerFunc(30, on_timer, d_press);
            break;
        case 'a':
        case 'A':
            move_player_by(-0.2, 0);
            glutPostRedisplay();
            //glutTimerFunc(30, on_timer, a_press);
            break;


        default:
            break;
    }

}

/*static void on_timer(int value)
{
    if(value == a_press) {
        move_player_by(-0.2, 0);
    }
    else if (value == d_press) {
        move_player_by(0.2, 0);
    }
    else {
        return;
    }

    glutPostRedisplay();

}
*/
static void on_reshape(int width, int height)
{
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1, 1500);
}
