#include "ball.h"

Ball::Ball(Vertex initialPosition, Audio *audioPlayerPtr){
    samples = 16;
    radius = 16;
    defaultSpeed = {3, 3};
    speed = getRandomDirection();
    lastCollision = 0;
    position = initialPosition;
    defaultPosition = initialPosition;
    audioPlayer = audioPlayerPtr;
}

Vertex Ball::getRandomDirection(){
    bool xDirection = rand() & 1;
    bool yDirection = rand() & 1;

    return {defaultSpeed.x * (xDirection? 1 : -1), defaultSpeed.y * (yDirection? 1 : -1)};
}

void Ball::collide(Player *player1, Player *player2){
    if((position.x - radius < 0 && ++(player2->score)) || (position.x + radius> WINDOW_WIDTH && ++(player1->score))){
        audioPlayer->goal();
        reset();
    }

    if(position.y - radius < 0 || position.y + radius > WINDOW_HEIGHT){
        audioPlayer->wallHit();
        speed.y *= -1;
    }

    if((lastCollision != 1 && player1->collide(position, radius) && (lastCollision = 1)) ||
       (lastCollision != 2 && player2->collide(position, radius)) && (lastCollision = 2)){
        audioPlayer->hit();
        speed.x *= -1;
        ++speed;
    }
}


void Ball::moveAndCollide(Player *player1, Player *player2){
    collide(player1, player2);
    
    position += speed;
}

void Ball::draw(){
    glBegin(GL_POLYGON);
        for(int i = 0; i < samples; i++){
            float theta = 2.0f * M_PIf * float(i) / samples;

            float local_x = radius * cosf(theta);
            float local_y = radius * sinf(theta);

            glVertex2f(local_x + position.x, local_y + position.y);
        }
    glEnd();
}

void Ball::reset(){
    position = defaultPosition;
    lastCollision = 0;
    speed = getRandomDirection();
}