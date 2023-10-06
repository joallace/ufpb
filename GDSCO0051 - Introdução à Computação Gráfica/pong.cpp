#include <GL/glut.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Vertex{
    int x;
    int y;
};

struct PlayerControls{
    bool up;
    bool down;
};

// Player Constants
int playerHeight = WINDOW_HEIGHT * 0.25;
int playerWidth = WINDOW_WIDTH * 0.025;
int playerSpeed = 10;

// Ball Constants
int ballRadius = 16;
int ballSamples = 16;

// Game variables
PlayerControls player1 = {false, false};
PlayerControls player2 = {false, false};
Vertex player1Pos = {50, WINDOW_HEIGHT/2};
Vertex player2Pos = {WINDOW_WIDTH - 50, WINDOW_HEIGHT/2};
Vertex ballPos = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
Vertex ballSpeed = {10, 10};

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

void drawPlayer(Vertex pos) {
    glBegin(GL_QUADS);
        glVertex2i(pos.x - playerWidth/2, pos.y + playerHeight/2);
        glVertex2i(pos.x + playerWidth/2, pos.y + playerHeight/2);
        glVertex2i(pos.x + playerWidth/2, pos.y - playerHeight/2);
        glVertex2i(pos.x - playerWidth/2, pos.y - playerHeight/2);
    glEnd();
}

void drawBall() {
    glBegin(GL_POLYGON);
        for(int i = 0; i < ballSamples; i++){
            float theta = 2.0f * M_PIf * float(i) / ballSamples;

            float local_x = ballRadius * cosf(theta);
            float local_y = ballRadius * sinf(theta);

            glVertex2f(local_x + ballPos.x, local_y + ballPos.y);
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlayer(player1Pos);
    drawPlayer(player2Pos);
    drawBall();

    glutSwapBuffers();
    glFlush();
}

void update(int value) {
    // Ball movement
    ballPos.x += ballSpeed.x;
    ballPos.y += ballSpeed.y;

    if(ballPos.x < 0 || ballPos.x > WINDOW_WIDTH)
        ballSpeed.x *= -1;
    if(ballPos.y < 0 || ballPos.y > WINDOW_HEIGHT)
        ballSpeed.y *= -1;

    // Players movement
    if(player1.up && player1Pos.y >= playerHeight/2)
        player1Pos.y -= playerSpeed;
    if(player1.down && player1Pos.y <= WINDOW_HEIGHT - playerHeight/2)
        player1Pos.y += playerSpeed;

    if(player2.up && player2Pos.y >= playerHeight/2)
        player2Pos.y -= playerSpeed;
    if(player2.down && player2Pos.y <= WINDOW_HEIGHT - playerHeight/2)
        player2Pos.y += playerSpeed;


    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'W':
        case 'w':
            player1.up = true;
            break;
        case 'S':
        case 's':
            player1.down = true;
            break;
    }
}

void handleKeyboardUp(unsigned char key, int x, int y) {
    switch(key) {
        case 'W':
        case 'w':
            player1.up = false;
            break;
        case 'S':
        case 's':
            player1.down = false;
            break;
    }
}


void handleArrowKeys(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            player2.up = true;
            break;
        case GLUT_KEY_DOWN:
            player2.down = true;
            break;
    }
}

void handleArrowKeysUp(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            player2.up = false;
            break;
        case GLUT_KEY_DOWN:
            player2.down = false;
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