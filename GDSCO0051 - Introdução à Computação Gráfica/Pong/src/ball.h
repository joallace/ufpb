#ifndef BALL_H
#define BALL_H

#include <GL/glut.h>
#include <math.h>
#include "structures.h"
#include "audio.h"

class Ball{
    private:
        int samples;
        int radius;
        Vertex defaultPosition;
        Vertex defaultSpeed;
        Audio *audioPlayer;

        void collide(Vertex player1Pos, Vertex player2Pos, Vertex playerSize);


    public:
        Ball(Vertex initialPosition, Audio *audioPlayerPtr);
        Vertex speed;
        Vertex position;

        void moveAndCollide(Vertex player1Pos, Vertex player2Pos, Vertex playerSize);
        void draw();
        void reset();
};

#endif