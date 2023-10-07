#include <GL/glut.h>
#include <math.h>
#include "structures.h"

class Ball{
    private:
        int samples;
        int radius;
        Vertex defaultPosition;

        void collide(Vertex player1Pos, Vertex player2Pos, Vertex playerSize);


    public:
        Ball(Vertex initialPosition);
        Vertex speed;
        Vertex position;

        void moveAndCollide(Vertex player1Pos, Vertex player2Pos, Vertex playerSize);
        void draw();
        void reset();
};