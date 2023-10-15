#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>
#include <stdio.h>
#include "structures.h"

class Player{
    private:
        Vertex size;
        Vertex defaultPosition;
        int speed;
        char id;

    public:
        Player(char id, Vertex initialPosition);

        int score;
        PlayerControls controls;
        Vertex position;

        void move();
        void draw();
        void drawScore(Vertex position);
        char goal();
        bool collide(Vertex ballPos, int ballRadius);
        char getId();
        Vertex getSize();
};

#endif