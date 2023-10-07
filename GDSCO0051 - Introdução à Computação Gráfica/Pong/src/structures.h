#ifndef STRUCTURES_H
#define STRUCTURES_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Vertex{
    int x;
    int y;

    void operator ++(){
        x>0 ? x++ : x--;
        y>0 ? y++ : y--;
    }
};

struct PlayerControls{
    bool up;
    bool down;
};

#endif