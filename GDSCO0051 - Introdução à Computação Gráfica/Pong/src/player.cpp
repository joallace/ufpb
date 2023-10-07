#include "player.h"

Player::Player(Vertex initialPosition){
    width = WINDOW_WIDTH * 0.025;
    height = WINDOW_HEIGHT * 0.25;
    speed = 10;
    controls = {false, false};
    position = initialPosition;
    defaultPosition = initialPosition;
}

void Player::move(){
    if(controls.up && position.y >= height/2)
        position.y -= speed;
    if(controls.down && position.y <= WINDOW_HEIGHT - height/2)
        position.y += speed;
}

void Player::draw(){
    glBegin(GL_QUADS);
        glVertex2i(position.x - width/2, position.y + height/2);
        glVertex2i(position.x + width/2, position.y + height/2);
        glVertex2i(position.x + width/2, position.y - height/2);
        glVertex2i(position.x - width/2, position.y - height/2);
    glEnd();
}

void Player::reset(){
    position = defaultPosition;
}