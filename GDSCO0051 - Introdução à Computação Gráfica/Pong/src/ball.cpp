#include "ball.h"

Ball::Ball(Vertex initialPosition, Audio *audioPlayerPtr){
    samples = WINDOW_WIDTH*0.02;
    radius = WINDOW_WIDTH*0.02;
    defaultSpeed = { (int)(WINDOW_WIDTH*0.005), 0};
    speed = getRandomDirection();
    lastCollision = 0;
    followingId = 0;
    position = initialPosition;
    defaultPosition = initialPosition;
    audioPlayer = audioPlayerPtr;
}

Vertex Ball::getRandomDirection(){
    bool xDirection = rand() & 1;
    bool yDirection = rand() & 1;

    return {defaultSpeed.x * (xDirection? 1 : -1), defaultSpeed.y * (yDirection? 1 : -1)};
}

void Ball::playerCollision(Player *player, char id){
    if(lastCollision != id && player->collide(position, radius)){
        audioPlayer->hit();
        lastCollision = id;
        if(player->controls.down)
            speed.y++;
        if(player->controls.up)
            speed.y--;
        speed.x *= -1;
        ++speed;
    }
}

void Ball::moveAndCollide(Player *player1, Player *player2){
    if((position.x - radius < 0 && ++(player2->score)) || (position.x + radius> WINDOW_WIDTH && ++(player1->score))){
        audioPlayer->goal();
        reset();
    }

    if(position.y - radius < 0 || position.y + radius > WINDOW_HEIGHT){
        audioPlayer->wallHit();
        speed.y *= -1;
    }

    playerCollision(player1, 1);
    playerCollision(player2, 2);
    
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