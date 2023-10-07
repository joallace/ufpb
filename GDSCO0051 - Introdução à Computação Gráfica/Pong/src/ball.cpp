#include "ball.h"

Ball::Ball(Vertex initialPosition, Audio *audioPlayerPtr){
    samples = 16;
    radius = 16;
    speed = {5, 5};
    position = initialPosition;
    defaultPosition = initialPosition;
    audioPlayer = audioPlayerPtr;
}

void Ball::collide(Vertex player1Pos, Vertex player2Pos, Vertex playerSize){
    if(position.x - radius < 0 || position.x + radius> WINDOW_WIDTH){
        audioPlayer->goal();
        reset();
    }
    if(position.y - radius < 0 || position.y + radius > WINDOW_HEIGHT){
        audioPlayer->wallHit();
        speed.y *= -1;
    }

    if(position.x-radius < player1Pos.x+playerSize.x/2 && position.y > player1Pos.y-playerSize.y/2 && position.y < player1Pos.y+playerSize.y/2){
        audioPlayer->hit();
        speed.x *= -1;
    }
    if(position.x+radius > player2Pos.x-playerSize.x/2 && position.y > player2Pos.y-playerSize.y/2 && position.y < player2Pos.y+playerSize.y/2){
        audioPlayer->hit();
        speed.x *= -1;
    }
}


void Ball::moveAndCollide(Vertex player1Pos, Vertex player2Pos, Vertex playerSize){
    collide(player1Pos, player2Pos, playerSize);
    
    position.x += speed.x;
    position.y += speed.y;
}

void Ball::draw(){
    glBegin(GL_TRIANGLE_FAN);
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
}