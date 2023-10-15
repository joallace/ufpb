#include "player.h"

Player::Player(Vertex initialPosition){
    size = {(int) (WINDOW_WIDTH * 0.025), (int) (WINDOW_HEIGHT * 0.25)};
    score = 0;
    speed = WINDOW_HEIGHT*0.017;
    controls = {false, false};
    position = initialPosition;
    defaultPosition = initialPosition;
}

void Player::move(){
    if(controls.up && position.y >= size.y/2)
        position.y -= speed;
    if(controls.down && position.y <= WINDOW_HEIGHT - size.y/2)
        position.y += speed;
}

void Player::draw(){
    glBegin(GL_QUADS);
        glVertex2i(position.x - size.x/2, position.y + size.y/2);
        glVertex2i(position.x + size.x/2, position.y + size.y/2);
        glVertex2i(position.x + size.x/2, position.y - size.y/2);
        glVertex2i(position.x - size.x/2, position.y - size.y/2);
    glEnd();
}

bool Player::collide(Vertex ballPos, int ballRadius){
    float closestX = (ballPos.x < position.x-size.x/2 ? position.x-size.x/2 : (ballPos.x > position.x+size.x/2 ? position.x+size.x/2 : ballPos.x));
    float closestY = (ballPos.y < position.y-size.y/2 ? position.y-size.y/2 : (ballPos.y > position.y+size.y/2 ? position.y+size.y/2 : ballPos.y));
    float dx = closestX - ballPos.x;
    float dy = closestY - ballPos.y;

    return ( dx * dx + dy * dy ) <= ballRadius * ballRadius;
}


void Player::reset(){
    position = defaultPosition;
}

Vertex Player::getSize(){
    return size;
}
