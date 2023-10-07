#include <GL/glut.h>
#include <math.h>

#include "structures.h"
#include "player.h"
#include "ball.h"

Player *player1 = new Player({50, WINDOW_HEIGHT/2});
Player *player2 = new Player({WINDOW_WIDTH - 50, WINDOW_HEIGHT/2});
Ball *ball = new Ball({WINDOW_WIDTH/2, WINDOW_HEIGHT/2});

void initializeGlut(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(WINDOW_WIDTH/2, -WINDOW_HEIGHT/2);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pong");
    glutIgnoreKeyRepeat(true);
}

void initializeOpenGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    player1->draw();
    player2->draw();
    ball->draw();

    glutSwapBuffers();
}

void update(int value) {
    ball->move(player1->position, player2->position);
    player1->move();
    player2->move();

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'W':
        case 'w':
            player1->controls.up = true;
            break;
        case 'S':
        case 's':
            player1->controls.down = true;
            break;
    }
}

void handleKeyboardUp(unsigned char key, int x, int y) {
    switch(key) {
        case 'W':
        case 'w':
            player1->controls.up = false;
            break;
        case 'S':
        case 's':
            player1->controls.down = false;
            break;
    }
}

void handleArrowKeys(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            player2->controls.up = true;
            break;
        case GLUT_KEY_DOWN:
            player2->controls.down = true;
            break;
    }
}

void handleArrowKeysUp(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            player2->controls.up = false;
            break;
        case GLUT_KEY_DOWN:
            player2->controls.down = false;
            break;
    }
}

int main(int argc, char** argv) {
    initializeGlut(argc, argv);
    initializeOpenGL();

    glutDisplayFunc(display);

    glutKeyboardFunc(handleKeyboard);
    glutKeyboardUpFunc(handleKeyboardUp);
    glutSpecialFunc(handleArrowKeys);
    glutSpecialUpFunc(handleArrowKeysUp);

    glutTimerFunc(25, update, 0);
    glutMainLoop();
    
    return 0;
}