#ifndef BALL_H
#define BALL_H

#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include "structures.h"
#include "player.h"
#include "audio.h"

class Ball{
    private:
        int samples;
        int radius;
        Vertex defaultPosition;
        Vertex defaultSpeed;
        Audio *audioPlayer;
        char lastCollision;
        char followingId;
        bool isClassicGameMode;

        Vertex getRandomDirection();
        void playerCollision(Player *player);


    public:
        Ball(Vertex initialPosition, Audio *audioPlayerPtr, bool isClassicGameMode);
        Vertex speed;
        Vertex position;

        void moveAndCollide(Player *player1, Player *player2);
        void draw();
        void reset();
        void release();
        bool isFollowing();
};

#endif