#include "player.h"

Player::Player(char id, Vertex initialPosition){
    size = {(int) (WINDOW_WIDTH * 0.025), (int) (WINDOW_HEIGHT * 0.25)};
    score = 0;
    speed = WINDOW_HEIGHT*0.017;
    controls = {false, false};
    position = initialPosition;
    defaultPosition = initialPosition;
    this->id = id;
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

void Player::drawScore(Vertex position){
    char scoreStr[3];

    glRasterPos2i(position.x, position.y);
    sprintf(scoreStr, "%d", score);
    for(int i=0; i<3; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreStr[i]);
    }
}

bool Player::collide(Vertex ballPos, int ballRadius){
    float closestX = (ballPos.x < position.x-size.x/2 ? position.x-size.x/2 : (ballPos.x > position.x+size.x/2 ? position.x+size.x/2 : ballPos.x));
    float closestY = (ballPos.y < position.y-size.y/2 ? position.y-size.y/2 : (ballPos.y > position.y+size.y/2 ? position.y+size.y/2 : ballPos.y));
    float dx = closestX - ballPos.x;
    float dy = closestY - ballPos.y;

    return ( dx * dx + dy * dy ) <= ballRadius * ballRadius;
}

char Player::getId(){
    return id;
}

Vertex Player::getSize(){
    return size;
}
