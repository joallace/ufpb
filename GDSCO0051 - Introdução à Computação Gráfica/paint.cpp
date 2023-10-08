#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <algorithm>

GLint WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;
GLint point[2] = {-1, -1};
bool active = false;
int menu = 0;

void initializeGlut(int argc, char *argv[]){
    //Inicializa a biblioteca GLUT e negocia uma 
    //seção com o sistema de janelas
    glutInit(&argc, argv);

    //Define qual será o modo inicial de display
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //Definir a posição inicial da janela, passando 
    //canto superior esquerdp
    glutInitWindowPosition(100,100);

    //Define a largura e altura da janela
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //Cria a janela, passando o titulo
    glutCreateWindow("Meu primeiro programa OpenGL");
}

void initialize(){
    //Define a cor de fundo
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    //Matriz que usaremos para opperacoes
    glMatrixMode(GL_MODELVIEW);

    //erquerdo, direito, baixo, cima
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0);

    glColor3f(1.0f, 0.0f, 0.0f);
}

void handleMenu(int index){
    if(index==2)
        glClear(GL_COLOR_BUFFER_BIT);
    else
        menu = index;

    point[0] = -1;
    glutPostRedisplay();
}

void createMenu(){
    GLint draw_menu = glutCreateMenu(handleMenu);
    glutAddMenuEntry("Ponto", 4);
    glutAddMenuEntry("Linha", 5);
    glutAddMenuEntry("Retangulo", 6);
    glutAddMenuEntry("Circulo", 7);
    glutAddMenuEntry("Livre", 8);
    
    GLint main_menu = glutCreateMenu(handleMenu);
    glutAddSubMenu("Desenhar", draw_menu);
    glutAddMenuEntry("Limpar", 2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawPoint(GLint x, GLint y){
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawLine(GLint x, GLint y){
    if(point[0] == -1){
        point[0] = x;
        point[1] = y;
    }
    else{
        glBegin(GL_LINES);
            glVertex2i(point[0], point[1]);
            glVertex2i(x, y);
        glEnd();

        point[0] = -1;
        glFlush();
    }
}

void drawRect(GLint x, GLint y){
    if(point[0] == -1){
        point[0] = x;
        point[1] = y;
    }
    else{
        glBegin(GL_LINE_LOOP);
            glVertex2i(std::min(point[0], x), std::max(point[1], y));
            glVertex2i(std::max(point[0], x), std::max(point[1], y));
            glVertex2i(std::max(point[0], x), std::min(point[1], y));
            glVertex2i(std::min(point[0], x), std::min(point[1], y));
        glEnd();

        point[0] = -1;
        glFlush();   
    }
}

void drawCirc(GLint x, GLint y){
    if(point[0] == -1){
        point[0] = x;
        point[1] = y;
    }
    else{
        GLfloat radius = sqrt(pow(x-point[0], 2)+pow(y-point[1], 2))/2;
        GLfloat origin_x = (point[0]+x)/2;
        GLfloat origin_y = (point[1]+y)/2;

        glBegin(GL_LINE_LOOP);
            for(int i = 0; i < 16; i++){
                GLfloat theta = 2.0f * M_PIf * float(i) / 16.0f;

                GLfloat local_x = radius * cosf(theta);
                GLfloat local_y = radius * sinf(theta);

                glVertex2f(local_x + origin_x, local_y + origin_y);
            }
        glEnd();

        point[0] = -1;
        glFlush();   
    }
}

void handleMouse(GLint button, GLint action, GLint x, GLint y){
    if(button == GLUT_LEFT_BUTTON && action == GLUT_UP){
        active = false;
    }
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        active = true;
        switch (menu){
        case 4:
            drawPoint(x, y);
            break;
        case 5:
            drawPoint(x, y);
            drawLine(x, y);
            break;
        case 6:
            drawPoint(x, y);
            drawRect(x, y);
            break;
        case 7:
            drawPoint(x, y);
            drawCirc(x, y);
            break;
        default:
            break;
        }
    }
}

void handleMouseMovement(GLint x, GLint y){
    if(active && menu == 8)
        drawPoint(x, y);
}

void handleKeyboard(unsigned char key, GLint x, GLint y){
    switch(key){
    case 'R':
    case 'r':
        printf("%c\n", key);
        glColor3f(1.0f, 0.0f, 0.0f);
        break;
    case 'G':
    case 'g':
        printf("%c\n", key);
        glColor3f(0.0f, 1.0f, 0.0f);
        break;
    case 'B':
    case 'b':
        printf("%c\n", key);
        glColor3f(0.0f, 0.0f, 1.0f);
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{   
    initializeGlut(argc, argv);
    initialize();
    createMenu();
    
    glutMotionFunc(handleMouseMovement);
    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);

    glutMainLoop();
    
    return EXIT_SUCCESS;
}
