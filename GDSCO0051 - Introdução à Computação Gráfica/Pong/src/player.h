#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>
#include "structures.h"

class Player{
    private:
        Vertex size;
        Vertex defaultPosition;
        int speed;

    public:
        Player(Vertex initialPosition);

        PlayerControls controls;
        Vertex position;

        void move();
        void draw();
        void reset();
        Vertex getSize();
};

#endif