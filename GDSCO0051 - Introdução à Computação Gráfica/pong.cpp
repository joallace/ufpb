#include <GL/glut.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

template <typename T>
struct Coordinates{
    T x, y;
};

typedef Coordinates<int> Vertex;

Vertex player1Pos = {50, WINDOW_HEIGHT/2};
Vertex player2Pos = {WINDOW_WIDTH - 50, WINDOW_HEIGHT/2};

Vertex ballPos = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
float ballRadius = 16;

Vertex ballSpeed = {10, 10};

int playerHeight = WINDOW_HEIGHT * 0.25;
int playerWidth = WINDOW_WIDTH * 0.025;
int playerSpeed = 10;

void initializeGlut(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(WINDOW_WIDTH/2, -WINDOW_HEIGHT/2);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pong");
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

void drawBall(int n_samples) {
    glBegin(GL_POLYGON);
        for(int i = 0; i < n_samples; i++){
            GLfloat theta = 2.0f * M_PIf * float(i) / n_samples;

            GLfloat local_x = ballRadius * cosf(theta);
            GLfloat local_y = ballRadius * sinf(theta);

            glVertex2f(local_x + ballPos.x, local_y + ballPos.y);
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPlayer(player1Pos);
    drawPlayer(player2Pos);
    drawBall(16);
    glutSwapBuffers();
    glFlush();
}

void update(int value) {
    ballPos.x += ballSpeed.x;
    ballPos.y += ballSpeed.y;

    if(ballPos.x < 0 || ballPos.x > WINDOW_WIDTH)
        ballSpeed.x *= -1;
    if(ballPos.y < 0 || ballPos.y > WINDOW_HEIGHT)
        ballSpeed.y *= -1;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'W':
        case 'w':
            if(player1Pos.y >= playerHeight/2)
                player1Pos.y -= playerSpeed;
            break;
        case 'S':
        case 's':
            if(player1Pos.y <= WINDOW_HEIGHT - playerHeight/2)
                player1Pos.y += playerSpeed;
            break;
    }
}

void handleArrowKeys(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            if(player2Pos.y >= playerHeight/2)
                player2Pos.y -= playerSpeed;
            break;
        case GLUT_KEY_DOWN:
            if(player2Pos.y <= WINDOW_HEIGHT - playerHeight/2)
                player2Pos.y += playerSpeed;
            break;
    }
}

int main(int argc, char** argv) {
    initializeGlut(argc, argv);
    initializeOpenGL();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(handleArrowKeys);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    
    return 0;
}