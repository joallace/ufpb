#include "ball.h"

Ball::Ball(Vertex initialPosition){
    samples = 16;
    radius = 16;
    speed = {5, 5};
    position = initialPosition;
    defaultPosition = initialPosition;
}

void Ball::collide(Vertex player1Pos, Vertex player2Pos){
    if(position.x - radius < 0 || position.x + radius> WINDOW_WIDTH)
        speed.x *= -1;
    if(position.y - radius < 0 || position.y + radius > WINDOW_HEIGHT)
        speed.y *= -1;
}


void Ball::move(Vertex player1Pos, Vertex player2Pos){
    collide(player1Pos, player2Pos);
    position.x += speed.x;
    position.y += speed.y;
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
}