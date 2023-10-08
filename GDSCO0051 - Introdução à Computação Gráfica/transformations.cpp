#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <algorithm>

GLint WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;
GLint point[2] = {-1, -1};
bool active = false;
int menu = 0;

template <typename T>
struct Coordinates{
    T x, y;

    Coordinates operator-() const {
        return {-x, -y};
    }
};

typedef Coordinates<int> Vertex;

struct Object {
    Vertex *v;
    int n;
};

Object *createObject(){
    Object *obj = (Object*)malloc(sizeof(Object));
    obj->n = 3;
    obj->v = (Vertex*)malloc(sizeof(Vertex)*obj->n);
    obj->v[0].x = 300;
    obj->v[0].y = 200;
    obj->v[1].x = 350;
    obj->v[1].y = 275;
    obj->v[2].x = 350;
    obj->v[2].y = 175;

    return obj;
}

Object *obj;
Vertex delta = {0};
Coordinates<float> scale = {1, 1};
float angle = 60;

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

    obj = createObject();
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

Vertex getObjCenter(Object *obj){
    Vertex center = {0, 0};

    for(int i=0; i<obj->n; i++){
        center.x += obj->v[i].x;
        center.y += obj->v[i].y;
    }

    return {center.x/obj->n, center.y/obj->n};
}


Vertex transform2d(Vertex v, Vertex delta){
    int final_coordinates[3] = {0, 0, 1};
    int homogenous_coordinates[3] = {v.x, v.y, 1};
    int transform_matrix[3][3]= {
        1, 0, delta.x,
        0, 1, delta.y,
        0, 0, 1
    };

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            final_coordinates[i] += transform_matrix[i][j] * homogenous_coordinates[j];

    return {final_coordinates[0], final_coordinates[1]};
}

Vertex scale2d(Vertex v, Coordinates<float> scale){
    int final_coordinates[3] = {0, 0, 1};
    int homogenous_coordinates[3] = {v.x, v.y, 1};
    float transform_matrix[3][3]= {
        scale.x, 0, 0,
        0, scale.y, 0,
        0, 0, 1
    };


    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            final_coordinates[i] += transform_matrix[i][j] * homogenous_coordinates[j];

    return {final_coordinates[0], final_coordinates[1]};
}

Vertex rotate2d(Vertex v, float angle){
    int final_coordinates[3] = {0, 0, 1};
    int homogenous_coordinates[3] = {v.x, v.y, 1};
    float s = sin(angle*M_PIf/180);
    float c = cos(angle*M_PIf/180);
    float transform_matrix[3][3]= {
        c, -s, 0,
        s, c, 0,
        0, 0, 1
    };

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            final_coordinates[i] += transform_matrix[i][j] * homogenous_coordinates[j];

    return {final_coordinates[0], final_coordinates[1]};
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

void drawObject(){
    Vertex v, center = getObjCenter(obj);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    for(int i=0; i < obj->n; i++){
        v = transform2d(obj->v[i], -center);
        v = rotate2d(v, angle);
        v = scale2d(v, scale);
        v = transform2d(v, center);
        v = transform2d(v, delta);
        // v = transform2d(obj->v[i], delta);
        glVertex2i(v.x, v.y);
    }
    glEnd();
    glFlush();
}

void handleMouse(GLint button, GLint action, GLint x, GLint y){
    if(button == GLUT_LEFT_BUTTON && action == GLUT_UP)
        active = false;

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
        case 'W':
        case 'w':
            delta.y -= 4;
            drawObject();
            break;
        case 'S':
        case 's':
            delta.y += 4;
            drawObject();
            break;
        case 'A':
        case 'a':
            delta.x -= 4;
            drawObject();
            break;
        case 'D':
        case 'd':
            delta.x += 4;
            drawObject();
            break;
        case 'Q':
        case 'q':
            angle--;
            printf("%f\n", angle);
            drawObject();
            break;
        case 'E':
        case 'e':
            angle++;
            printf("%f\n", angle);
            drawObject();
            break;
        case 'R':
        case 'r':
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 'G':
        case 'g':
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 'B':
        case 'b':
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        default:
            break;
    }
}

void handleArrowKeys(int key, int x, int y){
    switch (key){
        case GLUT_KEY_LEFT:
            scale.x -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            scale.x += 0.1;
            break;
        case GLUT_KEY_DOWN:
            scale.y -= 0.1;
            break;
        case GLUT_KEY_UP:
            scale.y += 0.1;
            break;
        
        default:
            return;
    }
    drawObject();
}

int main(int argc, char *argv[])
{   
    initializeGlut(argc, argv);
    initialize();
    createMenu();
    
    // glutDisplayFunc(drawObject);
    glutMotionFunc(handleMouseMovement);
    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);
    glutSpecialFunc(handleArrowKeys);

    glutMainLoop();
    
    return EXIT_SUCCESS;
}
