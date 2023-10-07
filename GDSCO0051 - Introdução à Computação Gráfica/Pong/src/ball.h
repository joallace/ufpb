#include <GL/glut.h>
#include <math.h>
#include "structures.h"

class Ball{
    private:
        int samples;
        int radius;
        Vertex defaultPosition;
        
        void collide(Vertex player1Pos, Vertex player2Pos);
    public:
        Ball(Vertex initialPosition);
        Vertex speed;
        Vertex position;

        void move(Vertex player1Pos, Vertex player2Pos);
        void draw();
        void reset();
};